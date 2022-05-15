using System;
using System.Runtime.InteropServices;

using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public partial class Dolphin : ISoundProvider
	{
		private short[] _sampleBuf = new short[1024 * 2];
		private int _nsamps = 0;

		private void ProcessSound()
		{
			IntPtr data = IntPtr.Zero;
			int sz = 0;
			_core.Dolphin_GetAudio(ref data, ref sz);
			if (sz > _sampleBuf.Length)
			{
				_sampleBuf = new short[sz];
			}
			Marshal.Copy(data, _sampleBuf, 0, sz);
			_nsamps = sz / 2;
		}

		public bool CanProvideAsync => false;

		public SyncSoundMode SyncMode => SyncSoundMode.Sync;

		public void DiscardSamples()
		{
			_nsamps = 0;
		}

		public void GetSamplesAsync(short[] samples)
		{
			throw new NotSupportedException("Aync mode is not supported");
		}

		public void GetSamplesSync(out short[] samples, out int nsamp)
		{
			samples = _sampleBuf;
			nsamp = _nsamps;
			DiscardSamples();
		}

		public void SetSyncMode(SyncSoundMode mode)
		{
			if (mode == SyncSoundMode.Async)
			{
				throw new NotSupportedException("Aync mode is not supported");
			}
		}
	}
}
