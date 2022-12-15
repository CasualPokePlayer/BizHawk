using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Linq;

using BizHawk.Common;

namespace BizHawk.Client.Common
{
	public sealed class LuaTableHelper
	{
		private readonly ILuaEngine _lua;
		private readonly Action<string> _logCallback;

		public LuaTableHelper(ILuaEngine lua, Action<string> logCallback)
		{
			_lua = lua;
			_logCallback = logCallback;
		}

		public ILuaTable CreateTable()
			=> _lua switch
			{
				NLuaEngine nlua => new NLuaTable(nlua),
				NeoLuaEngine => new NeoLuaTable(null),
				_ => throw new InvalidOperationException()
			};

		public object DictToTable<T>(IReadOnlyDictionary<string, T> dictionary)
		{
			var table = CreateTable();
			foreach (var (k, v) in dictionary) table[k] = v;
			return table.RawTable;
		}

		public IEnumerable<(TKey Key, TValue Value)> EnumerateEntries<TKey, TValue>(object table)
		{
			var t = ParseTable(table);
			return t.Keys.Cast<TKey>().Select(k => (k, (TValue) t[k]));
		}

		public IEnumerable<T> EnumerateValues<T>(object table)
			=> ParseTable(table).Values.Cast<T>();

		public object ListToTable<T>(IReadOnlyList<T> list, int indexFrom = 1)
		{
			var table = CreateTable();
			for (int i = 0, l = list.Count; i != l; i++) table[indexFrom + i] = list[i];
			return table.RawTable;
		}

		public object MemoryBlockToTable(IReadOnlyList<byte> bytes, long startAddr)
		{
			var length = bytes.Count;
			var table = CreateTable();
			var iArray = 0;
			var iDict = startAddr;
			while (iArray < length) table[iDict++] = bytes[iArray++];
			return table;
		}

		public object ObjectToTable(object obj)
		{
			var table = CreateTable();
			foreach (var method in obj.GetType().GetMethods())
			{
				if (!method.IsPublic) continue;
				var foundAttrs = method.GetCustomAttributes(typeof(LuaMethodAttribute), false);
				table[method.Name] = _lua.CreateFunction(
					foundAttrs.Length == 0 ? string.Empty : ((LuaMethodAttribute) foundAttrs[0]).Name, // empty string will default to the actual method name
					obj,
					method
				);
			}
			return table;
		}

		public Color ParseColor(object o) => ParseColor(o, safe: false, _logCallback) ?? throw new ArgumentException("failed to parse Color", nameof(o));

		public Color? SafeParseColor(object o) => ParseColor(o, safe: true, _logCallback);

		private static Color? ParseColor(object o, bool safe, Action<string> logCallback)
		{
			switch (o)
			{
				case null:
					return null;
				case Color c:
					return c;
				case double d:
					return ParseColor((int) (long) d, safe, logCallback);
				case int i:
					return Color.FromArgb(i);
				case uint u:
					return Color.FromArgb((int)u);
				case long l:
					return Color.FromArgb((int)l);
				case string s:
					if (s[0] is '#' && (s.Length is 7 or 9))
					{
						var i1 = uint.Parse(s.Substring(1), NumberStyles.HexNumber);
						if (s.Length is 7) i1 |= 0xFF000000U;
						return ParseColor(unchecked((int) i1), safe, logCallback);
					}
					var fromName = Color.FromName(s);
					if (fromName.IsNamedColor) return fromName;
					if (safe) logCallback($"ParseColor: not a known color name (\"{s}\")");
					return null;
				default:
					if (safe) logCallback("ParseColor: coercing object/table to string");
					return ParseColor(o.ToString(), safe, logCallback);
			}
		}

		public static ILuaFunction ParseFunction(object func)
			=> func switch
			{
				NLua.LuaFunction f => new NLuaFunction(f),
				Delegate d => new NeoLuaFunction(d),
				_ => throw new InvalidOperationException($"param {nameof(func)} is not a valid lua function!")
			};

		public static ILuaTable ParseTable(object table)
			=> table switch
			{
				NLua.LuaTable t => new NLuaTable(t),
				Neo.IronLua.LuaTable t => new NeoLuaTable(t),
				_ => throw new InvalidOperationException($"param {nameof(table)} is not a valid lua table!")
			};
	}
}
