#include "system.h"
#include "util.h"
#include "vdp.h"
#include "render.h"
#include "io.h"
#include "genesis.h"
#include "sms.h"

#include "../emulibc/emulibc.h"
#include "../emulibc/waterboxcore.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXPORT ECL_EXPORT

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

static time_t biz_time;

static time_t BizRtcCallback()
{
	return biz_time;
}

const u32 headless = 0;
const u32 exit_after = 0;
const u32 z80_enabled = 1;
const char* save_filename = "save.ram";
tern_node* config;
const u8 use_native_states = 1;

system_header *current_system;
system_media media;
system_type stype;

static vid_std video_standard;
static s32 last_width, last_height;
static s32 overscan_top, overscan_bot, overscan_left, overscan_right;

EXPORT bool Init(u8* rom, size_t sz)
{
	srand(time(NULL));
	//render_audio_initialized(RENDER_AUDIO_S16, 53693175 / (7 * 6 * 4), 2, 4, sizeof(int16_t));
	biz_time = 0;
	media.buffer = alloc_sealed(sz);
	memcpy(media.buffer, rom, sz);
	media.size = sz;
	stype = detect_system_type(&media);
	current_system = alloc_config_system(stype, &media, 0, 0);
	RtcCallback = BizRtcCallback;
	return !current_system;
}

EXPORT void GetMemoryAreas(MemoryArea *m)
{
}

static bool biz_lag;
static bool biz_started;
static bool biz_overscan;

typedef struct
{
	FrameInfo b;
	s64 Time;
	u32 P1Keys;
	u32 P2Keys;
	u32 Reset;
	u32 Overscan;
} MyFrameInfo;

static u32* fb;
static u8 last_fb;

EXPORT void FrameAdvance(MyFrameInfo* f)
{
	if (!f->Overscan)
	{
		overscan_top = overscan_bot = overscan_left = overscan_right = 0;
	}
	else
	{
		if (video_standard == VID_NTSC)
		{
			overscan_top = 11;
			overscan_bot = 8;
			overscan_left = 13;
			overscan_right = 14;
		}
		else
		{
			overscan_top = 30;
			overscan_bot = 24;
			overscan_left = 13;
			overscan_right = 14;
		}
	}

	if (f->Reset) current_system->soft_reset(current_system);

	for (u32 p = 0; p < 2;)
	{
		u32 keys = p++ ? f->P1Keys : f->P2Keys;
		for (u32 i = BUTTON_INVALID; i < NUM_GAMEPAD_BUTTONS;)
		{
			if (keys & (1 << i++))
				current_system->gamepad_down(current_system, p, i);
			else
				current_system->gamepad_up(current_system, p, i);
		}
	}

	biz_lag = true;
	biz_time = f->Time;

	fb = f->b.VideoBuffer;

	if (biz_started)
	{
		current_system->resume_context(current_system);
	}
	else
	{
		current_system->start_context(current_system, NULL);
		biz_started = true;
	}

	f->b.Width = last_width;
	f->b.Height = last_height;
	f->b.Samples = 0;
	//f->b.SoundBuffer
	f->b.Cycles = 0;
	f->b.Lagged = biz_lag;
}

void (*InputCallback)();

EXPORT void SetInputCallback(void (*callback)())
{
	InputCallback = callback;
}

uint32_t render_map_color(uint8_t r, uint8_t g, uint8_t b)
{
	return (0xFF << 24) | (r << 16) | (g << 8) | b;
}

uint8_t render_create_window(char *caption, uint32_t width, uint32_t height, window_close_handler close_handler)
{
	return 0;
}

void render_destroy_window(uint8_t which)
{
}

uint32_t *render_get_framebuffer(uint8_t which, int *pitch)
{
	*pitch = LINEBUF_SIZE * sizeof(uint32_t);
	if (which != last_fb) {
		*pitch = *pitch * 2;
	}

	if (which) {
		return fb + LINEBUF_SIZE;
	} else {
		return fb;
	}
}

void render_framebuffer_updated(u8 which, s32 width)
{
	s32 height = (video_standard == VID_NTSC ? 243 : 294) - (overscan_top + overscan_bot);
	width -= (overscan_left + overscan_right);
	s32 base_height = height;
	if (which != last_fb)
	{
		height *= 2;
		last_fb = which;
	}
	if (width != last_width || height != last_height)
	{
		last_width = width;
		last_height = height;
	}
	system_request_exit(current_system, 0);
}

u8 render_get_active_framebuffer(void)
{
	return 0;
}

void render_set_video_standard(vid_std std)
{
	video_standard = std;
}

s32 render_fullscreen(void)
{
	return 1;
}

u32 render_overscan_top()
{
	return overscan_top;
}

u32 render_overscan_bot()
{
	return overscan_bot;
}

void process_events()
{
	biz_lag = false;
	if (InputCallback)
		InputCallback();
}

void render_errorbox(char *title, char *message)
{
}
void render_warnbox(char *title, char *message)
{
}
void render_infobox(char *title, char *message)
{
}

uint8_t render_is_audio_sync(void)
{
	return 1;
}

uint8_t render_should_release_on_exit(void)
{
	return 0;
}

void render_buffer_consumed(audio_source *src)
{
}

void *render_new_audio_opaque(void)
{
	return NULL;
}

void render_free_audio_opaque(void *opaque)
{
}

void render_lock_audio(void)
{
}

void render_unlock_audio()
{
}

uint32_t render_min_buffered(void)
{
	return 4;
}

uint32_t render_audio_syncs_per_sec(void)
{
	return 0;
}

void render_audio_created(audio_source *src)
{
}

void render_do_audio_ready(audio_source *src)
{
	/*int16_t *tmp = src->front;
	src->front = src->back;
	src->back = tmp;
	src->front_populated = 1;
	src->buffer_pos = 0;
	if (all_sources_ready()) {
		int16_t buffer[8];
		int min_remaining_out;
		mix_and_convert((uint8_t *)buffer, sizeof(buffer), &min_remaining_out);
		retro_audio_sample_batch(buffer, sizeof(buffer)/(2*sizeof(*buffer)));
	}*/
}

void render_source_paused(audio_source *src, uint8_t remaining_sources)
{
}

void render_source_resumed(audio_source *src)
{
}

void render_set_external_sync(uint8_t ext_sync_on)
{
}

void bindings_set_mouse_mode(uint8_t mode)
{
}

void bindings_release_capture(void)
{
}

void bindings_reacquire_capture(void)
{
}

char *read_bundled_file(char *name, uint32_t *sizeret)
{
	return NULL;
}
