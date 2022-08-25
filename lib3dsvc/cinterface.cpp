#include "CGB/cgbEmuCore.h"
#include "CGB/cgbInput.h"
#include "CGB/cgbGraphic.h"
#include "newstate.h"
#include "blip_buf.h"
#include <assert.h>
#include <math.h>
#include <string>
#include <unordered_map>

#define EXPORT extern "C" __attribute__((visibility("default")))

static trlSEmuShellBuffer gb{};
static s16 sndBuf[TRL_EMUCORE_SNDBUF]{};
static u16 texBuf[2][TRL_EMUCORE_TEX_X * TRL_EMUCORE_TEX_Y]{};
static trlSEmuShellResume stateBuf[9]{};

static u32 colorLut[0x8000]{};
static blip_t* blipL{};
static blip_t* blipR{};
static s16 latchL{}, latchR{};

MemoryCallback_t ReadCallback{};
MemoryCallback_t WriteCallback{};
MemoryCallback_t ExecuteCallback{};
TraceCallback_t TraceCallback{};

u32* InterruptAddresses{};
u32 NumInterruptAddresses{};
s32 HitInterruptAddress{};

extern u64 TimeTicks;

static s32 SaveBackup() {
	// this is just a "force flush" function
	return 0;
}

static void ChangeMaskMode(u32) {
	// ???
}

static void ChangeFilterMode(u32) {
	// ???
}

std::unordered_map<std::string, u32> cgbConfig = {
	{ "SoundSwapLR", 0 },
	{ "RenderTime", 0 },
	{ "Logo", 0 },
	{ "ObjLineLimit", 1 },
	{ "LCDOnDelay", 1 },
	{ "LCDIntOnce", 0 },
	{ "VBlankDelay", 1 },
	{ "SoundCH1Sweep", 1 },
	{ "SoundNoiseTable", 1 },
	{ "SoundMultiSample", 1 },
	{ "SoundCH1Reset", 0 },
	{ "SoundCH2Reset", 0 },
	{ "SoundCH1SweepLimit", 2047 },
	{ "ColorLCD", CGB_RGB(31, 31, 31) },
	{ "SDataInitValue", 0 },
};

std::unordered_map<std::string, u32> dmgColorConfig = {
	{ "Color0", CGB_RGB(23, 31, 4) },
	{ "Color1", CGB_RGB(19, 29, 5) },
	{ "Color2", CGB_RGB(11, 17, 8) },
	{ "Color3", CGB_RGB(9, 9, 9) },
	{ "ColorLCD", CGB_RGB(20, 27, 7) },
};

std::unordered_map<std::string, u32> dmgColorGrayConfig = {
	{ "Color0", CGB_RGB(25, 25, 21) },
	{ "Color1", CGB_RGB(20, 20, 17) },
	{ "Color2", CGB_RGB(13, 13, 10) },
	{ "Color3", CGB_RGB(5, 5, 3) },
	{ "ColorLCD", CGB_RGB(25, 25, 21) },
};

static u32 ConfigData(const char* system, const char* configName, u32 defaultValue) {
	std::string which = std::string(system);
	std::string key = std::string(configName);

	if (which == std::string("CGB")) {
		if (cgbConfig.find(key) != cgbConfig.end()) {
			return cgbConfig[key];
		}
	} else if (which == std::string("DMG_COLOR")) {
		if (dmgColorConfig.find(key) != dmgColorConfig.end()) {
			return dmgColorConfig[key];
		}
	} else if (which == std::string("DMG_COLOR_GRAY")) {
		if (dmgColorGrayConfig.find(key) != dmgColorGrayConfig.end()) {
			return dmgColorGrayConfig[key];
		}
	}

	return defaultValue;
}

static inline u32 Pow2Ceil(u32 n) {
	--n;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	++n;

	return n;
}

static void Cleanup() {
	free(gb.pRomBuf);
	memset(&gb, 0, sizeof (gb));
	blip_delete(blipL);
	blip_delete(blipR);
	blipL = blipR = nullptr;
	latchL = latchR = 0;
	ReadCallback = WriteCallback = ExecuteCallback = nullptr;
	TraceCallback = nullptr;
	InterruptAddresses = nullptr;
	NumInterruptAddresses = 0;
	HitInterruptAddress = -1;
	TimeTicks = 0;
}

EXPORT void VC_Init(u8* rom, u32 romsz) {
	Cleanup();
	gb.nWidth = 160;
	gb.nHeight = 144;
	gb.nTexWidth = TRL_EMUCORE_TEX_X;
	gb.nTexHeight = TRL_EMUCORE_TEX_Y;
	gb.nRomBufSize = Pow2Ceil(romsz);
	gb.pRomBuf = malloc(gb.nRomBufSize);
	memcpy(gb.pRomBuf, rom, romsz);
	memset(((u8*)gb.pRomBuf) + romsz, 0xFF, gb.nRomBufSize - romsz);
	gb.nSoundBufSize = TRL_EMUCORE_SNDBUF * 2;
	gb.pSoundBuf = sndBuf;
	gb.pTextureBuf[0] = texBuf[0];
	gb.pTextureBuf[1] = texBuf[1];
	gb.pScreenBuf = texBuf[0];
	gb.pSaveData = stateBuf;
	gb.funcSaveBackup = SaveBackup;
	gb.funcChangeMaskMode = ChangeMaskMode;
	gb.funcChangeFilterMode = ChangeFilterMode;
	gb.funcConfigData = ConfigData;
	cgbEmuCoreInit(&gb);

	blipL = blip_new(1024);
	blipR = blip_new(1024);
	blip_set_rates(blipL, 1048576.0 / (188.0 / 8.0), 44100);
	blip_set_rates(blipR, 1048576.0 / (188.0 / 8.0), 44100);
	latchL = latchR = 0;

	for (u32 i = 0; i < 0x8000; i++) {
		u32 const pixel = i << 1;
		u32 r = CGB_BGRA_R(pixel);
		u32 g = CGB_BGRA_G(pixel);
		u32 b = CGB_BGRA_B(pixel);

		if (g_nCgbGameType == CGB_GAMETYPE_CGB) {
			static u32 sameBoyCgbColorCurve[32] = { 0, 6, 12, 20, 28, 36, 45, 56, 66, 76, 88, 100, 113, 125, 137, 149, 161, 172, 182, 192, 202, 210, 218, 225, 232, 238, 243, 247, 250, 252, 254, 255 };

			r = sameBoyCgbColorCurve[r];
			g = sameBoyCgbColorCurve[g];
			b = sameBoyCgbColorCurve[b];

			if (g != b) {
				constexpr double gamma = 1.6;
				g = round(pow((pow(g / 255.0, gamma) * 3 + pow(b / 255.0, gamma)) / 4, 1 / gamma) * 255);
			}
		} else {
			r = (r << 3) | (r >> 2);
			g = (g << 3) | (g >> 2);
			b = (b << 3) | (b >> 2);
		}

		colorLut[i] = (0xFF << 24) | (r << 16) | (g << 8) | b;
	}
}

EXPORT void VC_Deinit() {
	cgbEmuCoreExit();
	Cleanup();
	g_pCgbEmuBuf = nullptr;
}

EXPORT bool VC_IsCGB() {
	return g_nCgbGameType == CGB_GAMETYPE_CGB;
}

EXPORT void VC_Reset() {
	cgbEmuCoreReset();
}

extern s32 g_nCgbSndBufPos;

EXPORT s32 VC_RunFrame(u8 input, u32* vbuf, s16* sbuf, u32* nsamps) {
	cgbKeyUpdate(input);
	gb.nAudioSampleCurFrame = 1024;
	HitInterruptAddress = -1;
	cgbEmuCoreRunOneFrame();

	if (__builtin_expect(!!(g_nCgbBreakFlag & 1), 1)) {
		const u16* src = texBuf[gb.nTexID];
		for (u32 i = 0; i < 144; i++) {
			for (u32 j = 0; j < 160; j++) {
				vbuf[j] = colorLut[(src[j] >> 1) & 0x7FFF];
			}

			src += TRL_EMUCORE_TEX_X;
			vbuf += 160;
		}
	}

	for (u32 i = 0; i < g_nCgbSndBufPos; i += 2) {
		if (latchL != sndBuf[i]) {
			blip_add_delta(blipL, i / 2, latchL - sndBuf[i]);
			latchL = sndBuf[i];
		}

		if (latchR != sndBuf[i + 1]) {
			blip_add_delta(blipR, i / 2, latchR - sndBuf[i + 1]);
			latchR = sndBuf[i + 1];
		}
	}

	blip_end_frame(blipL, g_nCgbSndBufPos / 2);
	blip_end_frame(blipR, g_nCgbSndBufPos / 2);

	*nsamps = blip_samples_avail(blipL);
	blip_read_samples(blipL, sbuf + 0, *nsamps, 1);
	blip_read_samples(blipR, sbuf + 1, *nsamps, 1);

	TimeTicks += g_nCgbSndBufPos;
	g_nCgbSndBufPos = 0;

	return HitInterruptAddress;
}

EXPORT u32 VC_SramLength() {
	return gb.nBackupDataSize;
}

EXPORT u32 VC_SramDirty() {
	return gb.nSaveUpdate;
}

EXPORT void VC_SaveSram(u8* dst) {
	memcpy(dst, gb.pBackupData, gb.nBackupDataSize);
}

EXPORT void VC_LoadSram(u8* src) {
	memcpy(gb.pBackupData, src, gb.nBackupDataSize);
	gb.nSaveUpdate = 0;
}

EXPORT u32 VC_StateLength() {
	NewStateDummy dummy;
	SyncState<false>(&dummy);
	return dummy.GetLength();
}

EXPORT bool VC_SaveStateBinary(u8* dst, u32 len) {
	NewStateExternalBuffer saver(dst, len);
	SyncState<false>(&saver);
	return !saver.Overflow() && saver.GetLength() == len;
}

EXPORT bool VC_LoadStateBinary(u8* src, u32 len) {
	NewStateExternalBuffer loader(src, len);
	SyncState<true>(&loader);
	gb.nSaveUpdate = 1;
	return !loader.Overflow() && loader.GetLength() == len;
}

EXPORT void VC_SaveStateText(FPtrs* ff) {
	NewStateExternalFunctions saver(ff);
	SyncState<false>(&saver);
}

EXPORT void VC_LoadStateText(FPtrs* ff) {
	NewStateExternalFunctions loader(ff);
	SyncState<true>(&loader);
	gb.nSaveUpdate = 1;
}

enum class MemoryAreas {
	ROM,
	WRAM,
	VRAM,
	CartRAM,
	OAM,
	HRAM,
	MMIO,
	BGPAL,
	OBJPAL,
};

static u32 bgPal[0x20]{};
static u32 objPal[0x20]{};

template <bool bg>
static inline void UpdatePal() {
	const auto& srcPal = bg ? g_nCgbGrpBGPal : g_nCgbGrpOBJPal;
	auto& dstPal = bg ? bgPal : objPal;
	if (g_nCgbGameType == CGB_GAMETYPE_CGB) {
		for (u32 i = 0; i < 8; i++) {
			for (u32 j = 0; j < 4; j++) {
				dstPal[i * 4 + j] = colorLut[(srcPal[i][j] >> 1) & 0x7FFF];
			}
		}
	} else {
		memset(dstPal, 0xFF, 0x20 * sizeof(u32));
		for (u32 i = 0; i < (bg ? 1 : 2); i++) {
			for (u32 j = 0; j < 4; j++) {
				dstPal[i * 4 + j] = colorLut[(srcPal[i][j] >> 1) & 0x7FFF];
			}
		}
	}
}

extern u32 g_nCgbMemWRAMSize;
extern u32 g_nCgbMemVRAMSize;
extern u32 g_nCgbCardERAMSize;

EXPORT bool VC_GetMemoryArea(MemoryAreas which, void** ptr, u32* len) {
	switch (which) {
		case MemoryAreas::ROM:
			if (ptr) *ptr = g_pCgbROM;
			if (len) *len = gb.nRomBufSize;
			return true;
		case MemoryAreas::WRAM:
			if (ptr) *ptr = g_pCgbWRAM;
			if (len) *len = g_nCgbMemWRAMSize;
			return true;
		case MemoryAreas::VRAM:
			if (ptr) *ptr = g_pCgbVRAM;
			if (len) *len = g_nCgbMemVRAMSize;
			return true;
		case MemoryAreas::CartRAM:
			if (ptr) *ptr = g_pCgbERAM;
			if (len) *len = g_nCgbCardERAMSize;
			return true;
		case MemoryAreas::OAM:
			if (ptr) *ptr = g_pCgbOAM;
			if (len) *len = 0xA0;
			return true;
		case MemoryAreas::HRAM:
			if (ptr) *ptr = g_pCgbHRAM;
			if (len) *len = 0x80;
			return true;
		case MemoryAreas::MMIO:
			if (ptr) *ptr = g_pCgbREG;
			if (len) *len = 0x80;
			return true;
		case MemoryAreas::BGPAL:
			UpdatePal<true>();
			if (ptr) *ptr = bgPal;
			if (len) *len = sizeof(bgPal);
			return true;
		case MemoryAreas::OBJPAL:
			UpdatePal<false>();
			if (ptr) *ptr = objPal;
			if (len) *len = sizeof(objPal);
			return true;
	}

	return false;
}

EXPORT u8 VC_GetIOReg(u8 index) {
	return g_pCgbREG[index];
}

extern u8 cgbMemRead8(u16 nAddr);
extern u8 cgbMemWrite8(u16 nAddr, u8 nValue);

EXPORT u8 VC_Peek(u16 addr) {
	auto cb = ReadCallback;
	ReadCallback = nullptr;
	u8 ret = cgbMemRead8(addr);
	ReadCallback = cb;
	return ret;
}

EXPORT void VC_Poke(u16 addr, u8 val) {
	auto cb = WriteCallback;
	WriteCallback = nullptr;
	cgbMemWrite8(addr, val);
	WriteCallback = cb;
}

enum class CpuRegisters {
	PC,
	SP,
	AF,
	BC,
	DE,
	HL,
	A,
	F,
	B,
	C,
	D,
	E,
	H,
	L,
};

extern u16 g_nCgbCpuRegPC;
extern u16 g_nCgbCpuRegSP;
extern u8 g_nCgbCpuReg8[8];

EXPORT u32 VC_GetReg(CpuRegisters which) {
	switch (which) {
		case CpuRegisters::PC: return g_nCgbCpuRegPC;
		case CpuRegisters::SP: return g_nCgbCpuRegSP;
		case CpuRegisters::AF: return *(u16*)&g_nCgbCpuReg8[0];
		case CpuRegisters::BC: return *(u16*)&g_nCgbCpuReg8[2];
		case CpuRegisters::DE: return *(u16*)&g_nCgbCpuReg8[4];
		case CpuRegisters::HL: return *(u16*)&g_nCgbCpuReg8[6];
		case CpuRegisters::F: return g_nCgbCpuReg8[0];
		case CpuRegisters::A: return g_nCgbCpuReg8[1];
		case CpuRegisters::C: return g_nCgbCpuReg8[2];
		case CpuRegisters::B: return g_nCgbCpuReg8[3];
		case CpuRegisters::E: return g_nCgbCpuReg8[4];
		case CpuRegisters::D: return g_nCgbCpuReg8[5];
		case CpuRegisters::L: return g_nCgbCpuReg8[6];
		case CpuRegisters::H: return g_nCgbCpuReg8[7];
	}

	assert(false);
}

EXPORT void VC_GetRegs(u32* dst) {
	dst[0] = g_nCgbCpuRegPC;
	dst[1] = g_nCgbCpuRegSP;
	dst[2] = *(u16*)&g_nCgbCpuReg8[0];
	dst[3] = *(u16*)&g_nCgbCpuReg8[2];
	dst[4] = *(u16*)&g_nCgbCpuReg8[4];
	dst[5] = *(u16*)&g_nCgbCpuReg8[6];
}

EXPORT void VC_SetReg(CpuRegisters which, u32 val) {
	switch (which) {
		case CpuRegisters::PC: g_nCgbCpuRegPC = val; return;
		case CpuRegisters::SP: g_nCgbCpuRegSP = val; return;
		case CpuRegisters::AF: *(u16*)&g_nCgbCpuReg8[0] = val; return;
		case CpuRegisters::BC: *(u16*)&g_nCgbCpuReg8[2] = val; return;
		case CpuRegisters::DE: *(u16*)&g_nCgbCpuReg8[4] = val; return;
		case CpuRegisters::HL: *(u16*)&g_nCgbCpuReg8[6] = val; return;
		case CpuRegisters::F: g_nCgbCpuReg8[0] = val; return;
		case CpuRegisters::A: g_nCgbCpuReg8[1] = val; return;
		case CpuRegisters::C: g_nCgbCpuReg8[2] = val; return;
		case CpuRegisters::B: g_nCgbCpuReg8[3] = val; return;
		case CpuRegisters::E: g_nCgbCpuReg8[4] = val; return;
		case CpuRegisters::D: g_nCgbCpuReg8[5] = val; return;
		case CpuRegisters::L: g_nCgbCpuReg8[6] = val; return;
		case CpuRegisters::H: g_nCgbCpuReg8[7] = val; return;
	}

	assert(false);
}

enum class MemoryCallbacks {
	READ,
	WRITE,
	EXECUTE,
};

EXPORT void VC_SetMemoryCallback(MemoryCallbacks which, MemoryCallback_t callback) {
	switch (which) {
		case MemoryCallbacks::READ: ReadCallback = callback; return;
		case MemoryCallbacks::WRITE: WriteCallback = callback; return;
		case MemoryCallbacks::EXECUTE: ExecuteCallback = callback; return;
	}

	assert(false);
}

EXPORT void VC_SetTraceCallback(TraceCallback_t callback) {
	TraceCallback = callback;
}

EXPORT void VC_SetInterruptAddresses(u32* addrs, u32 numAddrs) {
	InterruptAddresses = addrs;
	NumInterruptAddresses = numAddrs;
}

extern s32 g_nCgbSndBufPos;
extern s32 g_nCgbSndTicks;

// at 2MiHz
EXPORT u64 VC_CycleCount() {
	return ((TimeTicks + g_nCgbSndBufPos) * 188 + ((188 - g_nCgbSndTicks) * 2 * 8)) / 8;
}
