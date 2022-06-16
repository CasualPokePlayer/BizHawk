#include <tic80.h>
#include <tic.h>

#include <emulibc.h>
#include <waterboxcore.h>

#include <string.h>

static tic80* tic;

ECL_EXPORT bool Init(u8* rom, u32 sz)
{
	tic = tic80_create(TIC80_SAMPLERATE, TIC80_PIXEL_COLOR_BGRA8888);
	if (!tic)
	{
		return false;
	}

	tic80_load(tic, rom, sz);
	return true;
}

int dummy[1];

ECL_EXPORT void GetMemoryAreas(MemoryArea* m)
{
	m[0].Data = dummy;
	m[0].Name = "dummy";
	m[0].Size = sizeof (dummy);
	m[0].Flags = MEMORYAREA_FLAGS_WORDSIZE4 | MEMORYAREA_FLAGS_WRITABLE;
}

typedef struct
{
	FrameInfo b;
	tic80_input inputs;
	bool crop;
} MyFrameInfo;

bool lagged;
void (*inputcb)() = 0;

ECL_EXPORT void FrameAdvance(MyFrameInfo* f)
{
	lagged = true;

	tic80_tick(tic, f->inputs);
	tic80_sound(tic);

	f->b.Samples = tic->samples.count / TIC80_SAMPLE_CHANNELS;
	memcpy(f->b.SoundBuffer, tic->samples.buffer, tic->samples.count * TIC80_SAMPLESIZE);

	u32* src;
	u32 width;
	u32 height;
	if (f->crop)
	{
		src = (u32*)tic->screen + (TIC80_FULLWIDTH * TIC80_OFFSET_TOP) + TIC80_OFFSET_LEFT;
		width = TIC80_WIDTH;
		height = TIC80_HEIGHT;
	}
	else
	{
		src = tic->screen;
		width = TIC80_FULLWIDTH;
		height = TIC80_FULLHEIGHT;
	}
	
	u32* dst = f->b.VideoBuffer;
	for (u32 i = 0; i < f->b.Height; i++)
	{
		memcpy(dst, src, width * sizeof (u32));
		dst += width;
		src += TIC80_FULLWIDTH;
	}

	f->b.Width = width;
	f->b.Height = height;

	f->b.Lagged = lagged;
}

ECL_EXPORT void SetInputCallback(void (*callback)())
{
	inputcb = callback;
}
