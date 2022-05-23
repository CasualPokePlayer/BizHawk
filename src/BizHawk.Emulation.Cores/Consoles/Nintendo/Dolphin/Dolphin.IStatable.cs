using System;
using System.IO;
using System.Runtime.InteropServices;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public partial class Dolphin : IStatable
	{
		private byte[] _stateBuf = new byte[0];

		public void SaveStateBinary(BinaryWriter writer)
		{
			bool compressed = _settings.UseCompressedStates;
			int sz = _core.Dolphin_StateSize(compressed);
			if (sz > _stateBuf.Length)
			{
				_stateBuf = new byte[sz];
			}
			_core.Dolphin_SaveState(_stateBuf, sz, compressed);

			writer.Write(compressed);
			writer.Write(sz);
			writer.Write(_stateBuf, 0, sz);

			// other variables
			writer.Write(IsLagFrame);
			writer.Write(LagCount);
			writer.Write(Frame);
		}

		public void LoadStateBinary(BinaryReader reader)
		{
			bool compressed = reader.ReadBoolean();
			int len = reader.ReadInt32();
			if (len > _stateBuf.Length)
			{
				_stateBuf = new byte[len];
			}

			reader.Read(_stateBuf, 0, len);
			_core.Dolphin_LoadState(_stateBuf, len, compressed);

			// other variables
			IsLagFrame = reader.ReadBoolean();
			LagCount = reader.ReadInt32();
			Frame = reader.ReadInt32();
		}
	}
}
