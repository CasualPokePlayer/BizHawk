using System;
using Veldrid;
using BizHawk.Bizware.BizwareGL;

namespace BizHawk.Bizware.Veldrid
{
	/// <summary>
	/// An IBlendState token that just caches all the args needed to create a blend state
	/// </summary>
	public class CacheBlendState : IBlendState
	{
		public readonly BlendAttachmentDescription Description;

		public CacheBlendState(
			bool enabled,
			BlendingFactorSrc colorSource,
			BlendEquationMode colorEquation,
			BlendingFactorDest colorDest,
			BlendingFactorSrc alphaSource,
			BlendEquationMode alphaEquation,
			BlendingFactorDest alphaDest)
		{
			Description.BlendEnabled = enabled;
			Description.ColorWriteMask = null; // TODO
			Description.SourceColorFactor = colorSource.ConvertToVeldrid();
			Description.DestinationColorFactor = colorDest.ConvertToVeldrid();
			Description.ColorFunction = colorEquation.ConvertToVeldrid();
			Description.SourceAlphaFactor = alphaSource.ConvertToVeldrid();
			Description.DestinationAlphaFactor = alphaDest.ConvertToVeldrid();
			Description.AlphaFunction = alphaEquation.ConvertToVeldrid();
		}
	}

	public static class BlendingStateExtensions
	{
		public static BlendFactor ConvertToVeldrid(this BlendingFactorSrc bfs)
			=> bfs switch
			{
				BlendingFactorSrc.Zero => BlendFactor.Zero,
				BlendingFactorSrc.One => BlendFactor.One,
				BlendingFactorSrc.SrcColor => BlendFactor.SourceColor,
				BlendingFactorSrc.OneMinusSrcColor => BlendFactor.InverseSourceColor,
				BlendingFactorSrc.SrcAlpha => BlendFactor.SourceAlpha,
				BlendingFactorSrc.OneMinusSrcAlpha => BlendFactor.InverseSourceAlpha,
				BlendingFactorSrc.DstAlpha => BlendFactor.DestinationAlpha,
				BlendingFactorSrc.OneMinusDstAlpha => BlendFactor.InverseDestinationAlpha,
				BlendingFactorSrc.DstColor => BlendFactor.DestinationColor,
				BlendingFactorSrc.OneMinusDstColor => BlendFactor.InverseDestinationColor,
				BlendingFactorSrc.SrcAlphaSaturate => throw new NotSupportedException(),
				BlendingFactorSrc.ConstantColor => BlendFactor.BlendFactor,
				BlendingFactorSrc.OneMinusConstantColor => BlendFactor.InverseBlendFactor,
				BlendingFactorSrc.ConstantAlpha => throw new NotSupportedException(),
				BlendingFactorSrc.OneMinusConstantAlpha => throw new NotSupportedException(),
				BlendingFactorSrc.Src1Alpha => throw new NotSupportedException(),
				BlendingFactorSrc.Src1Color => throw new NotSupportedException(),
				BlendingFactorSrc.OneMinusSrc1Color => throw new NotSupportedException(),
				BlendingFactorSrc.OneMinusSrc1Alpha => throw new NotSupportedException(),
				_ => throw new InvalidOperationException(),
			};

		public static BlendFactor ConvertToVeldrid(this BlendingFactorDest bfd)
			=> bfd switch
			{
				BlendingFactorDest.Zero => BlendFactor.Zero,
				BlendingFactorDest.One => BlendFactor.One,
				BlendingFactorDest.SrcColor => BlendFactor.SourceColor,
				BlendingFactorDest.OneMinusSrcColor => BlendFactor.InverseSourceColor,
				BlendingFactorDest.SrcAlpha => BlendFactor.SourceAlpha,
				BlendingFactorDest.OneMinusSrcAlpha => BlendFactor.InverseSourceAlpha,
				BlendingFactorDest.DstAlpha => BlendFactor.DestinationAlpha,
				BlendingFactorDest.OneMinusDstAlpha => BlendFactor.InverseDestinationAlpha,
				BlendingFactorDest.DstColor => BlendFactor.DestinationColor,
				BlendingFactorDest.OneMinusDstColor => BlendFactor.InverseDestinationColor,
				BlendingFactorDest.SrcAlphaSaturate => throw new NotSupportedException(),
				BlendingFactorDest.ConstantColor => BlendFactor.BlendFactor,
				BlendingFactorDest.OneMinusConstantColor => BlendFactor.InverseBlendFactor,
				BlendingFactorDest.ConstantAlpha => throw new NotSupportedException(),
				BlendingFactorDest.OneMinusConstantAlpha => throw new NotSupportedException(),
				BlendingFactorDest.Src1Alpha => throw new NotSupportedException(),
				BlendingFactorDest.Src1Color => throw new NotSupportedException(),
				BlendingFactorDest.OneMinusSrc1Color => throw new NotSupportedException(),
				BlendingFactorDest.OneMinusSrc1Alpha => throw new NotSupportedException(),
				_ => throw new InvalidOperationException(),
			};

		public static BlendFunction ConvertToVeldrid(this BlendEquationMode bem)
			=> bem switch
			{
				BlendEquationMode.FuncAdd => BlendFunction.Add,
				BlendEquationMode.Min => BlendFunction.Minimum,
				BlendEquationMode.Max => BlendFunction.Maximum,
				BlendEquationMode.FuncSubtract => BlendFunction.Subtract,
				BlendEquationMode.FuncReverseSubtract => BlendFunction.ReverseSubtract,
				_ => throw new InvalidOperationException(),
			};
	}
}