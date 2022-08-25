#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef void (*MemoryCallback_t)(u16 addr, u8 val);
typedef void (*TraceCallback_t)();

// no-op these functions
#define trlTraceFrameBegin(...)
#define trlTraceFrameEnd(...)
#define trlTracePushStack(...)
#define trlTraceSoundDetallSweepFreq(...)
#define trlTraceSoundDetailWriteReg(...)
#define trlTraceSoundDetailMakeSample(...)
#define trlTraceTickAdd(...)
#define NN_LOG(...)

extern MemoryCallback_t ReadCallback;
extern MemoryCallback_t WriteCallback;
extern MemoryCallback_t ExecuteCallback;
extern TraceCallback_t TraceCallback;

extern u32* InterruptAddresses;
extern u32 NumInterruptAddresses;
extern s32 HitInterruptAddress;

#define trlTraceCPURun() \
	if (__builtin_expect(TraceCallback != nullptr, 0)) { \
		TraceCallback(); \
	} \
\
	if (__builtin_expect(ExecuteCallback != nullptr, 0)) { \
		ExecuteCallback(PC, *g_pCgbCpuPC); \
	} \
\
	if (__builtin_expect(NumInterruptAddresses > 0, 0)) { \
		for (u32 i = 0; i < NumInterruptAddresses; i++) { \
			if (PC == (InterruptAddresses[i] & 0xFFFF)) { \
				const u32 bank = InterruptAddresses[i] >> 16; \
				if (!bank || bank == g_nCgbROMBank) { \
					HitInterruptAddress = InterruptAddresses[i]; \
					break; \
				} \
			} \
		} \
	} \
\
	if (__builtin_expect(HitInterruptAddress >= 0, 0)) { \
		g_nCgbBreakFlag |= 2; \
		break; \
	} \

#define trlTraceMemRead(nAddr, nValue) \
	if (__builtin_expect(ReadCallback != nullptr, 0)) { \
		ReadCallback(nAddr, nValue); \
	} \

#define trlTraceMemWrite(nAddr, nValue) \
	if (__builtin_expect(WriteCallback != nullptr, 0)) { \
		WriteCallback(nAddr, nValue); \
	} \

u64 trlTimeGetNow();
s32 trlTimeGetElapsedTime(u64 x, u64 y);

void* trlMemCopy(void* dst, const void* src, size_t len);
void* trlMemAlloc(size_t s);
void trlMemFree(void* p);

#define TRL_COLORDMG 0
