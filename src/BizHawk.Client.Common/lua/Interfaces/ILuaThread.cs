using System;

namespace BizHawk.Client.Common
{
	public interface ILuaThread : IDisposable
	{
		/// <summary>
		/// Resume the thread
		/// </summary>
		/// <returns>true if thread has yielded, false otherwise</returns>
		public bool Resume();

		/// <summary>
		/// Yield the thread
		/// </summary>
		public void Yield();
	}
}
