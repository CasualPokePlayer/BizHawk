using System.Reflection;
using System.Text;

using NLua;

namespace BizHawk.Client.Common
{
	public sealed class NLuaEngine : ILuaEngine
	{
		private readonly Lua _lua;

		public NLuaEngine()
		{
			_lua = new();
			_lua.State.Encoding = Encoding.UTF8;
		}

		public object this[string field]
		{
			get => _lua[field];
			set => _lua[field] = value;
		}

		public string Name => "NLua+KeraLua+Lua";

		public void Dispose()
			=> _lua.Dispose();

		public void DoString(string chunk)
			=> _lua.DoString(chunk);

		public void NewTable(string path)
			=> _lua.NewTable(path);

		public ILuaThread NewThread()
		{
			_lua.NewThread(out var thread);
			return new NLuaThread(thread);
		}

		public ILuaThread NewThread(string chunk)
		{
			var main = _lua.LoadString(chunk, "main");
			_lua.NewThread(main, out var thread);
			return new NLuaThread(thread);
		}

		public object CreateFunction(string name, object target, MethodInfo method)
			=> _lua.RegisterFunction(name, target, method);

		public void RegisterFunction(string name, object target, MethodInfo method)
			=> _lua.RegisterFunction(name, target, method);

		public void RegisterFunction(string table, string name, object target, MethodInfo method)
			=> _lua.RegisterFunction($"{table}.{name}", target, method);
	}
}
