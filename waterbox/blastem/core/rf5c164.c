#include <stdio.h>
#include "rf5c164.h"

enum {
	ENV,
	PAN,
	FDL,
	FDH,
	LSL,
	LSH,
	ST,
	CTRL,
	CHAN_ENABLE
};

enum {
	START,
	NORMAL,
	LOOP
};

#define FLAG_SOUNDING 0x80
#define FLAG_PENDING  0x01

void rf5c164_init(rf5c164* pcm, uint32_t mclks, uint32_t divider)
{
	pcm->audio = render_audio_source("rf5c164", mclks, divider * 384, 2);
	pcm->clock_step = divider * 4;
}

//48 cycles per channel
//1 external write per 16 cycles
//3 external writes per channel/sample
// TCE pulse width is 200ns @ 10Mhz aka 2 cycles
// total cycle is longer than TCE pulse, guessing 4 cycles
// 12 memory access slots per channel sample
// 3 for external memory writes
// 1 for internal register writes?
// 1 for refresh?
// 6 for register reads?
// or maybe 7 for register reads and writes happen when register is read?

#define CHECK pcm->cycle += pcm->clock_step; pcm->step++; if (pcm->cycle >= cycle) break
#define CHECK_LOOP pcm->cycle += pcm->clock_step; pcm->step = 0; if (pcm->cycle >= cycle) break

static void write_if_not_sounding(rf5c164* pcm)
{
	if (!(pcm->flags & FLAG_SOUNDING) && (pcm->flags & FLAG_PENDING)
		&& pcm->pending_address >= 0x1000) {
		pcm->ram[(pcm->pending_address & 0xFFF) | pcm->ram_bank] = pcm->pending_byte;
		pcm->flags &= ~FLAG_PENDING;
	}
}

static void write_always(rf5c164* pcm)
{
	if ((pcm->flags & FLAG_PENDING) && pcm->pending_address >= 0x1000) {
		pcm->ram[(pcm->pending_address & 0xFFF) | pcm->ram_bank] = pcm->pending_byte;
		pcm->flags &= ~FLAG_PENDING;
	}
}

void rf5c164_run(rf5c164* pcm, uint32_t cycle)
{
	//TODO: Timing of this is all educated guesses based on documentation, do some real measurements
	while (pcm->cycle < cycle)
	{
	switch (pcm->step)
	{
	case 0:
		//handle internal memory write
		// RF5C164 datasheet seems to suggest only 1 "internal memory" write every 48 cycles when the chip is not sounding (globally)
		// and 1 write every 384 cycles when the chip is sounding (globally). However, games seem to expect to be able to write faster than that
		// RF5C68 datasheet suggests internal memory writes are unrestricted regardless of sounding status
		/*if ((pcm->cur_channel == pcm->selected_channel || !(pcm->flags & FLAG_SOUNDING)) && (pcm->flags & FLAG_PENDING)
			&& pcm->pending_address <= ST
		) {
			printf("pcm_write commit chan %d, %X - %X @ %u\n", pcm->selected_channel, pcm->pending_address, pcm->pending_byte, pcm->cycle);
			pcm->channels[pcm->selected_channel].regs[pcm->pending_address] = pcm->pending_byte;
			pcm->flags &= ~FLAG_PENDING;
		}*/
		write_if_not_sounding(pcm);
		CHECK;
	case 1:
		if ((pcm->flags & FLAG_SOUNDING) && !(pcm->channel_enable & (1 << pcm->cur_channel))) {
			if (pcm->channels[pcm->cur_channel].state == START) {
				pcm->channels[pcm->cur_channel].cur_ptr = pcm->channels[pcm->cur_channel].regs[ST] << 19;
				//printf("chan %d START %X (%X raw)\n", pcm->cur_channel, pcm->channels[pcm->cur_channel].cur_ptr >> 11, pcm->channels[pcm->cur_channel].cur_ptr);
				pcm->channels[pcm->cur_channel].state = NORMAL;
			} else if (pcm->channels[pcm->cur_channel].state == LOOP) {
				pcm->channels[pcm->cur_channel].cur_ptr = (pcm->channels[pcm->cur_channel].regs[LSH] << 19) | (pcm->channels[pcm->cur_channel].regs[LSL] << 11);
				//printf("chan %d LOOP %X (%X raw)\n", pcm->cur_channel, pcm->channels[pcm->cur_channel].cur_ptr >> 11, pcm->channels[pcm->cur_channel].cur_ptr);
				pcm->channels[pcm->cur_channel].state = NORMAL;
			}
		}
		write_if_not_sounding(pcm);
		CHECK;
	case 2: {
		if ((pcm->flags & FLAG_SOUNDING) && !(pcm->channel_enable & (1 << pcm->cur_channel))) {
			uint8_t byte = pcm->ram[pcm->channels[pcm->cur_channel].cur_ptr >> 11];
			if (byte == 0xFF) {
				pcm->channels[pcm->cur_channel].state = LOOP;
			} else {
				pcm->channels[pcm->cur_channel].sample = byte;
			}
		}
		write_if_not_sounding(pcm);
		CHECK;
	}
	case 3:
		write_always(pcm);
		CHECK;
	case 4:
		if ((pcm->flags & FLAG_SOUNDING) && !(pcm->channel_enable & (1 << pcm->cur_channel))) {
			pcm->channels[pcm->cur_channel].cur_ptr += (pcm->channels[pcm->cur_channel].regs[FDH] << 8) | pcm->channels[pcm->cur_channel].regs[FDL];
			pcm->channels[pcm->cur_channel].cur_ptr &= 0x7FFFFFF;
		}
		write_if_not_sounding(pcm);
		CHECK;
	case 5:
		write_if_not_sounding(pcm);
		CHECK;
	case 6:
		write_if_not_sounding(pcm);
		CHECK;
	case 7:
		write_always(pcm);
		CHECK;
	case 8:
		write_if_not_sounding(pcm);
		CHECK;
	case 9:
		if ((pcm->flags & FLAG_SOUNDING) && !(pcm->channel_enable & (1 << pcm->cur_channel))) {
			int16_t sample = pcm->channels[pcm->cur_channel].sample & 0x7F;
			if (!(pcm->channels[pcm->cur_channel].sample & 0x80)) {
				sample = -sample;
			}
			sample *= pcm->channels[pcm->cur_channel].regs[ENV];
			int16_t left = (sample * (pcm->channels[pcm->cur_channel].regs[PAN] >> 4)) >> 5;
			int16_t right = (sample * (pcm->channels[pcm->cur_channel].regs[PAN] & 0xF)) >> 5;
			//printf("chan %d, raw %X, sample %d, left %d, right %d, ptr %X (raw %X)\n", pcm->cur_channel, pcm->channels[pcm->cur_channel].sample, sample, left, right, pcm->channels[pcm->cur_channel].cur_ptr >> 11, pcm->channels[pcm->cur_channel].cur_ptr);
			pcm->left += left;
			pcm->right += right;
		}
		write_if_not_sounding(pcm);
		CHECK;
	case 10:
		//refresh?
		//does refresh happen at the same rate when sounding disabled? warning in sega docs suggests maybe not
		write_if_not_sounding(pcm);
		CHECK;
	case 11:
		write_always(pcm);
		pcm->cur_channel++;
		pcm->cur_channel &= 7;
		if (!pcm->cur_channel) {
			if (pcm->left > INT16_MAX) {
				pcm->left = INT16_MAX;
			} else if (pcm->left < INT16_MIN) {
				pcm->left = INT16_MIN;
			}
			if (pcm->right > INT16_MAX) {
				pcm->right = INT16_MAX;
			} else if (pcm->right < INT16_MIN) {
				pcm->right = INT16_MIN;
			}
			render_put_stereo_sample(pcm->audio, pcm->left, pcm->right);
			pcm->left = pcm->right = 0;
		}
		CHECK_LOOP;
	}
	}
}

void rf5c164_write(rf5c164* pcm, uint16_t address, uint8_t value)
{
	//printf("pcm_write %X - %X @ %u\n", address, value, pcm->cycle);
	if (address == CTRL) {
		pcm->flags &= ~FLAG_SOUNDING;
		pcm->flags |= value & FLAG_SOUNDING;
		if (value & 0x40) {
			pcm->selected_channel = value & 0x7;
			//printf("selected channel %d\n", pcm->selected_channel);
		} else {
			pcm->ram_bank = value << 12 & 0xF000;
			//printf("selected RAM bank %X\n", pcm->ram_bank);
		}
		if (!(pcm->flags & FLAG_SOUNDING)) {
			pcm->left = pcm->right = 0;
		}
	} else if (address == CHAN_ENABLE) {
		uint8_t changed = pcm->channel_enable ^ value;
		pcm->channel_enable = value;
		for (int i = 0; i < 8; i++)
		{
			int mask = 1 << i;
			if ((changed & mask) && !(mask & value)) {
				pcm->channels[i].state = START;
			}
		}
	} else if (address <= ST) {
		//See note in first step of rf5c164_run
		pcm->channels[pcm->selected_channel].regs[address] = value;
	} else {
		pcm->pending_address = address;
		pcm->pending_byte = value;
		pcm->flags |= FLAG_PENDING;
	}
}

uint8_t rf5c164_read(rf5c164* pcm, uint16_t address)
{
	if (address >= 0x10 && address < 0x20) {
		uint16_t chan = address >> 1 & 0x7;
		if (address & 1) {
			return pcm->channels[chan].cur_ptr >> 19;
		} else {
			return pcm->channels[chan].cur_ptr >> 11;
		}
	} else if (address >= 0x1000 && !(pcm->flags & FLAG_SOUNDING)) {
		return pcm->ram[pcm->ram_bank | (address & 0xFFF)];
	} else {
		return 0xFF;
	}
}
