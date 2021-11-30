#ifndef Z80_H_
#define Z80_H_
#include "backend.h"

typedef struct {
	cpu_options gen;
} z80_options;

typedef struct {
	z80_options *opts;
	memmap_chunk *io_map;
	void *system;
	uint8_t *fastread[64];
	uint8_t *fastwrite[64];
	uint8_t *mem_pointers[4];
	uint32_t sync_cycle;
	uint32_t nmi_cycle;
	uint32_t io_mask;
	uint32_t io_chunks;
	uint32_t int_end_cycle;
	uint32_t int_cycle;
	uint32_t cycles;
	uint16_t wz;
	uint16_t sp;
	uint16_t scratch2;
	uint16_t scratch1;
	uint16_t pc;
	uint16_t iy;
	uint16_t ix;
	uint8_t main[8];
	uint8_t alt[8];
	uint8_t zflag;
	uint8_t rhigh;
	uint8_t reset;
	uint8_t r;
	uint8_t pvflag;
	uint8_t nflag;
	uint8_t last_flag_result;
	uint8_t int_value;
	uint8_t imode;
	uint8_t iff2;
	uint8_t iff1;
	uint8_t i;
	uint8_t chflags;
	uint8_t busreq;
	uint8_t busack;
} z80_context;

void z80_execute(z80_context *context, uint32_t target_cycle);
void init_z80_opts(z80_options * options, memmap_chunk const * chunks, uint32_t num_chunks, memmap_chunk const * io_chunks, uint32_t num_io_chunks, uint32_t clock_divider, uint32_t io_address_mask);
z80_context * init_z80_context(z80_options *options);
void z80_run(z80_context *context, uint32_t target_cycle);
void z80_assert_reset(z80_context * context, uint32_t cycle);
void z80_clear_reset(z80_context * context, uint32_t cycle);
void z80_assert_busreq(z80_context * context, uint32_t cycle);
void z80_clear_busreq(z80_context * context, uint32_t cycle);
void z80_assert_nmi(z80_context *context, uint32_t cycle);
uint8_t z80_get_busack(z80_context * context, uint32_t cycle);
void z80_invalidate_code_range(z80_context *context, uint32_t start, uint32_t end);
void z80_adjust_cycles(z80_context * context, uint32_t deduction);
void z80_serialize(z80_context *context, serialize_buffer *buf);
void z80_deserialize(deserialize_buffer *buf, void *vcontext);
void zinsert_breakpoint(z80_context * context, uint16_t address, uint8_t * bp_handler);
void zremove_breakpoint(z80_context * context, uint16_t address);
void z80_options_free(z80_options *opts);
void z80_sync_cycle(z80_context *context, uint32_t target_cycle);
#endif //Z80_H_
