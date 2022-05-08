#ifndef SEGACD_H_
#define SEGACD_H_
#include <stdint.h>
#include "genesis.h"
#include "cdd_mcu.h"
#include "rf5c164.h"

typedef struct {
	m68k_context    *m68k;
	system_media    *media;
	genesis_context *genesis;
	uint16_t        gate_array[0xC0];
	uint16_t        *rom;     //unaltered ROM, needed for mirrored locations
	uint16_t        *rom_mut; //ROM with low 16-bit of HINT vector modified by register write
	uint16_t        *prog_ram;
	uint16_t        *word_ram;
	uint8_t         *pcm_ram;
	uint8_t         *bram;
	uint32_t        stopwatch_cycle;
	uint32_t        int2_cycle;
	uint32_t        graphics_int_cycle;
	uint32_t        periph_reset_cycle;
	uint32_t        last_refresh_cycle;
	uint32_t        graphics_cycle;
	uint32_t        base;
	uint32_t        graphics_x;
	uint32_t        graphics_y;
	uint32_t        graphics_dx;
	uint32_t        graphics_dy;
	uint16_t        graphics_dst_x;
	uint8_t         graphics_pixels[4];
	uint8_t         timer_pending;
	uint8_t         timer_value;
	uint8_t         busreq;
	uint8_t         busack;
	uint8_t         reset;
	uint8_t         need_reset;
	uint8_t         memptr_start_index;
	rf5c164         pcm;
	lc8951          cdc;
	cdd_mcu         cdd;
	cdd_fader       fader;
	uint8_t         cdc_dst_low;
	uint8_t         cdc_int_ack;
	uint8_t         graphics_step;
	uint8_t         graphics_dst_y;
	uint8_t         enter_debugger;
	uint8_t         main_has_word2m;
	uint8_t         main_swap_request;
	uint8_t         bank_toggle;
	uint8_t         sub_paused_wordram;
} segacd_context;

segacd_context *alloc_configure_segacd(system_media *media, uint32_t opts, uint8_t force_region, rom_info *info);
memmap_chunk *segacd_main_cpu_map(segacd_context *cd, uint8_t cart_boot, uint32_t *num_chunks);
uint32_t gen_cycle_to_scd(uint32_t cycle, genesis_context *gen);
void scd_run(segacd_context *cd, uint32_t cycle);
void scd_adjust_cycle(segacd_context *cd, uint32_t deduction);

#endif //SEGACD_H_
