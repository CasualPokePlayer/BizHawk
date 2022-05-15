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
			int sz = 0;
			IntPtr buf = _core.Dolphin_SaveState(ref sz);
			if (sz > _stateBuf.Length)
			{
				_stateBuf = new byte[sz];
			}
			Marshal.Copy(buf, _stateBuf, 0, sz);

			writer.Write(sz);
			writer.Write(_stateBuf, 0, sz);

			// other variables
			writer.Write(IsLagFrame);
			writer.Write(LagCount);
			writer.Write(Frame);
		}

		public void LoadStateBinary(BinaryReader reader)
		{
			int len = reader.ReadInt32();
			if (len > _stateBuf.Length)
			{
				_stateBuf = new byte[len];
			}

			reader.Read(_stateBuf, 0, len);

			_core.Dolphin_LoadState(_stateBuf, len);

			// other variables
			IsLagFrame = reader.ReadBoolean();
			LagCount = reader.ReadInt32();
			Frame = reader.ReadInt32();
		}
	}
}
