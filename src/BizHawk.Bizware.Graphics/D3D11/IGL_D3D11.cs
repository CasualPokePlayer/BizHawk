// this is a mess, get back to it later
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Numerics;

using BizHawk.Bizware.BizwareGL;
using BizHawk.Common;

using Vortice.D3DCompiler;
using Vortice.Direct3D;
using Vortice.Direct3D11;
using Vortice.Direct3D11.Shader;
using Vortice.DXGI;

// todo - do a better job selecting shader model? base on caps somehow? try several and catch compilation exceptions (yuck, exceptions)
namespace BizHawk.Bizware.Graphics
{
	/// <summary>
	/// Direct3D11 implementation of the BizwareGL.IGL interface
	/// </summary>
	public sealed class IGL_D3D11 : IGL
	{
		public EDispMethod DispMethodEnum => EDispMethod.D3D11;

		private struct D3D11Resources : IDisposable
		{
			public IDXGIFactory2 Factory;
			public ID3D11Device Device;
			public ID3D11DeviceContext Context;
			public ID3D11BlendState BlendEnableState;
			public ID3D11BlendState BlendDisableState;
			public ID3D11RasterizerState RasterizerState;
			public ID3D11SamplerState PointSamplerState;
			public ID3D11SamplerState LinearSamplerState;

			public void CreateResources()
			{
				try
				{
					// we need IDXGIFactory2 for CreateSwapChainForHwnd
					Factory = DXGI.CreateDXGIFactory1<IDXGIFactory2>();
#if true
					// use this to debug D3D11 calls
					// note debug layer requires extra steps to use: https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-layers#debug-layer
					// also debug output will only be present with a "native debugger" attached (pure managed debugger can't see this output)
					const DeviceCreationFlags creationFlags = DeviceCreationFlags.Singlethreaded | DeviceCreationFlags.BgraSupport | DeviceCreationFlags.Debug;
#else
					// IGL is not thread safe, so let's not bother making this implementation thread safe
					const DeviceCreationFlags creationFlags = DeviceCreationFlags.Singlethreaded | DeviceCreationFlags.BgraSupport;
#endif
					D3D11.D3D11CreateDevice(
						adapter: null,
						DriverType.Hardware,
						creationFlags,
						featureLevels: null!,
						out Device,
						out Context).CheckError();

					var bd = default(BlendDescription);
					bd.AlphaToCoverageEnable = false;
					bd.IndependentBlendEnable = false;
					bd.RenderTarget[0].BlendEnable = true;
					bd.RenderTarget[0].SourceBlend = Blend.SourceAlpha;
					bd.RenderTarget[0].DestinationBlend = Blend.InverseSourceAlpha;
					bd.RenderTarget[0].BlendOperation = BlendOperation.Add;
					bd.RenderTarget[0].SourceBlendAlpha = Blend.One;
					bd.RenderTarget[0].DestinationBlendAlpha = Blend.Zero;
					bd.RenderTarget[0].BlendOperationAlpha = BlendOperation.Add;
					bd.RenderTarget[0].RenderTargetWriteMask = ColorWriteEnable.All;
					BlendEnableState = Device.CreateBlendState(bd);

					bd.RenderTarget[0].BlendEnable = false;
					bd.RenderTarget[0].SourceBlend = Blend.One;
					bd.RenderTarget[0].DestinationBlend = Blend.Zero;
					BlendDisableState = Device.CreateBlendState(bd);

					var rd = new RasterizerDescription()
					{
						CullMode = CullMode.None,
						FillMode = FillMode.Solid,
						ScissorEnable = true,
					};

					RasterizerState = Device.CreateRasterizerState(rd);

					PointSamplerState = Device.CreateSamplerState(SamplerDescription.PointClamp);
					LinearSamplerState = Device.CreateSamplerState(SamplerDescription.LinearClamp);
				}
				catch
				{
					Dispose();
					throw;
				}
			}

			public void Dispose()
			{
				LinearSamplerState?.Dispose();
				LinearSamplerState = null;
				PointSamplerState?.Dispose();
				PointSamplerState = null;

				RasterizerState?.Dispose();
				RasterizerState = null;

				BlendEnableState?.Dispose();
				BlendEnableState = null;
				BlendDisableState?.Dispose();
				BlendDisableState = null;

				Context?.Dispose();
				Context = null;
				Device?.Dispose();
				Device = null;

				Factory?.Dispose();
				Factory = null;
			}
		}

		// D3D11 resources
		// these might need to be thrown out and recreated if the device is lost
		private D3D11Resources _resources;

		private IDXGIFactory2 Factory => _resources.Factory;
		private ID3D11Device Device => _resources.Device;
		private ID3D11DeviceContext Context => _resources.Context;
		private ID3D11BlendState BlendEnableState => _resources.BlendEnableState;
		private ID3D11BlendState BlendDisableState => _resources.BlendDisableState;
		private ID3D11RasterizerState RasterizerState => _resources.RasterizerState;
		private ID3D11SamplerState PointSamplerState => _resources.PointSamplerState;
		private ID3D11SamplerState LinearSamplerState => _resources.LinearSamplerState;

		// rendering state
		private Pipeline _curPipeline;
		private RenderTarget _curRenderTarget;
		private D3D11SwapChain.SwapChainResources _controlSwapChain;

		// misc state
		private readonly HashSet<RenderTarget> _renderTargets = new();

		public string API => "D3D11";

		public IGL_D3D11()
		{
			if (OSTailoredCode.IsUnixHost)
			{
				throw new NotSupportedException("D3D11 is Windows only");
			}

			_resources.CreateResources();
		}

		private static SwapChainDescription1 CreateSwapChainDescription(D3D11SwapChain.ControlParameters cp)
		{
			return new(
				width: cp.Width,
				height: cp.Height,
				format: Format.B8G8R8A8_UNorm,
				stereo: false,
				swapEffect: SwapEffect.FlipSequential,
				bufferUsage: Usage.RenderTargetOutput,
				bufferCount: 2,
				scaling: Scaling.Stretch,
				alphaMode: AlphaMode.Ignore,
				flags: SwapChainFlags.AllowTearing);
		}

		private void ResetDevice(D3D11SwapChain.ControlParameters cp)
		{
			SuspendRenderTargets();
			_controlSwapChain.Dispose();

			ResumeRenderTargets();

			var sd = CreateSwapChainDescription(cp);
			var swapChain = Factory.CreateSwapChainForHwnd(Device, cp.Handle, sd);
			var bbTex = swapChain.GetBuffer<ID3D11Texture2D>(0);
			var rtv = Device.CreateRenderTargetView(bbTex);

			_controlSwapChain.Device = Device;
			_controlSwapChain.Context = Context;
			_controlSwapChain.BackBufferTexture = bbTex;
			_controlSwapChain.RTV = rtv;
			_controlSwapChain.SwapChain = swapChain;
		}

		public D3D11SwapChain CreateSwapChain(D3D11SwapChain.ControlParameters cp)
		{
			if (_controlSwapChain != null)
			{
				throw new InvalidOperationException($"{nameof(IGL_D3D11)} can only have 1 control swap chain");
			}

			var sd = CreateSwapChainDescription(cp);
			var swapChain = Factory.CreateSwapChainForHwnd(Device, cp.Handle, sd);
			var bbTex = swapChain.GetBuffer<ID3D11Texture2D>(0);
			var rtv = Device.CreateRenderTargetView(bbTex);

			_controlSwapChain = new D3D11SwapChain.SwapChainResources
			{
				Device = Device,
				Context = Context,
				BackBufferTexture = bbTex,
				RTV = rtv,
				SwapChain = swapChain
			};

			return new(_controlSwapChain, ResetDevice);
		}

		public void Dispose()
		{
			_controlSwapChain.Dispose();
			_resources.Dispose();
		}

		public void ClearColor(Color color)
		{
			if (_curRenderTarget == null)
			{
				Context.ClearRenderTargetView(_controlSwapChain.RTV, new(color.R, color.B, color.G, color.A));
			}
			else
			{
				var rw = (RenderTargetWrapper)_curRenderTarget.Opaque;
				Context.ClearRenderTargetView(rw.RTV, new(color.R, color.B, color.G, color.A));
			}
		}

		public void FreeTexture(Texture2d tex)
		{
			var tw = (TextureWrapper)tex.Opaque;
			tw.Texture.Dispose();
			tw.SRV.Dispose();
		}

		private class ShaderWrapper // Disposable fields cleaned up by Internal_FreeShader
		{
			public ReadOnlyMemory<byte> Bytecode;
			public ID3D11ShaderReflection Reflection;
			public ID3D11VertexShader VS;
			public ID3D11PixelShader PS;
			public Shader IGLShader;
		}

		/// <exception cref="InvalidOperationException"><paramref name="required"/> is <see langword="true"/> and compilation error occurred</exception>
		public Shader CreateFragmentShader(string source, string entry, bool required)
		{
			try
			{
				var sw = new ShaderWrapper();

				// ShaderFlags.EnableBackwardsCompatibility - used this once upon a time (please leave a note about why)
				var result = Compiler.Compile(
					shaderSource: source,
					entryPoint: entry,
					sourceName: null!, // this is safe to be null
					profile: "ps_4_0_level_9_1",
					shaderFlags: ShaderFlags.OptimizationLevel3);

				sw.PS = Device.CreatePixelShader(result.Span);
				sw.Reflection = Compiler.Reflect<ID3D11ShaderReflection>(result.Span);
				sw.Bytecode = result;

				var s = new Shader(this, sw, true);
				sw.IGLShader = s;

				return s;
			}
			catch (Exception ex)
			{
				if (required)
				{
					throw;
				}

				return new(this, null, false) { Errors = ex.ToString() };
			}
		}

		/// <exception cref="InvalidOperationException"><paramref name="required"/> is <see langword="true"/> and compilation error occurred</exception>
		public Shader CreateVertexShader(string source, string entry, bool required)
		{
			try
			{
				var sw = new ShaderWrapper();

				var result = Compiler.Compile(
					shaderSource: source,
					entryPoint: entry,
					sourceName: null!, // this is safe to be null
					profile: "vs_4_0_level_9_1",
					shaderFlags: ShaderFlags.OptimizationLevel3);

				sw.VS = Device.CreateVertexShader(result.Span);
				sw.Reflection = Compiler.Reflect<ID3D11ShaderReflection>(result.Span);
				sw.Bytecode = result;

				var s = new Shader(this, sw, true);
				sw.IGLShader = s;

				return s;
			}
			catch (Exception ex)
			{
				if (required)
				{
					throw;
				}

				return new(this, null, false) { Errors = ex.ToString() };
			}
		}

		public void EnableBlending()
			=> Context.OMSetBlendState(BlendEnableState);

		public void DisableBlending()
			=> Context.OMSetBlendState(BlendDisableState);

		/// <exception cref="InvalidOperationException">
		/// <paramref name="required"/> is <see langword="true"/> and either <paramref name="vertexShader"/> or <paramref name="fragmentShader"/> is unavailable (their <see cref="Shader.Available"/> property is <see langword="false"/>), or
		/// one of <paramref name="vertexLayout"/>'s items has an unsupported value in <see cref="VertexLayout.LayoutItem.AttribType"/>, <see cref="VertexLayout.LayoutItem.Components"/>, or <see cref="VertexLayout.LayoutItem.Usage"/>
		/// </exception>
		public Pipeline CreatePipeline(VertexLayout vertexLayout, Shader vertexShader, Shader fragmentShader, bool required, string memo)
		{
			if (!vertexShader.Available || !fragmentShader.Available)
			{
				var errors = $"Vertex Shader:\r\n {vertexShader.Errors} \r\n-------\r\nFragment Shader:\r\n{fragmentShader.Errors}";
				if (required)
				{
					throw new InvalidOperationException($"Couldn't build required GL pipeline:\r\n{errors}");
				}

				return new(this, null, false, null, null, null) { Errors = errors };
			}

			var ves = new InputElementDescription[vertexLayout.Items.Count];
			var stride = 0;
			foreach (var (i, item) in vertexLayout.Items)
			{
				if (item.AttribType != VertexAttribPointerType.Float)
				{
					throw new NotSupportedException();
				}

				var semanticName = item.Usage switch
				{
					AttribUsage.Position => "POSITION",
					AttribUsage.Color0 => "COLOR",
					AttribUsage.Texcoord0 or AttribUsage.Texcoord1 => "TEXCOORD",
					_ => throw new InvalidOperationException()
				};

				var format = item.Components switch
				{
					1 => Format.R32_Float,
					2 => Format.R32G32_Float,
					3 => Format.R32G32B32_Float,
					4 => Format.R32G32B32A32_Float,
					_ => throw new InvalidOperationException()
				};

				ves[i] = new(semanticName, item.Usage == AttribUsage.Texcoord1 ? 1 : 0, format, item.Offset, 0);
				stride += 4 * item.Components;
			}

			var bc = ((ShaderWrapper)vertexShader.Opaque).Bytecode.Span;
			var vlw = (VertexLayoutWrapper)vertexLayout.Opaque;
			vlw.VertexDeclaration = Device.CreateInputLayout(ves, bc);
			vlw.VertexStride = stride;

			var pw = new PipelineWrapper
			{
				VertexShader = (ShaderWrapper)vertexShader.Opaque,
				FragmentShader = (ShaderWrapper)fragmentShader.Opaque,
			};

			// scan uniforms from reflection
			var uniforms = new List<UniformInfo>();
			var vsrefl = pw.VertexShader.Reflection;
			var psrefl = pw.FragmentShader.Reflection;
			foreach (var refl in new[] { vsrefl, psrefl })
			{
				var isVs = refl == vsrefl;
				var reflCb = refl.ConstantBuffers.SingleOrDefault();
				if (reflCb != null)
				{
					var cbDesc = reflCb.Description;
					var cbSize = (cbDesc.Size + 15) & ~15; // must be aligned to 16 bytes
					var bd = new BufferDescription(cbSize, BindFlags.ConstantBuffer, ResourceUsage.Dynamic, CpuAccessFlags.Write);
					var constantBuffer = Device.CreateBuffer(bd);
					var pendingBuffer = Marshal.AllocCoTaskMem(cbSize);
					if (isVs)
					{
						pw.VSConstantBuffer = constantBuffer;
						pw.VSPendingBuffer = pendingBuffer;
						pw.VSConstantBufferSize = cbDesc.Size;
					}
					else
					{
						pw.PSConstantBuffer = constantBuffer;
						pw.PSPendingBuffer = pendingBuffer;
						pw.PSConstantBufferSize = cbDesc.Size;
					}

					uniforms.AddRange(reflCb.Variables
						.Select(reflCbVari => reflCbVari.Description)
						.Select(cbVariDesc => new UniformInfo
						{
							Name = cbVariDesc.Name,
							Opaque = new UniformWrapper
							{
								PendingBuffer = pendingBuffer,
								VariableStartOffset = cbVariDesc.StartOffset,
								VariableSize = cbVariDesc.Size,
								VS = isVs
							}
						}));
				}

				uniforms.AddRange(refl.BoundResources
					.Where(resource => resource.Type == ShaderInputType.Sampler)
					.Select(resource => new UniformInfo
					{
						IsSampler = true,
						Name = resource.Name,
						Opaque = new UniformWrapper { VS = isVs },
						SamplerIndex = resource.BindPoint
					}));
			}

			return new(this, pw, true, vertexLayout, uniforms, memo);
		}

		public void FreePipeline(Pipeline pipeline)
		{
			// unavailable pipelines will have no opaque
			if (pipeline.Opaque is not PipelineWrapper pw)
			{
				return;
			}

			Marshal.FreeCoTaskMem(pw.VSPendingBuffer);
			Marshal.FreeCoTaskMem(pw.PSPendingBuffer);
			pw.VSConstantBuffer?.Dispose();
			pw.PSConstantBuffer?.Dispose();
			pw.FragmentShader.IGLShader.Release();
			pw.VertexShader.IGLShader.Release();
		}

		public void Internal_FreeShader(Shader shader)
		{
			var sw = (ShaderWrapper)shader.Opaque;
			sw.Reflection?.Dispose();
			sw.PS?.Dispose();
			sw.VS?.Dispose();
		}

		private class UniformWrapper
		{
			public IntPtr PendingBuffer;
			public int VariableStartOffset;
			public int VariableSize;
			public bool VS;
		}

		private class PipelineWrapper // Disposable fields cleaned up by FreePipeline
		{
			public IntPtr VSPendingBuffer, PSPendingBuffer;
			public int VSConstantBufferSize, PSConstantBufferSize;
			public ID3D11Buffer VSConstantBuffer, PSConstantBuffer;

			public ShaderWrapper VertexShader, FragmentShader;
		}

		private class TextureWrapper
		{
			public ID3D11Texture2D Texture;
			public ID3D11ShaderResourceView SRV;
			public bool LinearFiltering;
		}

		private class RenderTargetWrapper
		{
			public ID3D11RenderTargetView RTV;
		}

		private class VertexLayoutWrapper
		{
			public ID3D11InputLayout VertexDeclaration;
			public int VertexStride;

			public ID3D11Buffer VertexBuffer;
			public int VertexBufferCount;
		}

		public VertexLayout CreateVertexLayout()
			=> new(this, new VertexLayoutWrapper());

		public void Internal_FreeVertexLayout(VertexLayout layout)
		{
			var vlw = (VertexLayoutWrapper)layout.Opaque;
			vlw.VertexDeclaration?.Dispose();
			vlw.VertexBuffer?.Dispose();
		}

		public void BindPipeline(Pipeline pipeline)
		{
			_curPipeline = pipeline;

			if (pipeline == null)
			{
				// unbind? i don't know
				return;
			}

			var pw = (PipelineWrapper)pipeline.Opaque;
			Context.PSSetShader(pw.FragmentShader.PS);
			Context.VSSetShader(pw.VertexShader.VS);

			var vlw = (VertexLayoutWrapper)pipeline.VertexLayout.Opaque;
			Context.IASetInputLayout(vlw.VertexDeclaration);

			Context.RSSetState(RasterizerState);
		}

		public void SetPipelineUniform(PipelineUniform uniform, bool value)
		{
			foreach (var ui in uniform.UniformInfos)
			{
				var uw = (UniformWrapper)ui.Opaque;
				unsafe
				{
					// note: HLSL bool is 4 bytes large
					var b = value ? 1 : 0;
					var variablePtr = (void*)(uw.PendingBuffer + uw.VariableStartOffset);
					Buffer.MemoryCopy(&b, variablePtr, uw.VariableSize, sizeof(int));
				}
			}
		}

		public void SetPipelineUniformMatrix(PipelineUniform uniform, Matrix4x4 mat, bool transpose)
			=> SetPipelineUniformMatrix(uniform, ref mat, transpose);

		public void SetPipelineUniformMatrix(PipelineUniform uniform, ref Matrix4x4 mat, bool transpose)
		{
			foreach (var ui in uniform.UniformInfos)
			{
				var uw = (UniformWrapper)ui.Opaque;
				unsafe
				{
					// transpose logic is inversed
					var m = transpose ? mat : Matrix4x4.Transpose(mat);
					var variablePtr = (void*)(uw.PendingBuffer + uw.VariableStartOffset);
					Buffer.MemoryCopy(&m, variablePtr, uw.VariableSize, sizeof(Matrix4x4));
				}
			}
		}

		public void SetPipelineUniform(PipelineUniform uniform, Vector4 value)
		{
			foreach (var ui in uniform.UniformInfos)
			{
				var uw = (UniformWrapper)ui.Opaque;
				unsafe
				{
					var variablePtr = (void*)(uw.PendingBuffer + uw.VariableStartOffset);
					Buffer.MemoryCopy(&value, variablePtr, uw.VariableSize, sizeof(Vector4));
				}
			}
		}

		public void SetPipelineUniform(PipelineUniform uniform, Vector2 value)
		{
			foreach (var ui in uniform.UniformInfos)
			{
				var uw = (UniformWrapper)ui.Opaque;
				unsafe
				{
					var variablePtr = (void*)(uw.PendingBuffer + uw.VariableStartOffset);
					Buffer.MemoryCopy(&value, variablePtr, uw.VariableSize, sizeof(Vector2));
				}
			}
		}

		public void SetPipelineUniform(PipelineUniform uniform, float value)
		{
			foreach (var ui in uniform.UniformInfos)
			{
				var uw = (UniformWrapper)ui.Opaque;
				unsafe
				{
					var variablePtr = (void*)(uw.PendingBuffer + uw.VariableStartOffset);
					Buffer.MemoryCopy(&value, variablePtr, uw.VariableSize, sizeof(float));
				}
			}
		}

		public void SetPipelineUniform(PipelineUniform uniform, Vector4[] values)
		{
			foreach (var ui in uniform.UniformInfos)
			{
				var uw = (UniformWrapper)ui.Opaque;
				unsafe
				{
					fixed (Vector4* v = values)
					{
						var variablePtr = (void*)(uw.PendingBuffer + uw.VariableStartOffset);
						Buffer.MemoryCopy(v, variablePtr, uw.VariableSize, values.Length * sizeof(Vector4));
					}
				}
			}
		}

		public void SetPipelineUniformSampler(PipelineUniform uniform, Texture2d tex)
		{
			if (uniform.Owner == null)
			{
				return; // uniform was optimized out
			}

			var tw = (TextureWrapper)tex.Opaque;
			var sampler = tw.LinearFiltering ? LinearSamplerState : PointSamplerState;

			foreach (var ui in uniform.UniformInfos)
			{
				if (!ui.IsSampler)
				{
					throw new InvalidOperationException("Uniform was not a texture/sampler");
				}

				var uw = (UniformWrapper)ui.Opaque;
				if (uw.VS)
				{
					Context.VSSetShaderResource(ui.SamplerIndex, tw.SRV);
					Context.VSSetSampler(ui.SamplerIndex, sampler);
				}
				else
				{
					Context.PSSetShaderResource(ui.SamplerIndex, tw.SRV);
					Context.PSSetSampler(ui.SamplerIndex, sampler);
				}
			}
		}

		public void SetTextureWrapMode(Texture2d tex, bool clamp)
		{
		}

		// TODO: Merge these to one call (for Linear / Nearest)
		public void SetMinFilter(Texture2d texture, TextureMinFilter minFilter)
		{
			var tw = (TextureWrapper)texture.Opaque;
			tw.LinearFiltering = minFilter == TextureMinFilter.Linear;
		}

		public void SetMagFilter(Texture2d texture, TextureMagFilter magFilter)
		{
			var tw = (TextureWrapper)texture.Opaque;
			tw.LinearFiltering = magFilter == TextureMagFilter.Linear;
		}

		public Texture2d LoadTexture(Bitmap bitmap)
		{
			using var bmp = new BitmapBuffer(bitmap, new());
			return LoadTexture(bmp);
		}

		public Texture2d LoadTexture(Stream stream)
		{
			using var bmp = new BitmapBuffer(stream, new());
			return LoadTexture(bmp);
		}

		public Texture2d CreateTexture(int width, int height)
		{
			var tex = Device.CreateTexture2D(
				Format.B8G8R8A8_UNorm,
				width,
				height,
				mipLevels: 1,
				bindFlags: BindFlags.ShaderResource,
				usage: ResourceUsage.Dynamic,
				cpuAccessFlags: CpuAccessFlags.Write);
			var srvd = new ShaderResourceViewDescription(ShaderResourceViewDimension.Texture2D, Format.B8G8R8A8_UNorm, mipLevels: 1, mostDetailedMip: 0);
			var srv = Device.CreateShaderResourceView(tex, srvd);
			var tw = new TextureWrapper { Texture = tex, SRV = srv };
			return new(this, tw, width, height);
		}

		public Texture2d WrapGLTexture2d(IntPtr glTexId, int width, int height)
		{
			// not used for non-GL backends
			return null;
		}

		/// <exception cref="InvalidOperationException">GDI+ call returned unexpected data</exception>
		public unsafe void LoadTextureData(Texture2d tex, BitmapBuffer bmp)
		{
			var tw = (TextureWrapper)tex.Opaque;
			var bmpData = bmp.LockBits();

			try
			{
				var srcSpan = new ReadOnlySpan<byte>(bmpData.Scan0.ToPointer(), bmpData.Stride * bmp.Height);
				var mappedTex = Context.Map<byte>(tw.Texture, 0, 0, MapMode.WriteDiscard);

				// TODO - do we need to handle odd sizes, weird pitches here?
				if (bmp.Width != tex.IntWidth || bmp.Height != tex.IntHeight || srcSpan.Length != mappedTex.Length)
				{
					throw new InvalidOperationException();
				}

				srcSpan.CopyTo(mappedTex);
			}
			finally
			{
				Context.Unmap(tw.Texture, 0);
				bmp.UnlockBits(bmpData);
			}
		}

		public Texture2d LoadTexture(BitmapBuffer bmp)
		{
			var ret = CreateTexture(bmp.Width, bmp.Height);
			LoadTextureData(ret, bmp);
			return ret;
		}

		/// <exception cref="InvalidOperationException">Vortice call returned unexpected data</exception>
		public BitmapBuffer ResolveTexture2d(Texture2d tex)
		{
			using var target = Device.CreateTexture2D(
				Format.B8G8R8A8_UNorm,
				tex.IntWidth,
				tex.IntHeight,
				bindFlags: BindFlags.None,
				usage: ResourceUsage.Staging,
				cpuAccessFlags: CpuAccessFlags.Read);

			var tw = (TextureWrapper)tex.Opaque;
			Context.CopyResource(target, tw.Texture);

			try
			{
				var srcSpan = Context.MapReadOnly<byte>(target);
				var pixels = new int[tex.IntWidth * tex.IntHeight];
				var dstSpan = MemoryMarshal.AsBytes(pixels.AsSpan());

				if (srcSpan.Length != dstSpan.Length)
				{
					throw new InvalidOperationException();
				}

				srcSpan.CopyTo(dstSpan);
				return new(tex.IntWidth, tex.IntHeight, pixels);
			}
			finally
			{
				Context.Unmap(target, 0);
			}
		}

		public Texture2d LoadTexture(string path)
		{
			using var fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read);
			return LoadTexture(fs);
		}

		public Matrix4x4 CreateGuiProjectionMatrix(int w, int h)
			=> CreateGuiProjectionMatrix(new(w, h));

		public Matrix4x4 CreateGuiViewMatrix(int w, int h, bool autoFlip)
			=> CreateGuiViewMatrix(new(w, h), autoFlip);

		public Matrix4x4 CreateGuiProjectionMatrix(Size dims)
		{
			var ret = Matrix4x4.Identity;
			ret.M11 = 2.0f / dims.Width;
			ret.M22 = 2.0f / dims.Height;
			return ret;
		}

		public Matrix4x4 CreateGuiViewMatrix(Size dims, bool autoFlip)
		{
			var ret = Matrix4x4.Identity;
			ret.M22 = -1.0f;
			ret.M41 = -dims.Width * 0.5f - 0.5f;
			ret.M42 = dims.Height * 0.5f + 0.5f;

			// auto-flipping isn't needed on D3D
			return ret;
		}

		public void SetViewport(int x, int y, int width, int height)
		{
			Context.RSSetViewport(x, y, width, height);
			Context.RSSetScissorRect(x, y, width, height);
		}

		public void SetViewport(int width, int height)
			=> SetViewport(0, 0, width, height);

		public void SetViewport(Size size)
			=> SetViewport(size.Width, size.Height);

		public void FreeRenderTarget(RenderTarget rt)
		{
			var tw = (TextureWrapper)rt.Texture2d.Opaque;
			tw.Texture.Dispose();
			tw.Texture = null;
			_renderTargets.Remove(rt);
		}

		public RenderTarget CreateRenderTarget(int w, int h)
		{
			var tw = new TextureWrapper { Texture = CreateRenderTargetTexture(w, h) };
			var tex = new Texture2d(this, tw, w, h);
			var rtvd = new RenderTargetViewDescription(RenderTargetViewDimension.Texture2D, Format.B8G8R8A8_UNorm);
			var rw = new RenderTargetWrapper { RTV = Device.CreateRenderTargetView(tw.Texture, rtvd) };
			var rt = new RenderTarget(this, rw, tex);
			_renderTargets.Add(rt);
			return rt;
		}

		private ID3D11Texture2D CreateRenderTargetTexture(int width, int height)
		{
			return Device.CreateTexture2D(
				Format.B8G8R8A8_UNorm,
				width,
				height,
				bindFlags: BindFlags.RenderTarget,
				usage: ResourceUsage.Default,
				cpuAccessFlags: CpuAccessFlags.None);
		}

		private void SuspendRenderTargets()
		{
			foreach (var tw in _renderTargets.Select(rt => (TextureWrapper)rt.Texture2d.Opaque))
			{
				tw.Texture.Dispose();
				tw.Texture = null;
			}
		}

		private void ResumeRenderTargets()
		{
			foreach (var rt in _renderTargets)
			{
				var tw = (TextureWrapper)rt.Texture2d.Opaque;
				tw.Texture = CreateRenderTargetTexture(rt.Texture2d.IntWidth, rt.Texture2d.IntHeight);
			}
		}

		public void BindRenderTarget(RenderTarget rt)
		{
			_curRenderTarget = rt;

			if (rt == null)
			{
				Context.OMSetRenderTargets(_controlSwapChain.RTV);
				return;
			}

			var rw = (RenderTargetWrapper)rt.Opaque;
			Context.OMSetRenderTargets(rw.RTV);
		}

		public void Draw(IntPtr data, int count)
		{
			Context.IASetPrimitiveTopology(PrimitiveTopology.TriangleStrip);

			var vlw = (VertexLayoutWrapper)_curPipeline.VertexLayout.Opaque;
			var stride = vlw.VertexStride;

			if (vlw.VertexBufferCount < count)
			{
				vlw.VertexBuffer?.Dispose();
				var bd = new BufferDescription(stride * count, BindFlags.VertexBuffer, ResourceUsage.Dynamic, CpuAccessFlags.Write);
				vlw.VertexBuffer = Device.CreateBuffer(in bd, data);
				vlw.VertexBufferCount = count;
			}
			else
			{
				var mappedVb = Context.Map(vlw.VertexBuffer, MapMode.WriteDiscard);
				try
				{
					unsafe
					{
						Buffer.MemoryCopy((void*)data, (void*)mappedVb.DataPointer, stride * vlw.VertexBufferCount, stride * count);
					}
				}
				finally
				{
					Context.Unmap(vlw.VertexBuffer);
				}
			}

			Context.IASetVertexBuffer(0, vlw.VertexBuffer, stride);

			unsafe
			{
				var pw = (PipelineWrapper)_curPipeline.Opaque;

				if (pw.VSConstantBuffer != null)
				{
					var vsCb = Context.Map(pw.VSConstantBuffer, MapMode.WriteDiscard);
					Buffer.MemoryCopy((void*)pw.VSPendingBuffer, (void*)vsCb.DataPointer, pw.VSConstantBufferSize, pw.VSConstantBufferSize);
					Context.Unmap(pw.VSConstantBuffer);
					Context.VSSetConstantBuffer(0, pw.VSConstantBuffer);
				}

				if (pw.PSConstantBuffer != null)
				{
					var psCb = Context.Map(pw.PSConstantBuffer, MapMode.WriteDiscard);
					Buffer.MemoryCopy((void*)pw.PSPendingBuffer, (void*)psCb.DataPointer, pw.PSConstantBufferSize, pw.PSConstantBufferSize);
					Context.Unmap(pw.PSConstantBuffer);
					Context.PSSetConstantBuffer(0, pw.PSConstantBuffer);
				}
			}

			Context.Draw(count - 2, 0);
		}

		public void BeginScene()
		{
		}

		public void EndScene()
		{
		}
	}
}
