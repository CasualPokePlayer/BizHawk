using System.Collections;

namespace BizHawk.Client.Common
{
	// TODO: Return an IDictionary<object, object> instead of Count/Keys/Values?
	public interface ILuaTable
	{
		/// <summary>
		/// Access the table by key name
		/// </summary>
		/// <param name="field">key name</param>
		/// <returns>value for key, or null if it does not exist</returns>
		object this[string field] { get; set; }

		/// <summary>
		/// Access the table by key object
		/// </summary>
		/// <param name="field">key object</param>
		/// <returns>value for key, or null if it does not exist</returns>
		object this[object field] { get; set; }

		/// <summary>
		/// Number of elements in the Lua table
		/// </summary>
		int Count { get; }

		/// <summary>
		/// Keys of the Lua table
		/// </summary>
		IEnumerable Keys { get; }

		/// <summary>
		/// Values of the Lua table
		/// </summary>
		IEnumerable Values { get; }

		/// <summary>
		/// Raw Lua engine defined table, should not be used directly by user code
		/// </summary>
		object RawTable { get; }
	}
}
