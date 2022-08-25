using System;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.ThreeDSVC
{
	public partial class ThreeDSVC : ISaveRam
	{
		public bool SaveRamModified
			=> _core.VC_SramDirty() != 0;

		public byte[] CloneSaveRam()
		{
			int length = _core.VC_SramLength();

			if (length > 0)
			{
				byte[] ret = new byte[length];
				_core.VC_SaveSram(ret);
				return ret;
			}

			return null;
		}

		public void StoreSaveRam(byte[] data)
		{
			int expected = _core.VC_SramLength();
			if (data.Length != expected) throw new ArgumentException(message: "Size of saveram data does not match expected!", paramName: nameof(data));

			if (expected > 0)
			{
				_core.VC_LoadSram(data);
			}
		}
	}
}
