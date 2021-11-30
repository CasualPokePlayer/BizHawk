#include <string.h>
#include <stdlib.h>
#include "z80.h"

void z80_read_8(z80_context *context);
void z80_write_8(z80_context *context);
void z80_io_read8(z80_context *context);
void z80_io_write8(z80_context *context);
void init_z80_opts(z80_options * options, memmap_chunk const * chunks, uint32_t num_chunks, memmap_chunk const * io_chunks, uint32_t num_io_chunks, uint32_t clock_divider, uint32_t io_address_mask);
void z80_options_free(z80_options *opts);
z80_context * init_z80_context(z80_options *options);
void z80_sync_cycle(z80_context *context, uint32_t target_cycle);
void z80_run(z80_context *context, uint32_t target_cycle);
void z80_assert_reset(z80_context * context, uint32_t cycle);
void z80_clear_reset(z80_context * context, uint32_t cycle);
void z80_assert_busreq(z80_context * context, uint32_t cycle);
void z80_clear_busreq(z80_context * context, uint32_t cycle);
void z80_assert_nmi(z80_context *context, uint32_t cycle);
uint8_t z80_get_busack(z80_context * context, uint32_t cycle);
void z80_invalidate_code_range(z80_context *context, uint32_t startA, uint32_t endA);
void z80_adjust_cycles(z80_context * context, uint32_t deduction);
void z80_serialize(z80_context *context, serialize_buffer *buf);
void z80_deserialize(deserialize_buffer *buf, void *vcontext);
void zinsert_breakpoint(z80_context * context, uint16_t address, uint8_t * bp_handler);
void zremove_breakpoint(z80_context * context, uint16_t address);