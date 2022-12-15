using System;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;

using Neo.IronLua;

namespace BizHawk.Client.Common
{
	public sealed class NeoLuaEngine : ILuaEngine
	{
		private readonly Lua _lua;
		private readonly LuaGlobal _g;

		public NeoLuaEngine()
		{
			_lua = new(LuaIntegerType.Int64, LuaFloatType.Double);
			_g = _lua.CreateEnvironment();
			_g.DefaultCompileOptions = new()
			{
				ClrEnabled = false,
			};
		}

		public object this[string field]
		{
			get => _g[field];
			set => _g[field] = value;
		}

		public string Name => "NLua+KeraLua+Lua";

		public void Dispose()
			=> _lua.Dispose();

		public void DoString(string chunk)
			=> _g.DoChunk(chunk, "chunk");

		public void NewTable(string path)
			=> _g[path] = new LuaTable();

		public ILuaThread NewThread()
			=> new NeoLuaThread(null, null);

		public ILuaThread NewThread(string chunk)
		{
			var main = _lua.CompileChunk(chunk, "main", _g.DefaultCompileOptions);
			return new NeoLuaThread(main, _g);
		}

		private static Delegate CreateDelegate(object target, MethodInfo method)
		{
			var typeArgs = method
				.GetParameters()
				.Select(p => p.ParameterType)
				.Concat(new[] { method.ReturnType })
				.ToArray();

			var delT = Expression.GetDelegateType(typeArgs);

			return method.IsStatic
				? Delegate.CreateDelegate(delT, method)
				: Delegate.CreateDelegate(delT, target, method.Name);
		}

		public object CreateFunction(string name, object target, MethodInfo method)
			=> CreateDelegate(target, method);

		public void RegisterFunction(string name, object target, MethodInfo method)
		{
			var del = CreateDelegate(target, method);
			_g.DefineFunction(name, del);
		}

		public void RegisterFunction(string table, string name, object target, MethodInfo method)
		{
			var del = CreateDelegate(target, method);
			var t = (LuaTable)_g[table];
			t.DefineFunction(name, del);
		}
	}
}
