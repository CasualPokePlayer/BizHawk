#include "trlHeader.h"

extern s32 g_nCgbSndBufPos;
extern s32 g_nCgbSndTicks;
// 1048576 / (188 / 8) * 2 Hz
// ie rate sound buffer is filled
u64 TimeTicks;

u64 trlTimeGetNow() {
	return (((TimeTicks + g_nCgbSndBufPos) * 188 + ((188 - g_nCgbSndTicks) * 2 * 8)) / (1048576 * 2 * 8));
}

s32 trlTimeGetElapsedTime(u64 x, u64 y) {
	return y - x;
}

void* trlMemCopy(void* dst, const void* src, size_t len) {
	return memcpy(dst, src, len);
}

void* trlMemAlloc(size_t s) {
	return calloc(sizeof(u8), s);
}

void trlMemFree(void* p) {
	free(p);
}
