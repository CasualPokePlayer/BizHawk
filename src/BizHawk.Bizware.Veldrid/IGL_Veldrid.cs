using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;

using Veldrid;
using Veldrid.Sdl2;
using Veldrid.SPIRV;
using Veldrid.StartupUtilities;
using Veldrid.Utilities;

using BizHawk.Common;
using BizHawk.Bizware.BizwareGL;

using BizPipeline = BizHawk.Bizware.BizwareGL.Pipeline;
using BizShader = BizHawk.Bizware.BizwareGL.Shader;
using VeldridPipeline = Veldrid.Pipeline;
using VeldridShader = Veldrid.Shader;

namespace BizHawk.Bizware.Veldrid
{
	/// <summary>
	/// Veldrid implementation of the BizwareGL.IGL interface
	/// </summary>
	public class IGL_Veldrid : IGL
	{
		public EDispMethod DispMethodEnum { get; }

		// an SDL2 window derived from a Control backs the graphics device
		private readonly Sdl2Window _sdl2Window;
		private readonly VeldridControlWrapper _graphicsControl;

		internal readonly GraphicsDevice _device;
		private readonly DisposeCollectorResourceFactory _resources;

		private readonly CommandList _commandList;

		//rendering state
		private BizPipeline _currPipeline;
		private RenderTarget _currRenderTarget;

		public string API => "VELDRID";

		public int Version
			=> _device.ApiVersion.Major * 100
				+ _device.ApiVersion.Minor * 10
				+ _device.ApiVersion.Subminor;

		public IGL_Veldrid(EDispMethod dispMethod)
		{
			var preferredBackend = dispMethod switch
			{
				EDispMethod.Direct3D11 => GraphicsBackend.Direct3D11,
				EDispMethod.Vulkan => GraphicsBackend.Vulkan,
				EDispMethod.OpenGL => GraphicsBackend.OpenGL,
				EDispMethod.Metal => GraphicsBackend.Metal,
				EDispMethod.OpenGLES => GraphicsBackend.OpenGLES,
				EDispMethod.GdiPlus => throw new NotSupportedException(),
				_ => throw new InvalidOperationException()
			};

			preferredBackend = GraphicsBackend.OpenGL;

			_graphicsControl = new(this,
				(width, height) =>
				{
					_device!.ResizeMainWindow((uint)width, (uint)height);
				},
				vsyncState =>
				{
					_device!.SyncToVerticalBlank = vsyncState;
				},
				() =>
				{
					_device!.SwapBuffers();
				});

			_graphicsControl.CreateControl();

			// SDL_CreateWindowFrom doesn't implicitly init video, so do it here 
			Sdl2Native.SDL_Init(SDLInitFlags.Video);
			// signal to SDL that this window can use OpenGL
			Sdl2Native.SDL_SetHint("SDL_VIDEO_FOREIGN_WINDOW_OPENGL", "1");

			_sdl2Window = new(_graphicsControl.Handle, false);

			if (!GraphicsDevice.IsBackendSupported(preferredBackend))
			{
				preferredBackend = VeldridStartup.GetPlatformDefaultBackend();
			}

			var gdo = new GraphicsDeviceOptions(false, null, false)
			{
				PreferStandardClipSpaceYDirection = preferredBackend is GraphicsBackend.Vulkan
			};

			try
			{
				_device = VeldridStartup.CreateGraphicsDevice(_sdl2Window, gdo, preferredBackend);
			}
			catch
			{
				preferredBackend = VeldridStartup.GetPlatformDefaultBackend();
				gdo.PreferStandardClipSpaceYDirection = preferredBackend is GraphicsBackend.Vulkan;
				_device = VeldridStartup.CreateGraphicsDevice(_sdl2Window, gdo, preferredBackend);
			}

			_resources = new(_device.ResourceFactory);
			_commandList = _resources.CreateCommandList();

			DispMethodEnum = preferredBackend switch
			{
				GraphicsBackend.Direct3D11 => EDispMethod.Direct3D11,
				GraphicsBackend.Vulkan => EDispMethod.Vulkan,
				GraphicsBackend.OpenGL => EDispMethod.OpenGL,
				GraphicsBackend.Metal => EDispMethod.Metal,
				GraphicsBackend.OpenGLES => EDispMethod.OpenGLES,
				_ => throw new InvalidOperationException()
			};

			CreateRenderStates();
		}

		private void DisposeCollectableResource(IDisposable resource)
		{
			resource.Dispose();
			_resources.DisposeCollector.Remove(resource);
		}

		public void BeginScene()
		{
			_commandList.Begin();
		}

		public void EndScene()
		{
			_commandList.End();
			_device.SubmitCommands(_commandList);
		}

		public void Dispose()
		{
			_device.WaitForIdle();
			_resources.DisposeCollector.DisposeAll();
			_device.Dispose();
			_sdl2Window.Close();
			_graphicsControl.Dispose();
		}

		private RgbaFloat _clearColor;

		public void Clear(ClearBufferMask mask)
		{
			// if the render target is null, you can't clear it?
			if (_currRenderTarget is null) return;

			if (mask.HasFlag(ClearBufferMask.ColorBufferBit))
				_commandList.ClearColorTarget(0, _clearColor);
			if (mask.HasFlag(ClearBufferMask.DepthBufferBit))
				_commandList.ClearDepthStencil(0);

			// other flags unsupported (we only use ColorBufferBit anyways)
		}

		public void SetClearColor(Color color)
		{
			_clearColor = new(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
		}

		public IGraphicsControl Internal_CreateGraphicsControl()
		{
			return _graphicsControl;
		}

		public void FreeTexture(Texture2d tex)
		{
			var texture = (Texture)tex.Opaque;
			DisposeCollectableResource(texture);
		}

		private class ShaderWrapper
		{
			public byte[] SpirvBytecode;
			public string Entrypoint;
			public VeldridShader NativeShader;
			public PipelineInfo PipelineInfo;
			public string Errors;
		}

		private static ShaderWrapper CreateShader(ShaderStages stage, string source, string entry, bool required) 
		{
			try
			{
				var shader = SpirvCompilation.CompileGlslToSpirv(source, null, stage, GlslCompileOptions.Default);
				return new() { SpirvBytecode = shader.SpirvBytes, Entrypoint = entry };
			}
			catch (SpirvCompilationException e) when (!required)
			{
				return new() { Errors = e.Message };
			}
		}

		public BizShader CreateVertexShader(string source, string entry, bool required)
		{
			var shader = CreateShader(ShaderStages.Vertex, source, entry, required);
			return new(this, shader, shader.Errors is null);
		}

		public BizShader CreateFragmentShader(string source, string entry, bool required)
		{
			var shader = CreateShader(ShaderStages.Fragment, source, entry, required);
			return new(this, shader, shader.Errors is null);
		}

		public IBlendState CreateBlendState(
			BlendingFactorSrc colorSource,
			BlendEquationMode colorEquation,
			BlendingFactorDest colorDest,
			BlendingFactorSrc alphaSource,
			BlendEquationMode alphaEquation,
			BlendingFactorDest alphaDest)
		{
			return new CacheBlendState(true, colorSource, colorEquation, colorDest, alphaSource, alphaEquation, alphaDest);
		}

		private BlendStateDescription _blendState;

		public void SetBlendState(IBlendState rsBlend)
		{
			var mybs = (CacheBlendState)rsBlend;
			_blendState = new(RgbaFloat.White, mybs.Description);
		}

		public IBlendState BlendNoneCopy => _rsBlendNoneVerbatim;
		
		public IBlendState BlendNoneOpaque => _rsBlendNoneOpaque;

		public IBlendState BlendNormal => _rsBlendNormal;

		private class PipelineInfo
		{
			public SpirvReflection SpirvReflection;
			public ShaderSetDescription ShaderSet;
			public ResourceLayout[] ResourceLayouts;
			public OutputDescription Outputs;
			public ResourceSet[] ResourceSets;
			public DeviceBuffer VertexBuffer;
			public List<UniformInfo> Uniforms;
		}

		private class PipelineWrapper
		{
			public VeldridPipeline Pipeline;
			public BizShader FragmentShader, VertexShader;
			public PipelineInfo PipelineInfo;
		}

		private CrossCompileTarget GetCrossCompileTarget()
			=> _device.BackendType switch
			{
				GraphicsBackend.Direct3D11 => CrossCompileTarget.HLSL,
				GraphicsBackend.OpenGL => CrossCompileTarget.GLSL,
				GraphicsBackend.Metal => CrossCompileTarget.MSL,
				GraphicsBackend.OpenGLES => CrossCompileTarget.ESSL,
				GraphicsBackend.Vulkan => throw new NotSupportedException(),
				_ => throw new InvalidOperationException()
			};

		private byte[] GetShaderBytes(string code)
			=> _device.BackendType switch
			{
				GraphicsBackend.Direct3D11 or GraphicsBackend.OpenGL or GraphicsBackend.OpenGLES => Encoding.ASCII.GetBytes(code),
				GraphicsBackend.Metal => Encoding.UTF8.GetBytes(code),
				GraphicsBackend.Vulkan => throw new NotSupportedException(),
				_ => throw new InvalidOperationException()
			};

		private PipelineInfo GetPipelineInfo(ShaderWrapper vertexShader, ShaderWrapper fragmentShader)
		{
			if (vertexShader.PipelineInfo is not null && fragmentShader.PipelineInfo is not null
				&& ReferenceEquals(vertexShader.PipelineInfo, fragmentShader.PipelineInfo))
			{
				return vertexShader.PipelineInfo;
			}

			var ret = new PipelineInfo();

			// kinda dumb, we need to cross compile in order to obtain reflection info
			// Vulkan directly takes in bytecode, so the cross compile step doesn't mean anything
			if (_device.BackendType is GraphicsBackend.Vulkan)
			{
				var result = SpirvCompilation.CompileVertexFragment(vertexShader.SpirvBytecode, fragmentShader.SpirvBytecode,
					CrossCompileTarget.GLSL, new(false, false, true));
				vertexShader.NativeShader = _resources.CreateShader(new(ShaderStages.Vertex,
					vertexShader.SpirvBytecode, vertexShader.Entrypoint));
				fragmentShader.NativeShader = _resources.CreateShader(new(ShaderStages.Fragment,
					fragmentShader.SpirvBytecode, fragmentShader.Entrypoint));
				ret.SpirvReflection = result.Reflection;
			}
			else
			{
				var result = SpirvCompilation.CompileVertexFragment(vertexShader.SpirvBytecode, fragmentShader.SpirvBytecode,
					GetCrossCompileTarget(), new(false, false, true));
				if (_device.BackendType is GraphicsBackend.Direct3D11)
				{
					// d3d11 changes entrypoint name to 'main' when cross-compiling
					vertexShader.Entrypoint = "main";
					fragmentShader.Entrypoint = "main";
				}
				vertexShader.NativeShader = _resources.CreateShader(new(ShaderStages.Vertex,
					GetShaderBytes(result.VertexShader), vertexShader.Entrypoint));
				fragmentShader.NativeShader = _resources.CreateShader(new(ShaderStages.Fragment,
					GetShaderBytes(result.FragmentShader), fragmentShader.Entrypoint));
				ret.SpirvReflection = result.Reflection;
			}

			ret.ShaderSet = new(new[] { new VertexLayoutDescription(ret.SpirvReflection.VertexElements) },
				new[] { vertexShader.NativeShader, fragmentShader.NativeShader });

			ret.ResourceLayouts = new ResourceLayout[ret.SpirvReflection.ResourceLayouts.Length];
			for (var i = 0; i < ret.ResourceLayouts.Length; i++)
			{
				ret.ResourceLayouts[i] = _resources.CreateResourceLayout(ref ret.SpirvReflection.ResourceLayouts[i]);
			}

			ret.Outputs = new(null, new OutputAttachmentDescription(PixelFormat.B8_G8_R8_A8_UNorm_SRgb)); // ???

			ret.VertexBuffer = _resources.CreateBuffer(new(ret.ShaderSet.VertexLayouts[0].Stride, BufferUsage.VertexBuffer));
			ret.Uniforms = new();

			ret.ResourceSets = new ResourceSet[ret.ResourceLayouts.Length];
			for (var i = 0; i < ret.ResourceSets.Length; i++)
			{
				var rleds = ret.SpirvReflection.ResourceLayouts[i].Elements;
				var br = new BindableResource[rleds.Length];
				for (var j = 0; j < br.Length; j++)
				{
					var rled = rleds[i];
					if (rled.Kind is ResourceKind.UniformBuffer)
					{
						br[j] = _resources.CreateBuffer(new(1024, BufferUsage.UniformBuffer));
						ret.Uniforms.Add(new()
						{
							Opaque = br[j],
							Name = rled.Name,
							SamplerIndex = j,
							IsSampler = false,
						});
					}
					else
					{
						throw new NotSupportedException();
					}
				}
				var rsd = new ResourceSetDescription(ret.ResourceLayouts[i], br);
				ret.ResourceSets[i] = _resources.CreateResourceSet(ref rsd);
			}

			return ret;
		}

		/// <exception cref="InvalidOperationException">
		/// <paramref name="required"/> is <see langword="true"/> and either <paramref name="vertexShader"/> or <paramref name="fragmentShader"/> is unavailable (their <see cref="BizShader.Available"/> property is <see langword="false"/>), or
		/// <c>glLinkProgram</c> call did not produce expected result
		/// </exception>
		public BizPipeline CreatePipeline(VertexLayout vertexLayout, BizShader vertexShader, BizShader fragmentShader, bool required, string memo)
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

			var vsw = (ShaderWrapper)vertexShader.Opaque;
			var fsw = (ShaderWrapper)fragmentShader.Opaque;

			var pipelineInfo = GetPipelineInfo(vsw, fsw);

			var gpd = new GraphicsPipelineDescription(
				_blendState,
				DepthStencilStateDescription.Disabled, // ???
				RasterizerStateDescription.Default, // ???
				PrimitiveTopology.TriangleStrip, // FIXME: IGL API normally expects this set AFTER making the pipeline, Veldrid wants it BEFORE
				pipelineInfo.ShaderSet,
				pipelineInfo.ResourceLayouts,
				pipelineInfo.Outputs);

			var pipeline = _resources.CreateGraphicsPipeline(ref gpd);

			var pw = new PipelineWrapper { Pipeline = pipeline, VertexShader = vertexShader, FragmentShader = fragmentShader, PipelineInfo = pipelineInfo };
			return new(this, pw, true, vertexLayout, pipelineInfo.Uniforms, memo);
		}

		public void FreePipeline(BizPipeline pipeline)
		{
			// unavailable pipelines will have no opaque
			if (pipeline.Opaque is not PipelineWrapper pw)
			{
				return;
			}

			DisposeCollectableResource(pw.Pipeline);
			pw.FragmentShader.Release();
			pw.VertexShader.Release();
		}

		public void Internal_FreeShader(BizShader shader)
		{
			var sw = (ShaderWrapper)shader.Opaque;
			DisposeCollectableResource(sw.NativeShader);
			sw.NativeShader = null;
			sw.PipelineInfo = null;
		}

		/// <exception cref="InvalidOperationException"><paramref name="pipeline"/>.<see cref="BizPipeline.Available"/> is <see langword="false"/></exception>
		public void BindPipeline(BizPipeline pipeline)
		{
			_currPipeline = pipeline;

			if (pipeline == null)
			{
				return;
			}

			if (!pipeline.Available)
			{
				throw new InvalidOperationException("Attempt to bind unavailable pipeline");
			}

			var pw = (PipelineWrapper)pipeline.Opaque;
			_commandList.SetPipeline(pw.Pipeline);
			for (var i = 0; i < pw.PipelineInfo.ResourceSets.Length; i++)
			{
				_commandList.SetGraphicsResourceSet((uint)i, pw.PipelineInfo.ResourceSets[i]);
			}
		}

		public VertexLayout CreateVertexLayout()
			=> new(this, null);

		public void SetTextureWrapMode(Texture2d tex, bool clamp)
		{
			var mode = clamp ? SamplerAddressMode.Clamp : SamplerAddressMode.Wrap;
			var texture = (Texture)tex.Opaque;
			// TODO
		}

		public void BindArrayData(IntPtr pData)
		{
			if (_currPipeline?.Opaque is PipelineWrapper pipeline)
			{
				var buffer = pipeline.PipelineInfo.VertexBuffer;
				_device.UpdateBuffer(buffer, 0, pData, buffer.SizeInBytes);
				_commandList.SetVertexBuffer(0, buffer);
			}
		}

		public void DrawArrays(PrimitiveType mode, int first, int count)
		{
			_commandList.Draw((uint)count, 1, (uint)first, 0);
		}

		public void SetPipelineUniform(PipelineUniform uniform, bool value)
		{
			var buffer = (DeviceBuffer)uniform.Sole.Opaque;
			_device.UpdateBuffer(buffer, 0, value);
		}

		public void SetPipelineUniformMatrix(PipelineUniform uniform, Matrix4 mat, bool transpose)
		{
			SetPipelineUniformMatrix(uniform, ref mat, transpose);
		}

		public void SetPipelineUniformMatrix(PipelineUniform uniform, ref Matrix4 mat, bool transpose)
		{
			// TODO: handle transpose
			var buffer = (DeviceBuffer)uniform.Sole.Opaque;
			// TODO: does this map correctly?
			_device.UpdateBuffer(buffer, 0, ref mat);
		}

		public void SetPipelineUniform(PipelineUniform uniform, Vector4 value)
		{
			var buffer = (DeviceBuffer)uniform.Sole.Opaque;
			// TODO: does this map correctly?
			_device.UpdateBuffer(buffer, 0, ref value);
		}

		public void SetPipelineUniform(PipelineUniform uniform, Vector2 value)
		{
			var buffer = (DeviceBuffer)uniform.Sole.Opaque;
			// TODO: does this map correctly?
			_device.UpdateBuffer(buffer, 0, ref value);
		}

		public void SetPipelineUniform(PipelineUniform uniform, float value)
		{
			var buffer = (DeviceBuffer)uniform.Sole.Opaque;
			// TODO: does this map correctly?
			_device.UpdateBuffer(buffer, 0, ref value);
		}

		public void SetPipelineUniform(PipelineUniform uniform, Vector4[] values)
		{
			var buffer = (DeviceBuffer)uniform.Sole.Opaque;
			// TODO: does this map correctly?
			_device.UpdateBuffer(buffer, 0, values);
		}

		public void SetPipelineUniformSampler(PipelineUniform uniform, Texture2d tex)
		{
			var sampler = (Sampler)uniform.Sole.Opaque;
			
			// TODO: does this map correctly?
			//_device.UpdateBuffer(buffer, 0, (Texture)tex.Opaque);
		}

		public void SetMinFilter(Texture2d texture, TextureMinFilter minFilter)
		{
			if (texture?.Opaque is Texture tex)
			{
				// todo
				// if (minFilter.HasFlag(TextureMinFilter.Nearest))
				// if (minFilter.HasFlag(TextureMinFilter.Linear))
			}
		}

		public void SetMagFilter(Texture2d texture, TextureMagFilter magFilter)
		{
			if (texture?.Opaque is Texture tex)
			{
				// todo
				// if (magFilter.HasFlag(TextureMinFilter.Nearest))
				// if (magFilter.HasFlag(TextureMinFilter.Linear))
			}
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
			var texDescription = new TextureDescription((uint)width, (uint)height, 1, 1, 1,
				PixelFormat.B8_G8_R8_A8_UNorm_SRgb, TextureUsage.Storage, TextureType.Texture2D);
			var tex = _resources.CreateTexture(ref texDescription);
			return new(this, tex, width, height);
		}

		public Texture2d WrapGLTexture2d(IntPtr glTexId, int width, int height)
		{
			var texDescription = new TextureDescription((uint)width, (uint)height, 0, 1, 1,
				PixelFormat.B8_G8_R8_A8_UNorm_SRgb, TextureUsage.Storage, TextureType.Texture2D);
			var tex = _resources.CreateTexture((ulong)glTexId, ref texDescription);
			return new(this, tex, width, height);
		}

		public void LoadTextureData(Texture2d tex, BitmapBuffer bmp)
		{
			var bmpData = bmp.LockBits();
			try
			{
				var texture = (Texture)tex.Opaque;
				_device.UpdateTexture(texture, bmpData.Scan0, (uint)(bmp.Width * bmp.Height * 4), 0, 0, 0, (uint)bmpData.Width, (uint)bmpData.Height, 1, 0, 0);
			}
			finally
			{
				bmp.UnlockBits(bmpData);
			}
		}

		public void FreeRenderTarget(RenderTarget rt)
		{
			rt.Texture2d.Dispose();
			if (rt.Opaque is Framebuffer fb)
			{
				DisposeCollectableResource(fb);
			}
		}

		private Texture2d CreateRenderTargetTexture(int width, int height)
		{
			var texDescription = new TextureDescription((uint)width, (uint)height, 1, 1, 1,
				PixelFormat.B8_G8_R8_A8_UNorm_SRgb, TextureUsage.RenderTarget, TextureType.Texture2D);
			var tex = _resources.CreateTexture(ref texDescription);
			return new(this, tex, width, height);
		}

		/// <exception cref="InvalidOperationException">framebuffer creation unsuccessful</exception>
		public RenderTarget CreateRenderTarget(int w, int h)
		{
			// create a texture for it
			var tex = CreateRenderTargetTexture(w, h);
			tex.SetMagFilter(TextureMagFilter.Nearest);
			tex.SetMinFilter(TextureMinFilter.Nearest);

			// create the FBO
			var fb = _resources.CreateFramebuffer(new(null, (Texture)tex.Opaque));

			return new(this, fb, tex);
		}

		public void BindRenderTarget(RenderTarget rt)
		{
			_currRenderTarget = rt;
			if (rt?.Opaque is Framebuffer fb)
			{
				_commandList.SetFramebuffer(fb);
			}
		}

		public Texture2d LoadTexture(BitmapBuffer bmp)
		{
			Texture2d ret = null;
			try
			{
				ret = CreateTexture(bmp.Width, bmp.Height);
				LoadTextureData(ret, bmp);
			}
			catch
			{
				ret?.Dispose();
				throw;
			}

			//set default filtering.. its safest to do this always
			ret.SetFilterNearest();

			return ret;
		}

		private Texture2d CreateStagingTexture(int width, int height)
		{
			var texDescription = new TextureDescription((uint)width, (uint)height, 1, 1, 1,
				PixelFormat.B8_G8_R8_A8_UNorm_SRgb, TextureUsage.Staging, TextureType.Texture2D);
			var tex = _resources.CreateTexture(ref texDescription);
			return new(this, tex, width, height);
		}

		public unsafe BitmapBuffer ResolveTexture2d(Texture2d tex)
		{
			var texture = (Texture)tex.Opaque;

			// have to create a staging texture, copy tex to it, then map that
			var stagingTex = CreateStagingTexture((int)texture.Width, (int)texture.Height);
			var stagingTexture = (Texture)stagingTex.Opaque;

			var cl = _resources.CreateCommandList();
			cl.Begin();
			cl.CopyTexture(texture, stagingTexture);
			cl.End();
			_device.SubmitCommands(cl);
			DisposeCollectableResource(cl);
			_device.WaitForIdle();

			var bb = new BitmapBuffer(tex.IntWidth, tex.IntHeight);
			var bmpdata = bb.LockBits();
			var mappedResource = _device.Map(stagingTexture, MapMode.Read);
			try
			{
				var src = new ReadOnlySpan<byte>(mappedResource.Data.ToPointer(), (int)mappedResource.SizeInBytes);
				var dst = new Span<byte>(bmpdata.Scan0.ToPointer(), bmpdata.Height * bmpdata.Stride);
				if (mappedResource.RowPitch == bmpdata.Stride)
				{
					// can direct copy entire thing in this case
					src.CopyTo(dst);
				}
				else
				{
					var rowLen = bmpdata.Width * 4;
					for (var i = 0; i < bmpdata.Height; i++)
					{
						var srcStart = i * (int)mappedResource.RowPitch;
						var dstStart = i * bmpdata.Stride;
						src.Slice(srcStart, rowLen).CopyTo(dst.Slice(dstStart, rowLen));
					}
				}

				return bb;
			}
			finally
			{
				_device.Unmap(stagingTexture);
				bb.UnlockBits(bmpdata);
			}
		}

		public Texture2d LoadTexture(string path)
		{
			using var fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read);
			return LoadTexture(fs);
		}

		public Matrix4 CreateGuiProjectionMatrix(int w, int h)
		{
			return CreateGuiProjectionMatrix(new(w, h));
		}

		public Matrix4 CreateGuiViewMatrix(int w, int h, bool autoflip)
		{
			return CreateGuiViewMatrix(new(w, h), autoflip);
		}

		public Matrix4 CreateGuiProjectionMatrix(Size dims)
		{
			var ret = Matrix4.Identity;
			ret.Row0.X = 2.0f / dims.Width;
			ret.Row1.Y = 2.0f / dims.Height;
			return ret;
		}

		public Matrix4 CreateGuiViewMatrix(Size dims, bool autoflip)
		{
			var ret = Matrix4.Identity;
			ret.Row1.Y = -1.0f;
			ret.Row3.X = -dims.Width * 0.5f;
			ret.Row3.Y = dims.Height * 0.5f;
			if (autoflip && _currRenderTarget is not null) // flip as long as we're not a final render target
			{
				ret.Row1.Y = 1.0f;
				ret.Row3.Y *= -1;
			}
			return ret;
		}

		public void SetViewport(int x, int y, int width, int height)
		{
			var vp = new Viewport(x, y, width, height, 0, 1);
			_commandList.SetViewport(0, ref vp);
			_commandList.SetScissorRect(0, (uint)x, (uint)y, (uint)width, (uint)height); //hack for mupen[rice]+intel: at least the rice plugin leaves the scissor rectangle scrambled, and we're trying to run it in the main graphics context for intel
			//BUT ALSO: new specifications.. viewport+scissor make sense together
		}

		public void SetViewport(int width, int height)
		{
			SetViewport(0, 0, width, height);
		}

		public void SetViewport(Size size)
		{
			SetViewport(size.Width, size.Height);
		}

#if false // see IGL comment
		public void SetViewport(System.Windows.Forms.Control control)
		{
			var r = control.ClientRectangle;
			SetViewport(r.Left, r.Top, r.Width, r.Height);
		}
#endif

		private void CreateRenderStates()
		{
			_rsBlendNoneVerbatim = new(
				false,
				BlendingFactorSrc.One, BlendEquationMode.FuncAdd, BlendingFactorDest.Zero,
				BlendingFactorSrc.One, BlendEquationMode.FuncAdd, BlendingFactorDest.Zero);

			// TODO
			_rsBlendNoneOpaque = new(
				false,
				BlendingFactorSrc.One, BlendEquationMode.FuncAdd, BlendingFactorDest.Zero,
				/*BlendingFactorSrc.ConstantAlpha*/ BlendingFactorSrc.ConstantColor, BlendEquationMode.FuncAdd, BlendingFactorDest.Zero);

			_rsBlendNormal = new(
				true,
				BlendingFactorSrc.SrcAlpha, BlendEquationMode.FuncAdd, BlendingFactorDest.OneMinusSrcAlpha,
				BlendingFactorSrc.One, BlendEquationMode.FuncAdd, BlendingFactorDest.Zero);
		}

		private CacheBlendState _rsBlendNoneVerbatim, _rsBlendNoneOpaque, _rsBlendNormal;
	}
}
