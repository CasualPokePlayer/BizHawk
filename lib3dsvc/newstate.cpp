#include "newstate.h"
#include "EmuShell/trlEmuShellStruct.h"
#include <cstring>
#include <algorithm>

NewStateDummy::NewStateDummy()
: length(0)
{
}

void NewStateDummy::Save(const void* /*ptr*/, size_t size, const char* /*name*/) {
	length += size;
}

void NewStateDummy::Load(void* /*ptr*/, size_t /*size*/, const char* /*name*/) {
}

NewStateExternalBuffer::NewStateExternalBuffer(u8 *buffer, ptrdiff_t maxlength)
: buffer(buffer)
, length(0)
, maxlength(maxlength)
{
}

void NewStateExternalBuffer::Save(const void* ptr, size_t size, const char* /*name*/) {
	if (maxlength - length >= (ptrdiff_t)size)
		std::memcpy(buffer + length, ptr, size);

	length += size;
}

void NewStateExternalBuffer::Load(void* ptr, size_t size, const char* /*name*/) {
	u8* dst = static_cast<u8 *>(ptr);
	if (maxlength - length >= (ptrdiff_t)size)
		std::memcpy(dst, buffer + length, size);

	length += size;
}

NewStateExternalFunctions::NewStateExternalFunctions(const FPtrs *ff)
: Save_(ff->Save_)
, Load_(ff->Load_)
, EnterSection_(ff->EnterSection_)
, ExitSection_(ff->ExitSection_)
{
}

void NewStateExternalFunctions::Save(const void* ptr, size_t size, const char* name) {
	Save_(ptr, size, name);
}

void NewStateExternalFunctions::Load(void* ptr, size_t size, const char* name) {
	Load_(ptr, size, name);
}

void NewStateExternalFunctions::EnterSection(const char* name) {
	EnterSection_(name);
}

void NewStateExternalFunctions::ExitSection(const char* name) {
	ExitSection_(name);
}

// cgbGlobal.cpp
// these pointers are constant, and various other pointers are relative to them

extern u8* g_pCgbROM;
extern u8* g_pCgbWRAM;
extern u8* g_pCgbVRAM;
extern u8* g_pCgbERAM;
extern u8* g_pCgbOAM;
extern u8* g_pCgbREG;

// cgbMemory.cpp

extern u8* g_pCgbCurWRAM;
extern u8* g_pCgbCurVRAM;
extern u32 g_nCgbMemWRAMSize;
extern u32 g_nCgbMemVRAMSize;

template <bool isReader>
static void MemorySyncState(NewState* ns) {
	PSS(g_pCgbWRAM, g_nCgbMemWRAMSize);
	PSS(g_pCgbVRAM, g_nCgbMemVRAMSize);
	PSS(g_pCgbOAM, 0xA0);
	PSS(g_pCgbREG, 0x100);
	RSS(g_pCgbCurWRAM, g_pCgbWRAM);
	RSS(g_pCgbCurVRAM, g_pCgbVRAM);
	NSS(g_nCgbMemWRAMSize);
	NSS(g_nCgbMemVRAMSize);
}

// cgbCard.cpp

extern u8* g_pCgbCurROM;
extern u8* g_pCgbCurERAM;
extern u8* g_pCgbERAMMBC4N64;
extern u8* g_pCgbMBC3RTCReg;
extern u64* g_pCgbMBC3Timer;
extern u32 g_nCgbRAMEnable;
extern u32 g_nCgbROMBank;
extern u32 g_nCgbRAMBank;
extern u32 g_nCgbROMBankMask;
extern u32 g_nCgbRAMBankMask;
extern u32 g_nCgbCardERAMSize;
extern u32 g_nCgbMBC1Mode;
extern u32 g_nCgbMBC3RTCSelect;
extern u32 g_nCgbMBC3ClockLatch;
extern u8 g_nCgbMBC3RTCLatch[8];
extern u32 g_nCgbMBC4N64;
extern u32 g_nCgbMBC5Rumble;
extern u32 g_nCgbCardWriteFlag;

template <bool isReader>
static void CardSyncState(NewState* ns) {
	if (g_pCgbERAM) PSS(g_pCgbERAM, g_nCgbCardERAMSize);
	RSS(g_pCgbCurROM, g_pCgbROM);
	RSS(g_pCgbCurERAM, g_pCgbERAM);
	if (g_pCgbERAMMBC4N64) PSS(g_pCgbERAMMBC4N64, 0x2000);
	RSS(g_pCgbMBC3RTCReg, g_pCgbERAM);
	RSS(g_pCgbMBC3Timer, (u64*)g_pCgbERAM);
	NSS(g_nCgbRAMEnable);
	NSS(g_nCgbROMBank);
	NSS(g_nCgbRAMBank);
	NSS(g_nCgbROMBankMask);
	NSS(g_nCgbRAMBankMask);
	NSS(g_nCgbCardERAMSize);
	NSS(g_nCgbMBC1Mode);
	NSS(g_nCgbMBC3RTCSelect);
	NSS(g_nCgbMBC3ClockLatch);
	NSS(g_nCgbMBC3RTCLatch);
	NSS(g_nCgbMBC4N64);
	NSS(g_nCgbMBC5Rumble);
	NSS(g_nCgbCardWriteFlag);
}

// cgbRegister.cpp
// most of the values are just constant pointers relative to g_pCgbREG

extern u8 g_nCgbRegLastVal;

template <bool isReader>
static void RegisterSyncState(NewState* ns) {
	NSS(g_nCgbRegLastVal);
}

// cgbTime.cpp

extern s32 g_nCgbTimeValue;
extern s32 g_nCgbTimeTicks;
extern s32 g_nCgbDivTicks;

template <bool isReader>
static void TimeSyncState(NewState* ns) {
	NSS(g_nCgbTimeValue);
	NSS(g_nCgbTimeTicks);
	NSS(g_nCgbDivTicks);
}

// cgbDMA.cpp

extern s32 g_nCgbDmaTicks;
extern s32 g_nCgbDmaTick0;
extern u32 g_nCgbDmaHDMAFlag;

template <bool isReader>
static void DMASyncState(NewState* ns) {
	NSS(g_nCgbDmaTicks);
	NSS(g_nCgbDmaTick0);
	NSS(g_nCgbDmaHDMAFlag);
}

// cgbGraphic.cpp

// duplicate struct info to avoid including header

struct cgbSGrpOAMInfo {
	s32 nTop;
	s32 nBottom;
	s32 nSX;
	u32 nCharID;
	u32 nAttr;
	s32 nStart;
	s32 nEnd;
	u16* pPal;
	u32 nCharOffset;
	s32 nTileX;
	cgbSGrpOAMInfo* pNext;
};

extern s32 g_nCgbGrpTicks;
extern s32 g_nCgbGrpTick0;
extern s32 g_nCgbGrpTick1;
extern s32 g_nCgbGrpTick2;
extern s32 g_nCgbGrpTick3;
extern u8* g_pCgbGrpLineInfo;
extern u16 g_nCgbGrpDMGColor[14];
extern u16 g_nCgbGrpBGPalReal[8][4];
extern u16 g_nCgbGrpOBJPalReal[8][4];
extern u16 g_nCgbGrpBGPal[8][4];
extern u16 g_nCgbGrpOBJPal[8][4];
extern s32 g_nCgbGrpWinY;
extern cgbSGrpOAMInfo* g_pCgbGrpOAMInfo;
extern u32 g_nCgbGrpOAMInfoCount;
extern u8* g_pCgbGrpBGSrnDataBase;
extern u8* g_pCgbGrpBGAtrDataBase;
extern u8* g_pCgbGrpWinSrnDataBase;
extern u8* g_pCgbGrpWinAtrDataBase;
extern u16* g_pCgbGrpBGWinTileDataBase;
extern u8 g_nCgbGrpBGWinTileOffset;
extern s32 g_nCgbGrpOBJSize;
extern u32 g_bCgbGrpOAMChange;
extern u16* g_pCgbGrpRenderBuf;
extern u8* g_pCgbGrpCGBFlipData;
extern u32 g_bCgbGrpLCDEnable;
extern u32 g_bCgbGrpVBlankMode;
extern u32 g_bCgbGrpRenderTime;
extern u32 g_bCgbGrpWinEnable;
extern u32 g_bCgbGrpLogo;
extern u32 g_bCgbGrpObjLineLimit;
extern u32 g_nCgbGrpLCDCIntFlag;
extern u32 g_nCgbGrpLCDCInt;
extern u32 g_nCgbGrpLCDOnDelay;
extern s32 g_nCgbGrpVBlankDelay;

template <bool isReader>
static void GraphicSyncState(NewState* ns) {
	NSS(g_nCgbGrpTicks);
	NSS(g_nCgbGrpTick0);
	NSS(g_nCgbGrpTick1);
	NSS(g_nCgbGrpTick2);
	NSS(g_nCgbGrpTick3);
	PSS(g_pCgbGrpLineInfo, 160);
	NSS(g_nCgbGrpDMGColor);
	NSS(g_nCgbGrpBGPalReal);
	NSS(g_nCgbGrpOBJPalReal);
	NSS(g_nCgbGrpBGPal);
	NSS(g_nCgbGrpOBJPal);
	NSS(g_nCgbGrpWinY);
	for (u32 i = 0; i < 40; i++) {
		NSS(g_pCgbGrpOAMInfo[i].nTop);
		NSS(g_pCgbGrpOAMInfo[i].nBottom);
		NSS(g_pCgbGrpOAMInfo[i].nSX);
		NSS(g_pCgbGrpOAMInfo[i].nCharID);
		NSS(g_pCgbGrpOAMInfo[i].nAttr);
		NSS(g_pCgbGrpOAMInfo[i].nEnd);
		RSS(g_pCgbGrpOAMInfo[i].pPal, &g_nCgbGrpOBJPal[0][0]);
		NSS(g_pCgbGrpOAMInfo[i].nCharOffset);
		NSS(g_pCgbGrpOAMInfo[i].nTileX);
		RSS(g_pCgbGrpOAMInfo[i].pNext, g_pCgbGrpOAMInfo);
	}
	NSS(g_nCgbGrpOAMInfoCount);
	RSS(g_pCgbGrpBGSrnDataBase, g_pCgbVRAM);
	RSS(g_pCgbGrpBGAtrDataBase, g_pCgbVRAM);
	RSS(g_pCgbGrpWinSrnDataBase, g_pCgbVRAM);
	RSS(g_pCgbGrpWinAtrDataBase, g_pCgbVRAM);
	RSS(g_pCgbGrpBGWinTileDataBase, (u16*)g_pCgbVRAM);
	NSS(g_nCgbGrpBGWinTileOffset);
	NSS(g_nCgbGrpOBJSize);
	NSS(g_bCgbGrpOAMChange);
	if (g_pCgbGrpCGBFlipData) PSS(g_pCgbGrpCGBFlipData, 256);
	NSS(g_bCgbGrpLCDEnable);
	NSS(g_bCgbGrpVBlankMode);
	NSS(g_bCgbGrpRenderTime);
	NSS(g_bCgbGrpWinEnable);
	NSS(g_bCgbGrpLogo);
	NSS(g_bCgbGrpObjLineLimit);
	NSS(g_nCgbGrpLCDCIntFlag);
	NSS(g_nCgbGrpLCDCInt);
	NSS(g_nCgbGrpLCDOnDelay);
	NSS(g_nCgbGrpVBlankDelay);
}

// cgbSound.cpp

extern s8 g_nCgbSndWavePattern[4][8];
extern s32 g_nCgbSndBufOutput1;
extern s32 g_nCgbSndBufOutput2;
extern s32 g_nCgbSndBufSwap;
extern s32 g_nCgbSndTicks;
extern s32 g_nCgbSndTick0;
extern s32 g_nCgbSndVolume1;
extern s32 g_nCgbSndVolume2;
extern s32 g_nCgbSnd1Index;
extern s32 g_nCgbSnd1Length;
extern u32 g_nCgbSnd1Frequency;
extern s32 g_nCgbSnd1EnvelopeValue;
extern s32 g_nCgbSnd1EnvelopeLength;
extern s32 g_nCgbSnd1EnvelopeLengthInit;
extern s32 g_nCgbSnd1SweepLimit;
extern s32 g_nCgbSnd1SweepLength;
extern s32 g_nCgbSnd1SweepLengthInit;
extern s8* g_pCgbSnd1Wave;
extern u32 g_nCgbSnd1SweepFreq;
extern u32 g_bCgbSnd1SweepMode;
extern s32 g_nCgbSnd2Index;
extern s32 g_nCgbSnd2Length;
extern u32 g_nCgbSnd2Frequency;
extern s32 g_nCgbSnd2EnvelopeValue;
extern s32 g_nCgbSnd2EnvelopeLength;
extern s32 g_nCgbSnd2EnvelopeLengthInit;
extern s8* g_pCgbSnd2Wave;
extern s32 g_nCgbSnd3Index;
extern s32 g_nCgbSnd3Length;
extern u32 g_nCgbSnd3Frequency;
extern s32 g_nCgbSnd4Index;
extern s32 g_nCgbSnd4Length;
extern u32 g_nCgbSnd4Frequency;
extern s32 g_nCgbSnd4EnvelopeValue;
extern s32 g_nCgbSnd4EnvelopeLength;
extern s32 g_nCgbSnd4EnvelopeLengthInit;
extern s32 g_nCgbSnd4Shift;
extern u32 g_bCgbSnd4NoiseTable;
extern s32 g_nCgbSnd4TableIndex;
extern s32 g_nCgbSnd1Reset;
extern s32 g_nCgbSnd2Reset;
extern u32 g_nCgbSndMultiSample;

template <bool isReader>
static void SoundSyncState(NewState* ns) {
	NSS(g_nCgbSndBufOutput1);
	NSS(g_nCgbSndBufOutput2);
	NSS(g_nCgbSndBufSwap);
	NSS(g_nCgbSndTicks);
	NSS(g_nCgbSndTick0);
	NSS(g_nCgbSndVolume1);
	NSS(g_nCgbSndVolume2);
	NSS(g_nCgbSnd1Index);
	NSS(g_nCgbSnd1Length);
	NSS(g_nCgbSnd1Frequency);
	NSS(g_nCgbSnd1EnvelopeValue);
	NSS(g_nCgbSnd1EnvelopeLength);
	NSS(g_nCgbSnd1EnvelopeLengthInit);
	NSS(g_nCgbSnd1SweepLimit);
	NSS(g_nCgbSnd1SweepLength);
	NSS(g_nCgbSnd1SweepLengthInit);
	RSS(g_pCgbSnd1Wave, &g_nCgbSndWavePattern[0][0]);
	NSS(g_nCgbSnd1SweepFreq);
	NSS(g_bCgbSnd1SweepMode);
	NSS(g_nCgbSnd2Index);
	NSS(g_nCgbSnd2Length);
	NSS(g_nCgbSnd2Frequency);
	NSS(g_nCgbSnd2EnvelopeValue);
	NSS(g_nCgbSnd2EnvelopeLength);
	NSS(g_nCgbSnd2EnvelopeLengthInit);
	RSS(g_pCgbSnd2Wave, &g_nCgbSndWavePattern[0][0]);
	NSS(g_nCgbSnd3Index);
	NSS(g_nCgbSnd3Length);
	NSS(g_nCgbSnd3Frequency);
	NSS(g_nCgbSnd4Index);
	NSS(g_nCgbSnd4Length);
	NSS(g_nCgbSnd4Frequency);
	NSS(g_nCgbSnd4EnvelopeValue);
	NSS(g_nCgbSnd4EnvelopeLength);
	NSS(g_nCgbSnd4EnvelopeLengthInit);
	NSS(g_nCgbSnd4Shift);
	NSS(g_bCgbSnd4NoiseTable);
	NSS(g_nCgbSnd4TableIndex);
	NSS(g_nCgbSnd1Reset);
	NSS(g_nCgbSnd2Reset);
	NSS(g_nCgbSndMultiSample);
}

// cgbSerial.cpp

extern s32 g_nCgbSerialTicks;
extern s32 g_nCgbSerialTick0;
extern s32 g_nCgbSerialBits;

template <bool isReader>
static void SerialSyncState(NewState* ns) {
	NSS(g_nCgbSerialTicks);
	NSS(g_nCgbSerialTick0);
	NSS(g_nCgbSerialBits);
}

// cgbCPU.cpp

extern s32 g_nCgbCpuEventTicks;
extern s32 g_nCgbCpuTicks;
extern u8 g_nCgbCpuReg8[8];
extern u16 g_nCgbCpuRegPC;
extern u16 g_nCgbCpuRegSP;
extern u8 g_nCgbCpuTemp8;
extern u16 g_nCgbCpuTemp16;
extern u32 g_nCgbCpuIME;
extern u32 g_nCgbCpuState;
extern u8* g_pCgbCpuPC;

extern u8* cgbMemReadOpcode(u16 nAddr);

template <bool isReader>
static void CPUSyncState(NewState* ns) {
	NSS(g_nCgbCpuEventTicks);
	NSS(g_nCgbCpuTicks);
	NSS(g_nCgbCpuReg8);
	NSS(g_nCgbCpuRegPC);
	NSS(g_nCgbCpuRegSP);
	NSS(g_nCgbCpuTemp8);
	NSS(g_nCgbCpuTemp16);
	NSS(g_nCgbCpuIME);
	NSS(g_nCgbCpuState);
	if (isReader) {
		// FIXME: Not always right!
		g_pCgbCpuPC = cgbMemReadOpcode(g_nCgbCpuRegPC);
	}
}

#define SYNC(x) do { ns->EnterSection(#x); x##SyncState<isReader>(ns); ns->ExitSection(#x); } while (0)

template void SyncState<false>(NewState* ns);
template void SyncState<true>(NewState* ns);

extern u64 TimeTicks;

template <bool isReader>
void SyncState(NewState* ns) {
	ns->EnterSection("CGB");
	NSS(TimeTicks);
	SYNC(Memory);
	SYNC(Card);
	SYNC(Register);
	SYNC(Time);
	SYNC(DMA);
	SYNC(Graphic);
	SYNC(Sound);
	SYNC(Serial);
	SYNC(CPU);
	ns->ExitSection("CGB");
}
