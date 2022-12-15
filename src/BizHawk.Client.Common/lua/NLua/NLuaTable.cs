using System.Collections;

using NLua;

namespace BizHawk.Client.Common
{
	public readonly struct NLuaTable : ILuaTable
	{
		private readonly LuaTable _table;

		public NLuaTable(NLuaEngine lua)
		{
			lua.NewTable("__BIZHAWK_INTERNAL_TEMP_TABLE");
			_table = (LuaTable)lua["__BIZHAWK_INTERNAL_TEMP_TABLE"];
			lua["__BIZHAWK_INTERNAL_TEMP_TABLE"] = null;
		}

		public NLuaTable(LuaTable table)
			=> _table = table;

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

		public int Count => _table.Keys.Count;

		public IEnumerable Keys => _table.Keys;

		public IEnumerable Values => _table.Values;

		public object RawTable => _table;
	}
}
