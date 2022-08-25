using System;
using System.IO;

using Newtonsoft.Json;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public partial class ThreeDSVC : IStatable, ITextStatable
	{
		private readonly byte[] _stateBuf;

		public void SaveStateBinary(BinaryWriter writer)
		{
			if (!_core.VC_SaveStateBinary(_stateBuf, _stateBuf.Length))
			{
				throw new Exception($"{nameof(_core.VC_SaveStateBinary)}() returned false");
			}

			writer.Write(_stateBuf.Length);
			writer.Write(_stateBuf);

			// other variables
			writer.Write(IsLagFrame);
			writer.Write(LagCount);
			writer.Write(Frame);
			writer.Write(IsCgb);
		}

		public void LoadStateBinary(BinaryReader reader)
		{
			int length = reader.ReadInt32();
			if (length != _stateBuf.Length)
			{
				throw new InvalidOperationException("Savestate buffer size mismatch!");
			}

			reader.Read(_stateBuf, 0, _stateBuf.Length);

			if (!_core.VC_LoadStateBinary(_stateBuf, _stateBuf.Length))
			{
				throw new Exception($"{nameof(_core.VC_LoadStateBinary)}() returned false");
			}

			// other variables
			IsLagFrame = reader.ReadBoolean();
			LagCount = reader.ReadInt32();
			Frame = reader.ReadInt32();
			IsCgb = reader.ReadBoolean();
		}

		private readonly JsonSerializer ser = new() { Formatting = Formatting.Indented };

		// other data in the text state besides core
		private class TextStateData
		{
			public int Frame;
			public int LagCount;
			public bool IsLagFrame;
			public bool IsCgb;
		}

		public void SaveStateText(TextWriter writer)
		{
			var s = new TextState<TextStateData>();
			s.Prepare();
			var ff = s.GetFunctionPointersSave();
			_core.VC_SaveStateText(ref ff);
			s.ExtraData.IsLagFrame = IsLagFrame;
			s.ExtraData.LagCount = LagCount;
			s.ExtraData.Frame = Frame;
			s.ExtraData.IsCgb = IsCgb;
			ser.Serialize(writer, s);
		}

		public void LoadStateText(TextReader reader)
		{
			var s = (TextState<TextStateData>)ser.Deserialize(reader, typeof(TextState<TextStateData>));
			s.Prepare();
			var ff = s.GetFunctionPointersLoad();
			_core.VC_LoadStateText(ref ff);
			IsLagFrame = s.ExtraData.IsLagFrame;
			LagCount = s.ExtraData.LagCount;
			Frame = s.ExtraData.Frame;
			IsCgb = s.ExtraData.IsCgb;
			reader.ReadToEnd();
		}
	}
}
