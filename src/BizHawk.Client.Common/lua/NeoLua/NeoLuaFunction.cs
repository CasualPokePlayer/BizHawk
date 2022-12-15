using System;

using Neo.IronLua;

namespace BizHawk.Client.Common
{
	public readonly struct NeoLuaFunction : ILuaFunction
	{
		private readonly Delegate _func;

		public NeoLuaFunction(Delegate func)
			=> _func = func;

		public object[] Invoke(params object[] args)
			=> new LuaResult(Lua.RtInvoke(_func, args)).Values;

		public object RawFunction => _func;
	}
}
