using System;

using Neo.IronLua;

namespace BizHawk.Client.Common
{
	public sealed class NeoLuaThread : ILuaThread
	{
		private readonly LuaChunk _chunk;
		private readonly LuaGlobal _env;
		private readonly Action _threadProc;
		private readonly LuaThread _thread;
		private Exception _ex;

		private void ThreadProc()
		{
			try
			{
				_chunk.Run(_env);
			}
			catch (Exception ex)
			{
				_ex = ex;
				Yield();
			}
		}

		public NeoLuaThread(LuaChunk chunk, LuaGlobal env)
		{
			_chunk = chunk;
			_env = env;
			_threadProc = ThreadProc;
			_thread = new(_threadProc);
		}

		public void Dispose()
			=> _thread.Dispose();

		public bool Resume()
		{
			_thread.resume(null);
			return false;

			if (_ex is not null)
			{
				throw _ex;
			}

			return _thread.Status switch
			{
				LuaThreadStatus.Normal => false,
				LuaThreadStatus.Suspended => true,
				LuaThreadStatus.Dead => throw new InvalidOperationException("LuaThread died!"),
				_ => throw new InvalidOperationException()
			};
		}

		public void Yield()
			=> LuaThread.yield(null);
	}
}