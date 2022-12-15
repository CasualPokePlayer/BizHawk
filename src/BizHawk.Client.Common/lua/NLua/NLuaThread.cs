using System;

using KeraLua;
using NLua;

namespace BizHawk.Client.Common
{
	public sealed class NLuaThread : ILuaThread
	{
		private readonly LuaThread _thread;

		public NLuaThread(LuaThread thread)
			=> _thread = thread;

		public void Dispose()
			=> _thread.Dispose();

		public bool Resume()
		{
			var execResult = _thread.Resume();
			return execResult switch
			{
				LuaStatus.OK => false,
				LuaStatus.Yield => true,
				_ => throw new InvalidOperationException($"{nameof(_thread.Resume)}() returned {execResult}?")
			};
		}

		public void Yield()
			=> _thread.Yield();
	}
}
