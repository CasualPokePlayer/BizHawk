#ifndef RF5C164_H_
#define RF5C164_H_
#include <stdint.h>
#include "render_audio.h"

typedef struct {
	uint32_t cur_ptr;
	uint8_t  regs[7];
	uint8_t  sample;
	uint8_t  state;
} rf5c164_channel;

typedef struct {
	audio_source    *audio;
	uint32_t        cycle;
	uint32_t        clock_step;
	uint16_t        ram[64*1024];
	uint16_t        ram_bank;
	uint16_t        pending_address;
	int32_t         left;
	int32_t         right;
	rf5c164_channel channels[8];
	uint8_t         pending_byte;
	uint8_t         channel_enable;
	uint8_t         selected_channel;
	uint8_t         cur_channel;
	uint8_t         step;
	uint8_t         flags;
} rf5c164;

void rf5c164_init(rf5c164* pcm, uint32_t mclks, uint32_t divider);
void rf5c164_run(rf5c164* pcm, uint32_t cycle);
void rf5c164_write(rf5c164* pcm, uint16_t address, uint8_t value);
uint8_t rf5c164_read(rf5c164* pcm, uint16_t address);

#endif //RF5C164_H_
