using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Collections.Generic;
using System.Reflection;

using Newtonsoft.Json;

using BizHawk.Common;
using BizHawk.Emulation.Common;

namespace BizHawk.Emulation.Cores.Nintendo.Dolphin
{
	public partial class Dolphin : ISettable<object, Dolphin.DolphinSyncSettings>
	{
		private DolphinSyncSettings _syncSettings;

		public object GetSettings() => null;

		public PutSettingsDirtyBits PutSettings(object o) => PutSettingsDirtyBits.None;

		public DolphinSyncSettings GetSyncSettings() => _syncSettings.Clone();

		public PutSettingsDirtyBits PutSyncSettings(DolphinSyncSettings o)
		{
			bool ret = DolphinSyncSettings.NeedsReboot(_syncSettings, o);
			_syncSettings = o;
			return ret ? PutSettingsDirtyBits.RebootCore : PutSettingsDirtyBits.None;
		}

		public class DolphinSyncSettings
		{
			public DolphinMainSettings MainSettings { get; set; }
			/*
				{System::Main, "Dolphin"},
				{System::GCPad, "GCPad"},
				{System::WiiPad, "Wiimote"},
				{System::GCKeyboard, "GCKeyboard"},
				{System::GFX, "Graphics"},
				{System::Logger, "Logger"},
				{System::Debugger, "Debugger"},
				{System::SYSCONF, "SYSCONF"},
				{System::DualShockUDPClient, "DualShockUDPClient"},
				{System::FreeLook, "FreeLook"},
				{System::Session, "Session"}};
			 */

			public DolphinSyncSettings()
			{
				MainSettings = new();
			}

			public void ApplyNativeSettings(List<string> config)
			{
				MainSettings.ApplyNativeSettings(config);
			}

			public DolphinSyncSettings Clone() => MemberwiseClone() as DolphinSyncSettings;

			public static bool NeedsReboot(DolphinSyncSettings x, DolphinSyncSettings y) => !DeepEquality.DeepEquals(x, y);
		}

		public abstract class DolphinNativeSettings
		{
			protected abstract string NativeName { get; }

			private static bool IsBrowsable(PropertyInfo prop)
			{
				var brAttr = prop.GetCustomAttribute<BrowsableAttribute>();
				return brAttr?.Browsable ?? throw new Exception("Could not determine if setting should be browsable!");
			}

			private static object GetDefaultValue(PropertyInfo prop)
			{
				var dvAttr = prop.GetCustomAttribute<DefaultValueAttribute>();
				return dvAttr?.Value ?? throw new Exception("Could not find default value!");
			}

			private static string GetCategoryName(PropertyInfo prop)
			{
				var cAttr = prop.GetCustomAttribute<CategoryAttribute>();
				return cAttr?.Category ?? throw new Exception("Could not find category name!");
			}

			private static object MaybeGetDisplayName(object s, PropertyInfo prop)
			{
				var c = prop.GetCustomAttribute<TypeConverterAttribute>();
				if (Type.GetType(c.ConverterTypeName) == typeof(DescribableEnumConverter))
				{
					// use display names here
					var converter = new DescribableEnumConverter(s.GetType());
					return converter.ConvertTo(null, null, s, null);
				}
				else
				{
					// just return the raw value
					return (int)s;
				}
			}

			private static string ToNativeConfigString(object s, PropertyInfo prop)
			{
				var t = s.GetType();
				if (t == typeof(bool))
				{
					var b = (bool)s;
					return b.ToString();
				}
				else if (t == typeof(int))
				{
					var i = (int)s;
					return i.ToString();
				}
				else if (t == typeof(string))
				{
					return (string)s;
				}
				else if (t.IsEnum)
				{
					if (Enum.GetUnderlyingType(s.GetType()) != typeof(int))
					{
						throw new Exception("Enums must be ints!");
					}

					var n = MaybeGetDisplayName(s, prop);
					if (n.GetType() == typeof(string))
					{
						return (string)n;
					}
					else if (n.GetType() == typeof(int))
					{
						var i = (int)n;
						return i.ToString();
					}
				}

				throw new Exception("Could not determine native config string!");
			}

			public void ApplyNativeSettings(List<string> config)
			{
				foreach (var prop in this.GetType().GetProperties())
				{
					// ensure settings which cannot be browsed have their defaults set
					if (prop.CanWrite && !IsBrowsable(prop))
					{
						prop.SetValue(this, GetDefaultValue(prop));
					}

					if (prop.CanRead)
					{
						config.Add($"--config={NativeName}.{GetCategoryName(prop)}.{prop.Name}={ToNativeConfigString(prop.GetValue(this), prop)}");
					}
				}
			}
 		}

		public class DolphinMainSettings : DolphinNativeSettings
		{
			protected override string NativeName => "Dolphin";

			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool CPUThread { get; set; }

			[Category("Core")]
			[DefaultValue(0)]
			[Browsable(false)]
			public int EmulationSpeed { get; set; }

			public enum DSPBackends
			{
				[Display(Name = "No Audio Output")]
				NoAudioOutput = 0,
			}

			[Category("DSP")]
			[DefaultValue(DSPBackends.NoAudioOutput)]
			[TypeConverter(typeof(DescribableEnumConverter))]
			[Browsable(false)]
			public DSPBackends Backend { get; set; }
		}
	}
}
