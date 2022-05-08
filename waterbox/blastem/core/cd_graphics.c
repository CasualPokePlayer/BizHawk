#include "cd_graphics.h"
#include "backend.h"

void cd_graphics_init(segacd_context *cd)
{
	cd->graphics_int_cycle = CYCLE_NEVER;
}

#define BIT_HFLIP 0x8000

static uint8_t get_src_pixel(segacd_context *cd)
{
	uint16_t x = cd->graphics_x >> 11;
	uint16_t y = cd->graphics_y >> 11;
	cd->graphics_x += cd->graphics_dx;
	cd->graphics_x &= 0xFFFFFF;
	cd->graphics_y += cd->graphics_dy;
	cd->graphics_y &= 0xFFFFFF;
	uint16_t stamp_shift, pixel_mask;
	uint16_t stamp_num_mask;
	if (cd->gate_array[GA_STAMP_SIZE] & BIT_STS) {
		//32x32 stamps
		stamp_shift = 5;
		pixel_mask = 0x1F;
		stamp_num_mask = 0x3FC;
	} else {
		//16x16 stamps
		stamp_shift = 4;
		pixel_mask = 0xF;
		stamp_num_mask = 0x3FF;
	}
	uint16_t stamp_x = x >> stamp_shift;
	uint16_t stamp_y = y >> stamp_shift;
	uint16_t max, base_mask;
	uint32_t row_shift;
	if (cd->gate_array[GA_STAMP_SIZE] & BIT_SMS) {
		max = 4096 >> stamp_shift;
		base_mask = 0xE000 << ((5 - stamp_shift) << 1);
		//128 stamps in 32x32 mode, 256 stamps in 16x16 mode
		row_shift = 12 - stamp_shift;
	} else {
		max = 256 >> stamp_shift;
		base_mask = 0xFFE0 << ((5 - stamp_shift) << 1);
		//8 stamps in 32x32 mode, 16 stamps in 16x16 mode
		row_shift = 8 - stamp_shift;
	}
	if (stamp_x >= max || stamp_y >= max) {
		if (cd->gate_array[GA_STAMP_SIZE] & BIT_RPT) {
			stamp_x &= max - 1;
			stamp_y &= max - 1;
		} else {
			return 0;
		}
	}
	uint32_t address = (cd->gate_array[GA_STAMP_MAP_BASE] & base_mask) << 1;
	address += (stamp_y << row_shift) + stamp_x;
	uint16_t stamp_def = cd->word_ram[address];
	uint16_t stamp_num = stamp_def & stamp_num_mask;
	if (!stamp_num) {
		//manual says stamp 0 can't be used, I assume that means it's treated as transparent
		return 0;
	}
	uint16_t pixel_x = x & pixel_mask;
	uint16_t pixel_y = y & pixel_mask;
	if (stamp_def & BIT_HFLIP) {
		pixel_x = pixel_mask - pixel_x;
	}
	uint16_t tmp;
	switch (stamp_def >> 13 & 3)
	{
	case 0:
		break;
	case 1:
		tmp = pixel_y;
		pixel_y = pixel_x;
		pixel_x = pixel_mask - tmp;
		break;
	case 2:
		pixel_y = pixel_mask - pixel_y;
		pixel_x = pixel_mask - pixel_x;
		break;
	case 3:
		tmp = pixel_y;
		pixel_y = pixel_mask - pixel_x;
		pixel_x = tmp;
		break;
	}
	uint16_t cell_x = pixel_x >> 3;
	uint32_t pixel_address = stamp_num << 6;
	pixel_address += (pixel_y << 1) + (cell_x << (stamp_shift + 1)) + (pixel_x >> 2 & 1);
	uint16_t word = cd->word_ram[pixel_address];
	switch (pixel_x & 3)
	{
	default:
	case 0:
		return word >> 12;
	case 1:
		return word >> 8 & 0xF;
	case 2:
		return word >> 4 & 0xF;
	case 3:
		return word & 0xF;
	}

}

enum {
	FETCH_X,
	FETCH_Y,
	FETCH_DX,
	FETCH_DY,
	PIXEL0,
	PIXEL1,
	PIXEL2,
	PIXEL3,
	DRAW
};

void draw_pixels(segacd_context *cd)
{
	uint16_t to_draw = 4 - (cd->graphics_dst_x & 3);
	uint16_t x_end = cd->gate_array[GA_IMAGE_BUFFER_HDOTS] + (cd->gate_array[GA_IMAGE_BUFFER_OFFSET] & 3);
	if (cd->graphics_dst_x + to_draw > x_end) {
		to_draw = cd->gate_array[GA_IMAGE_BUFFER_HDOTS] + (cd->gate_array[GA_IMAGE_BUFFER_OFFSET] & 3) - cd->graphics_dst_x;
	}
	for(uint16_t i = 0; i < to_draw; i++)
	{
		uint32_t dst_address = cd->gate_array[GA_IMAGE_BUFFER_START] << 1;
		dst_address += cd->graphics_dst_y << 1;
		dst_address += cd->graphics_dst_x >> 2 & 1;
		dst_address += ((cd->graphics_dst_x >> 3) * (cd->gate_array[GA_IMAGE_BUFFER_VCELLS] + 1)) << 4;
		uint16_t pixel_shift = 12 - 4 * (cd->graphics_dst_x & 3);
		uint16_t pixel = cd->graphics_pixels[i] << pixel_shift;
		uint16_t src_mask_check = 0xF << pixel_shift;
		uint16_t src_mask_keep = ~src_mask_check;
		pixel &= src_mask_check;
		switch (cd->gate_array[1] >> 3 & 3)
		{
		case 0:
			//priority mode off
			cd->word_ram[dst_address] &= src_mask_keep;
			cd->word_ram[dst_address] |= pixel;
			break;
		case 1:
			//underwrite
			if (pixel && ! (cd->word_ram[dst_address] & src_mask_check)) {
				cd->word_ram[dst_address] &= src_mask_keep;
				cd->word_ram[dst_address] |= pixel;
			}
			break;
		case 2:
			//overwrite
			if (pixel) {
				cd->word_ram[dst_address] &= src_mask_keep;
				cd->word_ram[dst_address] |= pixel;
			}
			break;
		}
		cd->graphics_dst_x++;
	}
	if (cd->graphics_dst_x == x_end) {
		cd->graphics_dst_y++;
		--cd->gate_array[GA_IMAGE_BUFFER_LINES];
		cd->gate_array[GA_TRACE_VECTOR_BASE] += 2;
		cd->graphics_step = FETCH_X;
	} else {
		cd->graphics_step = PIXEL0;
	}
}

#define CHECK_CYCLES cd->graphics_step++; if(cd->graphics_cycle >= cycle) break
#define CHECK_ONLY if(cd->graphics_cycle >= cycle) break

static void do_graphics(segacd_context *cd, uint32_t cycle)
{
	if (!cd->gate_array[GA_IMAGE_BUFFER_LINES]) {
		return;
	}
	while (cd->graphics_cycle < cycle)
	{
		switch (cd->graphics_step)
		{
		case FETCH_X:
			cd->graphics_x = cd->word_ram[cd->gate_array[GA_TRACE_VECTOR_BASE] << 1] << 8;
			cd->graphics_cycle += 3*4;
			cd->graphics_dst_x = cd->gate_array[GA_IMAGE_BUFFER_OFFSET] & 3;
			CHECK_CYCLES;
		case FETCH_Y:
			cd->graphics_y = cd->word_ram[(cd->gate_array[GA_TRACE_VECTOR_BASE] << 1) + 1] << 8;
			cd->graphics_cycle += 2*4;
			CHECK_CYCLES;
		case FETCH_DX:
			cd->graphics_dx = cd->word_ram[(cd->gate_array[GA_TRACE_VECTOR_BASE] << 1) + 2];
			if (cd->graphics_dx & 0x8000) {
				cd->graphics_dx |= 0xFF0000;
			}
			cd->graphics_cycle += 2*4;
			CHECK_CYCLES;
		case FETCH_DY:
			cd->graphics_dy = cd->word_ram[(cd->gate_array[GA_TRACE_VECTOR_BASE] << 1) + 3];
			if (cd->graphics_dy & 0x8000) {
				cd->graphics_dy |= 0xFF0000;
			}
			cd->graphics_cycle += 2*4;
			CHECK_CYCLES;
		case PIXEL0:
			cd->graphics_pixels[0] = get_src_pixel(cd);
			cd->graphics_cycle += 2*4;
			if ((cd->graphics_dst_x & 3) == 3 || (cd->graphics_dst_x + 1 == cd->gate_array[GA_IMAGE_BUFFER_HDOTS] + (cd->gate_array[GA_IMAGE_BUFFER_OFFSET] & 3))) {
				cd->graphics_step = DRAW;
				CHECK_ONLY;
				goto draw;
			} else {
				CHECK_CYCLES;
			}
		case PIXEL1:
			cd->graphics_pixels[1] = get_src_pixel(cd);
			cd->graphics_cycle += 2*4;
			if ((cd->graphics_dst_x & 3) == 2 || (cd->graphics_dst_x + 2 == cd->gate_array[GA_IMAGE_BUFFER_HDOTS] + (cd->gate_array[GA_IMAGE_BUFFER_OFFSET] & 3))) {
				cd->graphics_step = DRAW;
				CHECK_ONLY;
				goto draw;
			} else {
				CHECK_CYCLES;
			}
		case PIXEL2:
			cd->graphics_pixels[2] = get_src_pixel(cd);
			cd->graphics_cycle += 2*4;
			if ((cd->graphics_dst_x & 3) == 1 || (cd->graphics_dst_x + 3 == cd->gate_array[GA_IMAGE_BUFFER_HDOTS] + (cd->gate_array[GA_IMAGE_BUFFER_OFFSET] & 3))) {
				cd->graphics_step = DRAW;
				CHECK_ONLY;
				goto draw;
			} else {
				CHECK_CYCLES;
			}
		case PIXEL3:
			cd->graphics_pixels[3] = get_src_pixel(cd);
			cd->graphics_cycle += 2*4;
			CHECK_CYCLES;
draw:
		case DRAW:
			draw_pixels(cd);
			cd->graphics_cycle += 1*4;
			if (!cd->gate_array[GA_IMAGE_BUFFER_LINES]) {
				return;
			}
			CHECK_ONLY;
		}
	}
}

void cd_graphics_run(segacd_context *cd, uint32_t cycle)
{
	while (cd->graphics_cycle < cycle)
	{
		if (cd->gate_array[GA_STAMP_SIZE] & BIT_GRON) {
			do_graphics(cd, cycle);
			//end calculation and actual emulated execution time probably don't 100% line up yet
			//deal with that here for now
			for(; cd->graphics_cycle < cycle; cd->graphics_cycle += 4)
			{
			}
			if (cd->graphics_cycle >= cd->graphics_int_cycle) {
				printf("graphics end %u\n", cd->graphics_cycle);
				cd->gate_array[GA_STAMP_SIZE] &= ~BIT_GRON;
				break;
			}
		} else {
			cd->graphics_cycle = cycle;
		}
	}
}
void cd_graphics_start(segacd_context *cd)
{
	if (!(cd->gate_array[GA_STAMP_SIZE] & BIT_GRON)) {

		cd->gate_array[GA_STAMP_SIZE] |= BIT_GRON;
		//Manual scan is bad, but formula appears to be
		// vsize * (13 + 2 * hoffset + 9 * (hdots + hoffset - 1))
		//with an additional 13? cycle setup cost per line
		uint32_t lines = cd->gate_array[GA_IMAGE_BUFFER_LINES];
		uint32_t hdots = cd->gate_array[GA_IMAGE_BUFFER_HDOTS];
		uint32_t hoffset = cd->gate_array[GA_IMAGE_BUFFER_OFFSET] & 3;
		uint16_t pm = cd->gate_array[1] >> 3 & 3;
		cd->graphics_int_cycle = cd->graphics_cycle + 4 * lines * (13 + 2 * hoffset + 9 * (hdots + hoffset - 1));
		cd->graphics_dst_y = cd->gate_array[GA_IMAGE_BUFFER_OFFSET] >> 3;
		printf("graphics start @ %u, %u lines, %u hdots, pm = %u, hoff = %u, voff = %u, addr = %X\n", cd->graphics_cycle, lines, hdots, pm, hoffset, cd->graphics_dst_y, cd->gate_array[GA_IMAGE_BUFFER_START]);
		cd->graphics_step = FETCH_X;
	} else {
		printf("graphics start ignored @ %u\n", cd->graphics_cycle);
	}

}
