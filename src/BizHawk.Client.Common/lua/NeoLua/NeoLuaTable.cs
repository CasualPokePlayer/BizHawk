using System.Collections;
using Neo.IronLua;

namespace BizHawk.Client.Common
{
	public readonly struct NeoLuaTable : ILuaTable
	{
		private readonly LuaTable _table;

		public NeoLuaTable(LuaTable table)
			=> _table = table ?? new();

		public object this[string field]
		{
			get => _table[field];
			set => _table[field] = value;
		}

		public object this[object field]
		{
			get => _table[field];
			set => _table[field] = value;
		}

		public int Count => _table.Values.Count;

		public IEnumerable Keys => _table.Values.Keys;

		public IEnumerable Values => _table.Values.Values;

		public object RawTable => _table;
	}
}
