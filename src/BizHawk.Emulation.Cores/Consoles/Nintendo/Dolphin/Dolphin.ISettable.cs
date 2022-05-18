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

		public void ApplyNativeSettings(List<string> config)
		{
			var ss = _syncSettings.Clone();
			ss.MainSettings.EnableCustomRTC = DeterministicEmulation;
			ss.MainSettings.ApplyNativeSettings(config);
			ss.WiiPadSettings.ApplyNativeSettings(config);
			ss.GFXSettings.ApplyNativeSettings(config);
			ss.SYSCONFSettings.ApplyNativeSettings(config);
		}

		public class DolphinSyncSettings
		{
			public DolphinMainSettings MainSettings { get; set; }
			public DolphinWiiPadSettings WiiPadSettings { get; set; }
			public DolphinGFXSettings GFXSettings { get; set; }
			public DolphinSYSCONFSettings SYSCONFSettings { get; set; }
			public bool ApplyPerGameSettings { get; set; }

			public DolphinSyncSettings()
			{
				MainSettings = new();
				WiiPadSettings = new();
				GFXSettings = new();
				SYSCONFSettings = new();
				ApplyPerGameSettings = true;
			}

			public DolphinSyncSettings Clone() => MemberwiseClone() as DolphinSyncSettings;

			public static bool NeedsReboot(DolphinSyncSettings x, DolphinSyncSettings y)
			{
				return x.ApplyPerGameSettings != y.ApplyPerGameSettings
				|| !DeepEquality.DeepEquals(x.MainSettings, y.MainSettings)
				|| !DeepEquality.DeepEquals(x.WiiPadSettings, y.WiiPadSettings)
				|| !DeepEquality.DeepEquals(x.GFXSettings, y.GFXSettings)
				|| !DeepEquality.DeepEquals(x.SYSCONFSettings, y.SYSCONFSettings);
			}
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
				if (c is not null) // must be DescribableEnumConverter
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

			private static readonly DateTime _unixEpoch = new(1970, 1, 1, 0, 0, 0);

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
				else if (t == typeof(float))
				{
					var f = (float)s;
					return f.ToString();
				}
				else if (t == typeof(DateTime))
				{
					var d = (DateTime)s;
					return ((uint)(d - _unixEpoch).TotalSeconds).ToString();
				}
				else if (t == typeof(string))
				{
					return (string)s;
				}
				else if (t.IsEnum)
				{
					if (Enum.GetUnderlyingType(t) != typeof(int))
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

			public DolphinMainSettings()
			{
				SettingsUtil.SetDefaultValues(this);
			}

			[DisplayName("Skip IPL")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool SkipIPL { get; set; }

			public enum CPUCores : int
			{
				Interpreter = 0,
				JIT64 = 1,
				// we don't support ARM
				CachedInterpreter = 5,
			}

			[DisplayName("CPU Core")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(CPUCores.JIT64)]
			[Browsable(true)]
			public CPUCores CPUCore { get; set; }

			[DisplayName("JIT Follow Branch")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool JITFollowBranch { get; set; }

			[DisplayName("Fast Mem")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool Fastmem { get; set; }

			[DisplayName("DSP HLE")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool DSPHLE { get; set; }

			[DisplayName("Timing Variance")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(40)]
			[Browsable(false)]
			public int TimingVariance { get; set; }

			[DisplayName("CPU Thread")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool CPUThread { get; set; }

			[DisplayName("Sync On Skip Idle")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool SyncOnSkipIdle { get; set; }

			public enum GCLanguages : int
			{
				English = 0,
				German = 1,
				French = 2,
				Spanish = 3,
				Italian = 4,
				Dutch = 5,
				Unknown,
			}

			[DisplayName("Selected Language")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(GCLanguages.English)]
			[Browsable(true)]
			public GCLanguages SelectedLanguage { get; set; }

			[DisplayName("Override Region Settings")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool OverrideRegionSettings { get; set; }

			[DisplayName("DPL2 Decoder")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool DPL2Decoder { get; set; }

			public enum DPL2Qualitys : int
			{
				Lowest = 0,
				Low = 1,
				High = 2,
				Highest = 3,
			}

			[DisplayName("DPL2 Quality")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(DPL2Qualitys.High)]
			[Browsable(true)]
			public DPL2Qualitys DPL2Quality { get; set; }

			public enum MemoryCardSizes : int
			{
				OneHundredTwentyEightMBit = -1,
				FourMBit = 0,
				EightMBit = 1,
				SixteenMBit = 2,
				ThiryTwoMBit = 3,
				SixtyFourMBit = 4,
			}

			[DisplayName("Memory Card Size")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(MemoryCardSizes.OneHundredTwentyEightMBit)]
			[Browsable(true)]
			public MemoryCardSizes MemoryCardSize { get; set; }

			public enum EXIDeviceType : int
			{
				Dummy = 0,
				MemoryCardFolder = 8,
				None = 0xFF,
			}

			[DisplayName("Slot A")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(EXIDeviceType.MemoryCardFolder)]
			[Browsable(true)]
			public EXIDeviceType SlotA { get; set; }

			[DisplayName("Slot B")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(EXIDeviceType.None)]
			[Browsable(true)]
			public EXIDeviceType SlotB { get; set; }

			public enum EXIDeviceTypeSP1 : int
			{
				Dummy = 0,
				None = 0xFF,
			}

			[DisplayName("Serial Port 1")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(EXIDeviceTypeSP1.None)]
			[Browsable(true)]
			public EXIDeviceTypeSP1 SerialPort1 { get; set; }

			public enum SIDevices
			{
				None = 0,
				Controller = 6,
				// todo
				/*SteeringWheel = 8,
				DanceMat = 9,
				TaruKonga = 10,*/
			}

			[DisplayName("SI Device 0")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(SIDevices.Controller)]
			[Browsable(true)]
			public SIDevices SIDevice0 { get; set; }

			[DisplayName("SI Device 1")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(SIDevices.None)]
			[Browsable(true)]
			public SIDevices SIDevice1 { get; set; }

			[DisplayName("SI Device 2")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(SIDevices.None)]
			[Browsable(true)]
			public SIDevices SIDevice2 { get; set; }

			[DisplayName("SI Device 3")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(SIDevices.None)]
			[Browsable(true)]
			public SIDevices SIDevice3 { get; set; }

			[DisplayName("Wii SD Card")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool WiiSDCard { get; set; }

			[DisplayName("Wii Keyboard")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool WiiKeyboard { get; set; }

			[DisplayName("Wiimote Enable Speaker")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool WiimoteEnableSpeaker { get; set; }

			[DisplayName("MMU")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool MMU { get; set; }

			[DisplayName("BB Dump Port")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(-1)]
			[Browsable(false)]
			public int BBDumpPort { get; set; }

			[DisplayName("Sync GPU")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(true)]
			[Browsable(false)]
			public bool SyncGPU { get; set; }

			[DisplayName("Sync Gpu Max Distance")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(200000)]
			[Browsable(false)]
			public int SyncGpuMaxDistance { get; set; }

			[DisplayName("Sync Gpu Min Distance")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(-200000)]
			[Browsable(false)]
			public int SyncGpuMixDistance { get; set; }

			[DisplayName("Sync Gpu Overclock")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(1.0f)]
			[Browsable(false)]
			public float SyncGpuOverclock { get; set; }

			[DisplayName("Fast Disc Speed")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool FastDiscSpeed { get; set; }

			[DisplayName("Low DCBZ Hack")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool LowDCBZHack { get; set; }

			[DisplayName("Float Exceptions")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool FloatExceptions { get; set; }

			[DisplayName("Div By Zero Exceptions")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool DivByZeroExceptions { get; set; }

			[DisplayName("FPRF")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool FPRF { get; set; }

			[DisplayName("Accurate NaNs")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool AccurateNaNs { get; set; }

			[DisplayName("Disable ICache")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool DisableICache { get; set; }

			[DisplayName("Emulation Speed")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(0.0f)]
			[Browsable(false)]
			public float EmulationSpeed { get; set; }

			[DisplayName("Overclock")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(1.0f)]
			[Browsable(false)]
			public float Overclock { get; set; }

			[DisplayName("Overclock Enable")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool OverclockEnable { get; set; }

			[DisplayName("RAM Override Enable")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool RAMOverrideEnable { get; set; }

			[DisplayName("MEM1 Size")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(0x01800000)]
			[Browsable(false)]
			public int MEM1Size { get; set; }

			[DisplayName("MEM2 Size")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(0x04000000)]
			[Browsable(false)]
			public int MEM2Size { get; set; }

			public enum GFXBackends : int
			{
				//[Display(Name = "OGL")]
				//OGL = 0,
				// can't use OGL here
				[Display(Name = "D3D")]
				D3D11 = 1,
				[Display(Name = "D3D12")]
				D3D12 = 2,
				[Display(Name = "Vulkan")]
				Vulkan = 3,
				//[Display(Name = "Software Renderer")]
				//SoftwareRenderer = 4,
				//software renderer needs OGL so...
				[Display(Name = "Null")]
				Null = 5,
			}

			[DisplayName("GFX Backend")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(GFXBackends.Vulkan)]
			[TypeConverter(typeof(DescribableEnumConverter))]
			[Browsable(true)]
			public GFXBackends GFXBackend { get; set; }

			public enum GPUDeterminismModes : int
			{
				[Display(Name = "fake-completion")]
				FakeCompletion = 2,
			}

			[DisplayName("GPU Determinism Mode")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(GPUDeterminismModes.FakeCompletion)]
			[TypeConverter(typeof(DescribableEnumConverter))]
			[Browsable(false)]
			public GPUDeterminismModes GPUDeterminismMode { get; set; }

			[DisplayName("Override Boot IOS")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(-1)]
			[Browsable(false)]
			public int OverrideBootIOS { get; set; }

			[DisplayName("Enable Custom RTC")]
			[Description("Forced true when recording a movie.")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool EnableCustomRTC { get; set; }

			[DisplayName("Custom RTC Value")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(typeof(DateTime), "2010-01-01")]
			[TypeConverter(typeof(BizDateTimeConverter))]
			[Browsable(true)]
			public DateTime CustomRTCValue { get; set; }

			public enum Regions
			{
				NTSC_J = 0,
				NTSC_U = 1,
				PAL = 2,
				Unknown = 3,
				NTSC_K = 4,
			}

			[DisplayName("Fallback Region")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(Regions.NTSC_U)]
			[Browsable(true)]
			public Regions FallbackRegion { get; set; }

			[DisplayName("Auto Disc Change")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool AutoDiscChange { get; set; }

			[DisplayName("Wii SD Card Allow Writes")]
			[Description("")]
			[Category("Core")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool WiiSDCardAllowWrites { get; set; }

			[DisplayName("DSP Thread")]
			[Description("")]
			[Category("DSP")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool DSPThread { get; set; }

			[DisplayName("Enable JIT")]
			[Description("")]
			[Category("DSP")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool EnableJIT { get; set; }

			public enum DSPBackends : int
			{
				[Display(Name = "No Audio Output")]
				NoAudioOutput = 0,
			}

			[DisplayName("Backend")]
			[Description("")]
			[Category("DSP")]
			[DefaultValue(DSPBackends.NoAudioOutput)]
			[TypeConverter(typeof(DescribableEnumConverter))]
			[Browsable(false)]
			public DSPBackends Backend { get; set; }

			[DisplayName("Use Panic Handlers")]
			[Description("")]
			[Category("Interface")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool UsePanicHandlers { get; set; }

			[DisplayName("Abort On Panic Alert")]
			[Description("")]
			[Category("Interface")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool AbortOnPanicAlert { get; set; }

			[DisplayName("On Screen Display Messages")]
			[Description("")]
			[Category("Interface")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool OnScreenDisplayMessages { get; set; }
		}

		public class DolphinWiiPadSettings
		{
			// custom since all keys are "Source"
			// luckily there's few settings here
			public void ApplyNativeSettings(List<string> config)
			{
				config.Add($"--config=Wiimote.Wiimote1.Source={(int)Wiimote1}");
				config.Add($"--config=Wiimote.Wiimote2.Source={(int)Wiimote2}");
				config.Add($"--config=Wiimote.Wiimote3.Source={(int)Wiimote3}");
				config.Add($"--config=Wiimote.Wiimote4.Source={(int)Wiimote4}");
				config.Add($"--config=Wiimote.BalanceBoard.Source={(int)WiimoteSources.None}");
			}

			public DolphinWiiPadSettings()
			{
				SettingsUtil.SetDefaultValues(this);
			}

			public enum WiimoteSources
			{
				None = 0,
				Emulated = 1,
			}

			[DisplayName("Wiimote 1")]
			[Description("")]
			[Category("Wiimotes")]
			[DefaultValue(WiimoteSources.Emulated)]
			[Browsable(true)]
			public WiimoteSources Wiimote1 { get; set; }

			[DisplayName("Wiimote 2")]
			[Description("")]
			[Category("Wiimotes")]
			[DefaultValue(WiimoteSources.None)]
			[Browsable(true)]
			public WiimoteSources Wiimote2 { get; set; }

			[DisplayName("Wiimote 3")]
			[Description("")]
			[Category("Wiimotes")]
			[DefaultValue(WiimoteSources.None)]
			[Browsable(true)]
			public WiimoteSources Wiimote3 { get; set; }

			[DisplayName("Wiimote 4")]
			[Description("")]
			[Category("Wiimotes")]
			[DefaultValue(WiimoteSources.None)]
			[Browsable(true)]
			public WiimoteSources Wiimote4 { get; set; }
		}

		public class DolphinGFXSettings : DolphinNativeSettings
		{
			protected override string NativeName => "Graphics";

			public DolphinGFXSettings()
			{
				SettingsUtil.SetDefaultValues(this);
			}

			[DisplayName("VSync")]
			[Description("")]
			[Category("Hardware")]
			[DefaultValue(false)]
			[Browsable(false)]
			public bool VSync { get; set; }

			[DisplayName("Adapter")]
			[Description("Refer to Dolphin's adapter order for what these values mean.")]
			[Category("Hardware")]
			[DefaultValue(0)]
			[Browsable(true)]
			public int Adapter { get; set; }

			[DisplayName("Widescreen Hack")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool wideScreenHack { get; set; }

			public enum AspectModes : int
			{
				Auto,
				AnalogWide,
				Analog,
				Stretch,
			}

			[DisplayName("Aspect Ratio")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(AspectModes.Auto)]
			[Browsable(true)]
			public AspectModes AspectRatio { get; set; }

			[DisplayName("Crop")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool Crop { get; set; }

			public enum TextureCache : int
			{
				Safe = 0,
				Mid = 512,
				Fast = 128,
			}

			[DisplayName("Texture Cache Accuracy")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(TextureCache.Fast)]
			[Browsable(true)]
			public TextureCache SafeTextureCacheColorSamples { get; set; }

			[DisplayName("Enable GPU Texture Decoding")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool EnableGPUTextureDecoding { get; set; }

			[DisplayName("Enable Pixel Lighting")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool EnablePixelLighting { get; set; }

			[DisplayName("Fast Depth Calc")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool FastDepthCalc { get; set; }

			[DisplayName("Disable Fog")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool DisableFog { get; set; }

			[DisplayName("Backend Multithreading")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool BackendMultithreading { get; set; }

			[DisplayName("Save Texture Cache To State")]
			[Description("")]
			[Category("Settings")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool SaveTextureCacheToState { get; set; }

			[DisplayName("Force Filtering")]
			[Description("")]
			[Category("Enhancements")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool ForceFiltering { get; set; }

			[DisplayName("Force True Color")]
			[Description("")]
			[Category("Enhancements")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool ForceTrueColor { get; set; }

			[DisplayName("Disable Copy Filter")]
			[Description("")]
			[Category("Enhancements")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool DisableCopyFilter { get; set; }

			[DisplayName("Arbitrary Mipmap Detection")]
			[Description("")]
			[Category("Enhancements")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool ArbitraryMipmapDetection { get; set; }

			[DisplayName("EFB Access Enable")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool EFBAccessEnable { get; set; }

			[DisplayName("EFB Access Defer Invalidation")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool EFBAccessDeferInvalidation { get; set; }

			[DisplayName("Bounding Box Enable")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool BBoxEnable { get; set; }

			[DisplayName("Force Progressive")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool ForceProgressive { get; set; }

			[DisplayName("EFB To Texture Enable")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool EFBToTextureEnable { get; set; }

			[DisplayName("XFB To Texture Enable")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool XFBToTextureEnable { get; set; }

			[DisplayName("Disable Copy To VRAM")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool DisableCopyToVRAM { get; set; }

			[DisplayName("Defer EFB Copies")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool DeferEFBCopies { get; set; }

			[DisplayName("Immediate XFB Enable")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool ImmediateXFBEnable { get; set; }

			[DisplayName("Skip Duplicate XFBs")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool SkipDuplicateXFBs { get; set; }

			[DisplayName("Early XFB Output")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool EarlyXFBOutput { get; set; }

			[DisplayName("EFB Scaled Copy")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool EFBScaledCopy { get; set; }

			[DisplayName("EFB Emulate Format Changes")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool EFBEmulateFormatChanges { get; set; }

			[DisplayName("Vertex Rounding")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool VertexRounding { get; set; }

			[DisplayName("Fast Texture Sampling")]
			[Description("")]
			[Category("Hacks")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool FastTextureSampling { get; set; }
		}

		public class DolphinSYSCONFSettings : DolphinNativeSettings
		{
			protected override string NativeName => "SYSCONF";

			public DolphinSYSCONFSettings()
			{
				SettingsUtil.SetDefaultValues(this);
			}

			[DisplayName("Sreensaver")]
			[Description("")]
			[Category("IPL")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool SSV { get; set; }

			public enum WiiLanguages : int
			{
				Japanese = 0,
				English = 1,
				German = 2,
				French = 3,
				Spanish = 4,
				Italian = 5,
				Dutch = 6,
				SimplifiedChinese = 7,
				TraditionalChinese = 8,
				Korean = 9,
				Unknown,
			}

			[DisplayName("Language")]
			[Description("")]
			[Category("IPL")]
			[DefaultValue(WiiLanguages.English)]
			[Browsable(true)]
			public WiiLanguages LNG { get; set; }

			public enum WiiCountries : int
			{
				Europe = 0,
				Japan,
				USA,
				Australia,
				France,
				Germany,
				Italy,
				Korea,
				Netherlands,
				Russia,
				Spain,
				Taiwan,
				World,
				Unknown,
			}

			[DisplayName("Country")]
			[Description("")]
			[Category("IPL")]
			[DefaultValue(WiiCountries.USA)]
			[Browsable(true)]
			public WiiCountries SADR { get; set; }

			[DisplayName("Widescreen")]
			[Description("")]
			[Category("IPL")]
			[DefaultValue(false)]
			[Browsable(true)]
			public bool AR { get; set; }

			[DisplayName("Progressive Scan")]
			[Description("")]
			[Category("IPL")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool PGS { get; set; }

			[DisplayName("PAL60")]
			[Description("")]
			[Category("IPL")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool E60 { get; set; }

			public enum SoundModes : int
			{
				Mono = 0,
				Stereo = 1,
				Surround = 2,
			}

			[DisplayName("Sound Mode")]
			[Description("")]
			[Category("IPL")]
			[DefaultValue(SoundModes.Stereo)]
			[Browsable(true)]
			public SoundModes SND { get; set; }

			public enum SensorBarPositions : int
			{
				Bottom = 0,
				Top = 1,
			}

			[DisplayName("Sensor Bar Position")]
			[Description("")]
			[Category("BT")]
			[DefaultValue(SensorBarPositions.Top)]
			[Browsable(true)]
			public SensorBarPositions BAR { get; set; }

			public enum SensorBarSensitivities : int
			{
				Min = 1,
				Low = 2,
				Mid = 3,
				High = 4,
				Max = 5,
			}

			[JsonIgnore]
			private int _spkv;

			[DisplayName("Wiimote Speaker Volume")]
			[Description("")]
			[Category("BT")]
			[DefaultValue(88)]
			[Browsable(true)]
			public int SPKV
			{
				get => _spkv;
				set => _spkv = Math.Min(Math.Max(0, value), 127);
			}

			[DisplayName("Wiimote Motor On")]
			[Description("")]
			[Category("BT")]
			[DefaultValue(true)]
			[Browsable(true)]
			public bool MOT { get; set; }
		}
	}
}
