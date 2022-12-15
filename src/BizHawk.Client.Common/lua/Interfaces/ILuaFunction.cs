namespace BizHawk.Client.Common
{
	public interface ILuaFunction
	{
		/// <summary>
		/// Raw Lua engine defined function, should not be used directly by user code
		/// </summary>
		public object RawFunction { get; }

		/// <summary>
		/// Invoke the Lua function with args. Under the current implemention, this does not return a value
		/// TODO: Maybe we'll want to return the value from the function call?
		/// </summary>
		/// <param name="args">Arguments for the lua function, may be omitted</param>
		public object[] Invoke(params object[] args);
	}
}
