using System;
using System.Reflection;

namespace BizHawk.Client.Common
{
	public interface ILuaEngine : IDisposable
	{
		string Name { get; }

		object this[string field] { get; set; }

		ILuaThread NewThread();

		ILuaThread NewThread(string chunk);

		void DoString(string chunk);

		void NewTable(string path);

		object CreateFunction(string name, object target, MethodInfo method);

		void RegisterFunction(string name, object target, MethodInfo method);

		void RegisterFunction(string table, string name, object target, MethodInfo method);
	}
}
