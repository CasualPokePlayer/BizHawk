#ifndef LC8951_H_
#define LC8951_H_

#include <stdint.h>

typedef uint8_t (*lcd8951_byte_recv_fun)(void *data, uint8_t byte);

typedef struct {
	lcd8951_byte_recv_fun byte_handler;
	void     *handler_data;
	uint32_t cycle;
	uint32_t clock_step;
	uint32_t cycles_per_byte;
	uint32_t decode_end;
	uint32_t transfer_end;
	uint32_t next_byte_cycle;
	uint16_t sector_counter;

	uint8_t  buffer[0x4000];

	uint8_t  regs[16];
	uint8_t  comin[8];

	uint16_t dac;
	uint8_t  comin_write;
	uint8_t  comin_count;
	uint8_t  ifctrl;
	uint8_t  ctrl0;
	uint8_t  ctrl1;
	uint8_t  ar;
	uint8_t  ar_mask;
	uint8_t  sync_counter;
} lc8951;

void lc8951_init(lc8951 *context, lcd8951_byte_recv_fun byte_handler, void *handler_data);
void lc8951_set_dma_multiple(lc8951 *context, uint32_t multiple);
void lc8951_run(lc8951 *context, uint32_t cycle);
void lc8951_reg_write(lc8951 *context, uint8_t value);
uint8_t lc8951_reg_read(lc8951 *context);
void lc8951_ar_write(lc8951 *context, uint8_t value);
void lc8951_write_byte(lc8951 *context, uint32_t cycle, int sector_offset, uint8_t byte);
uint32_t lc8951_next_interrupt(lc8951 *context);
void lc8951_resume_transfer(lc8951 *context, uint32_t cycle);
void lc8951_adjust_cycles(lc8951 *context, uint32_t deduction);

#endif //LC8951_H_
