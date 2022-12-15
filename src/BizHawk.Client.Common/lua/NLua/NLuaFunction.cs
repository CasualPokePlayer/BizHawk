using NLua;

namespace BizHawk.Client.Common
{
	public readonly struct NLuaFunction : ILuaFunction
	{
		private readonly LuaFunction _func;

		public NLuaFunction(LuaFunction func)
			=> _func = func;

		public object[] Invoke(params object[] args)
			=> _func.Call(args);

		public object RawFunction => _func;
	}
}
