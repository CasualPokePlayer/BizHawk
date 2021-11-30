#ifndef M68K_H_
#define M68K_H_
#include "backend.h"

typedef struct {
	cpu_options gen;
} m68k_options;

typedef struct {
	m68k_options *opts;
	void *reset_handler;
	void *mem_pointers[8];
	uint32_t dregs[8];
	uint32_t aregs[8];
	uint32_t sync_cycle;
	uint32_t scratch2;
	uint32_t scratch1;
	uint32_t pc;
	uint32_t other_sp;
	uint32_t int_cycle;
	uint32_t cycles;
	uint16_t prefetch;
	uint8_t zflag;
	uint8_t xflag;
	uint8_t vflag;
	uint8_t status;
	uint8_t nflag;
	uint8_t int_priority;
	uint8_t int_pending_num;
	uint8_t int_pending;
	uint8_t int_num;
	uint8_t int_ack;
	uint8_t cflag;
	uint8_t ccr;
} m68k_context;

void m68k_execute(m68k_context *context, uint32_t target_cycle);
typedef m68k_context *(*m68k_reset_handler)(m68k_context *context);
void init_m68k_opts(m68k_options *opts, memmap_chunk * memmap, uint32_t num_chunks, uint32_t clock_divider);
m68k_context *init_68k_context(m68k_options * opts, m68k_reset_handler reset_handler);
void m68k_reset(m68k_context *context);
void m68k_print_regs(m68k_context *context);
#endif //M68K_H_
