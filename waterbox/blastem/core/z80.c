#include "z80.h"
#include "util.h"
#include <stdlib.h>
#include "z80_util.h"

static void unimplemented(z80_context *context, uint32_t target_cycle)
{
	fatal_error("Unimplemented instruction\n");
}

typedef void (*impl_fun)(z80_context *context, uint32_t target_cycle);
static impl_fun impl_cb[256];
static impl_fun impl_ed[256];
static impl_fun impl_dded[256];
static impl_fun impl_fded[256];
static impl_fun impl_ddcb[256];
static impl_fun impl_fdcb[256];
static impl_fun impl_dd[256];
static impl_fun impl_fd[256];
static impl_fun impl_main[256];
void rlc_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[0] << 1 | context->main[0] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rlc_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[1] << 1 | context->main[1] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rlc_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[2] << 1 | context->main[2] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rlc_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[3] << 1 | context->main[3] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rlc_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[4] << 1 | context->main[4] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rlc_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[5] << 1 | context->main[5] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rlc_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1 | tmp >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void rlc_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rrc_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[0] = context->main[0] >> 1 | context->main[0] << (8 - 1);
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->chflags = (context->chflags & ~128U) | (context->main[0] & 128U);
	gen_tmp8__ = (context->main[0] ^ (context->main[0] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rrc_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[1] = context->main[1] >> 1 | context->main[1] << (8 - 1);
	context->zflag = context->main[1] == 0;
	context->last_flag_result = context->main[1];
	context->chflags = (context->chflags & ~128U) | (context->main[1] & 128U);
	gen_tmp8__ = (context->main[1] ^ (context->main[1] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rrc_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[2] = context->main[2] >> 1 | context->main[2] << (8 - 1);
	context->zflag = context->main[2] == 0;
	context->last_flag_result = context->main[2];
	context->chflags = (context->chflags & ~128U) | (context->main[2] & 128U);
	gen_tmp8__ = (context->main[2] ^ (context->main[2] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rrc_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[3] = context->main[3] >> 1 | context->main[3] << (8 - 1);
	context->zflag = context->main[3] == 0;
	context->last_flag_result = context->main[3];
	context->chflags = (context->chflags & ~128U) | (context->main[3] & 128U);
	gen_tmp8__ = (context->main[3] ^ (context->main[3] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rrc_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[4] = context->main[4] >> 1 | context->main[4] << (8 - 1);
	context->zflag = context->main[4] == 0;
	context->last_flag_result = context->main[4];
	context->chflags = (context->chflags & ~128U) | (context->main[4] & 128U);
	gen_tmp8__ = (context->main[4] ^ (context->main[4] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rrc_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[5] = context->main[5] >> 1 | context->main[5] << (8 - 1);
	context->zflag = context->main[5] == 0;
	context->last_flag_result = context->main[5];
	context->chflags = (context->chflags & ~128U) | (context->main[5] & 128U);
	gen_tmp8__ = (context->main[5] ^ (context->main[5] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rrc_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	tmp = tmp >> 1 | tmp << (8 - 1);
	context->zflag = tmp == 0;
	context->last_flag_result = tmp;
	context->chflags = (context->chflags & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void rrc_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] >> 1 | context->main[7] << (8 - 1);
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	context->chflags = (context->chflags & ~128U) | (context->main[7] & 128U);
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rl_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[0] << 1 | context->main[0] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rl_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[1] << 1 | context->main[1] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rl_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[2] << 1 | context->main[2] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rl_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[3] << 1 | context->main[3] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rl_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[4] << 1 | context->main[4] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rl_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[5] << 1 | context->main[5] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rl_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1 | tmp >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void rl_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rr_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[0] >> 1 | context->main[0] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rr_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[1] >> 1 | context->main[1] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rr_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[2] >> 1 | context->main[2] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rr_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[3] >> 1 | context->main[3] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rr_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[4] >> 1 | context->main[4] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rr_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[5] >> 1 | context->main[5] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void rr_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp16__ = tmp >> 1 | tmp << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void rr_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] >> 1 | context->main[7] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sla_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[0] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sla_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[1] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sla_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[2] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sla_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[3] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sla_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[4] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sla_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[5] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sla_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void sla_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sra_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = (context->main[0] >> 1) | (context->main[0] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[0] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sra_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = (context->main[1] >> 1) | (context->main[1] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[1] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sra_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = (context->main[2] >> 1) | (context->main[2] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[2] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sra_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = (context->main[3] >> 1) | (context->main[3] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[3] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sra_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = (context->main[4] >> 1) | (context->main[4] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[4] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sra_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = (context->main[5] >> 1) | (context->main[5] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[5] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sra_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp16__ = (tmp >> 1) | (tmp & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (tmp << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void sra_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = (context->main[7] >> 1) | (context->main[7] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[7] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void sll_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	gen_tmp16__ = context->main[0] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[0] = 1 | context->main[0];
	gen_tmp8__ = (context->main[0] ^ (context->main[0] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
}
void sll_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	gen_tmp16__ = context->main[1] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[1] = 1 | context->main[1];
	gen_tmp8__ = (context->main[1] ^ (context->main[1] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
}
void sll_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	gen_tmp16__ = context->main[2] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[2] = 1 | context->main[2];
	gen_tmp8__ = (context->main[2] ^ (context->main[2] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
}
void sll_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	gen_tmp16__ = context->main[3] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[3] = 1 | context->main[3];
	gen_tmp8__ = (context->main[3] ^ (context->main[3] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
}
void sll_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	gen_tmp16__ = context->main[4] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[4] = 1 | context->main[4];
	gen_tmp8__ = (context->main[4] ^ (context->main[4] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
}
void sll_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	gen_tmp16__ = context->main[5] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[5] = 1 | context->main[5];
	gen_tmp8__ = (context->main[5] ^ (context->main[5] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
}
void sll_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	tmp = 1 | tmp;
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void sll_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	gen_tmp16__ = context->main[7] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[7] = 1 | context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
}
void srl_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[0] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[0] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void srl_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[1] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[1] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void srl_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[2] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[2] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void srl_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[3] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[3] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void srl_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[4] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[4] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void srl_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[5] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[5] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void srl_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp16__ = tmp >> 1;
	context->chflags = (context->chflags & ~128U) | (tmp << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void srl_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[7] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
}
void bit_reg_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[0];
	tmp = context->main[0] & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[1];
	tmp = context->main[1] & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[2];
	tmp = context->main[2] & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[3];
	tmp = context->main[3] & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[4];
	tmp = context->main[4] & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[5];
	tmp = context->main[5] & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_hl_B_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_reg_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->last_flag_result = context->main[7];
	tmp = context->main[7] & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void res_reg_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -2;
}
void res_reg_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -2;
}
void res_reg_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -2;
}
void res_reg_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -2;
}
void res_reg_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -2;
}
void res_reg_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -2;
}
void res_hl_B_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -2;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -2;
}
void res_reg_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -3;
}
void res_reg_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -3;
}
void res_reg_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -3;
}
void res_reg_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -3;
}
void res_reg_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -3;
}
void res_reg_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -3;
}
void res_hl_B_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -3;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -3;
}
void res_reg_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -5;
}
void res_reg_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -5;
}
void res_reg_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -5;
}
void res_reg_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -5;
}
void res_reg_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -5;
}
void res_reg_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -5;
}
void res_hl_B_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -5;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -5;
}
void res_reg_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -9;
}
void res_reg_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -9;
}
void res_reg_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -9;
}
void res_reg_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -9;
}
void res_reg_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -9;
}
void res_reg_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -9;
}
void res_hl_B_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -9;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -9;
}
void res_reg_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -17;
}
void res_reg_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -17;
}
void res_reg_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -17;
}
void res_reg_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -17;
}
void res_reg_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -17;
}
void res_reg_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -17;
}
void res_hl_B_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -17;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -17;
}
void res_reg_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -33;
}
void res_reg_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -33;
}
void res_reg_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -33;
}
void res_reg_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -33;
}
void res_reg_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -33;
}
void res_reg_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -33;
}
void res_hl_B_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -33;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -33;
}
void res_reg_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -65;
}
void res_reg_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -65;
}
void res_reg_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -65;
}
void res_reg_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -65;
}
void res_reg_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -65;
}
void res_reg_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -65;
}
void res_hl_B_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -65;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -65;
}
void res_reg_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] & -129;
}
void res_reg_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] & -129;
}
void res_reg_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] & -129;
}
void res_reg_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] & -129;
}
void res_reg_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] & -129;
}
void res_reg_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] & -129;
}
void res_hl_B_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 & -129;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void res_reg_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] & -129;
}
void set_reg_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 1;
}
void set_reg_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 1;
}
void set_reg_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 1;
}
void set_reg_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 1;
}
void set_reg_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 1;
}
void set_reg_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 1;
}
void set_hl_B_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 1;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 1;
}
void set_reg_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 2;
}
void set_reg_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 2;
}
void set_reg_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 2;
}
void set_reg_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 2;
}
void set_reg_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 2;
}
void set_reg_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 2;
}
void set_hl_B_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 2;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 2;
}
void set_reg_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 4;
}
void set_reg_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 4;
}
void set_reg_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 4;
}
void set_reg_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 4;
}
void set_reg_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 4;
}
void set_reg_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 4;
}
void set_hl_B_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 4;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 4;
}
void set_reg_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 8;
}
void set_reg_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 8;
}
void set_reg_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 8;
}
void set_reg_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 8;
}
void set_reg_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 8;
}
void set_reg_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 8;
}
void set_hl_B_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 8;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 8;
}
void set_reg_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 16;
}
void set_reg_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 16;
}
void set_reg_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 16;
}
void set_reg_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 16;
}
void set_reg_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 16;
}
void set_reg_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 16;
}
void set_hl_B_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 16;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 16;
}
void set_reg_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 32;
}
void set_reg_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 32;
}
void set_reg_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 32;
}
void set_reg_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 32;
}
void set_reg_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 32;
}
void set_reg_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 32;
}
void set_hl_B_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 32;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 32;
}
void set_reg_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 64;
}
void set_reg_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 64;
}
void set_reg_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 64;
}
void set_reg_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 64;
}
void set_reg_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 64;
}
void set_reg_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 64;
}
void set_hl_B_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 64;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 64;
}
void set_reg_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[0] = context->main[0] | 128;
}
void set_reg_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[1] = context->main[1] | 128;
}
void set_reg_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[2] = context->main[2] | 128;
}
void set_reg_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[3] = context->main[3] | 128;
}
void set_reg_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[4] = context->main[4] | 128;
}
void set_reg_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[5] = context->main[5] | 128;
}
void set_hl_B_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->scratch1 | 128;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void set_reg_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->main[7] = context->main[7] | 128;
}
static impl_fun impl_cb[256] = {
	rlc_R_000,
	rlc_R_001,
	rlc_R_010,
	rlc_R_011,
	rlc_R_100,
	rlc_R_101,
	rlc_hl,
	rlc_R_111,
	rrc_R_000,
	rrc_R_001,
	rrc_R_010,
	rrc_R_011,
	rrc_R_100,
	rrc_R_101,
	rrc_hl,
	rrc_R_111,
	rl_R_000,
	rl_R_001,
	rl_R_010,
	rl_R_011,
	rl_R_100,
	rl_R_101,
	rl_hl,
	rl_R_111,
	rr_R_000,
	rr_R_001,
	rr_R_010,
	rr_R_011,
	rr_R_100,
	rr_R_101,
	rr_hl,
	rr_R_111,
	sla_R_000,
	sla_R_001,
	sla_R_010,
	sla_R_011,
	sla_R_100,
	sla_R_101,
	sla_hl,
	sla_R_111,
	sra_R_000,
	sra_R_001,
	sra_R_010,
	sra_R_011,
	sra_R_100,
	sra_R_101,
	sra_hl,
	sra_R_111,
	sll_R_000,
	sll_R_001,
	sll_R_010,
	sll_R_011,
	sll_R_100,
	sll_R_101,
	sll_hl,
	sll_R_111,
	srl_R_000,
	srl_R_001,
	srl_R_010,
	srl_R_011,
	srl_R_100,
	srl_R_101,
	srl_hl,
	srl_R_111,
	bit_reg_B_000_R_000,
	bit_reg_B_000_R_001,
	bit_reg_B_000_R_010,
	bit_reg_B_000_R_011,
	bit_reg_B_000_R_100,
	bit_reg_B_000_R_101,
	bit_hl_B_000,
	bit_reg_B_000_R_111,
	bit_reg_B_001_R_000,
	bit_reg_B_001_R_001,
	bit_reg_B_001_R_010,
	bit_reg_B_001_R_011,
	bit_reg_B_001_R_100,
	bit_reg_B_001_R_101,
	bit_hl_B_001,
	bit_reg_B_001_R_111,
	bit_reg_B_010_R_000,
	bit_reg_B_010_R_001,
	bit_reg_B_010_R_010,
	bit_reg_B_010_R_011,
	bit_reg_B_010_R_100,
	bit_reg_B_010_R_101,
	bit_hl_B_010,
	bit_reg_B_010_R_111,
	bit_reg_B_011_R_000,
	bit_reg_B_011_R_001,
	bit_reg_B_011_R_010,
	bit_reg_B_011_R_011,
	bit_reg_B_011_R_100,
	bit_reg_B_011_R_101,
	bit_hl_B_011,
	bit_reg_B_011_R_111,
	bit_reg_B_100_R_000,
	bit_reg_B_100_R_001,
	bit_reg_B_100_R_010,
	bit_reg_B_100_R_011,
	bit_reg_B_100_R_100,
	bit_reg_B_100_R_101,
	bit_hl_B_100,
	bit_reg_B_100_R_111,
	bit_reg_B_101_R_000,
	bit_reg_B_101_R_001,
	bit_reg_B_101_R_010,
	bit_reg_B_101_R_011,
	bit_reg_B_101_R_100,
	bit_reg_B_101_R_101,
	bit_hl_B_101,
	bit_reg_B_101_R_111,
	bit_reg_B_110_R_000,
	bit_reg_B_110_R_001,
	bit_reg_B_110_R_010,
	bit_reg_B_110_R_011,
	bit_reg_B_110_R_100,
	bit_reg_B_110_R_101,
	bit_hl_B_110,
	bit_reg_B_110_R_111,
	bit_reg_B_111_R_000,
	bit_reg_B_111_R_001,
	bit_reg_B_111_R_010,
	bit_reg_B_111_R_011,
	bit_reg_B_111_R_100,
	bit_reg_B_111_R_101,
	bit_hl_B_111,
	bit_reg_B_111_R_111,
	res_reg_B_000_R_000,
	res_reg_B_000_R_001,
	res_reg_B_000_R_010,
	res_reg_B_000_R_011,
	res_reg_B_000_R_100,
	res_reg_B_000_R_101,
	res_hl_B_000,
	res_reg_B_000_R_111,
	res_reg_B_001_R_000,
	res_reg_B_001_R_001,
	res_reg_B_001_R_010,
	res_reg_B_001_R_011,
	res_reg_B_001_R_100,
	res_reg_B_001_R_101,
	res_hl_B_001,
	res_reg_B_001_R_111,
	res_reg_B_010_R_000,
	res_reg_B_010_R_001,
	res_reg_B_010_R_010,
	res_reg_B_010_R_011,
	res_reg_B_010_R_100,
	res_reg_B_010_R_101,
	res_hl_B_010,
	res_reg_B_010_R_111,
	res_reg_B_011_R_000,
	res_reg_B_011_R_001,
	res_reg_B_011_R_010,
	res_reg_B_011_R_011,
	res_reg_B_011_R_100,
	res_reg_B_011_R_101,
	res_hl_B_011,
	res_reg_B_011_R_111,
	res_reg_B_100_R_000,
	res_reg_B_100_R_001,
	res_reg_B_100_R_010,
	res_reg_B_100_R_011,
	res_reg_B_100_R_100,
	res_reg_B_100_R_101,
	res_hl_B_100,
	res_reg_B_100_R_111,
	res_reg_B_101_R_000,
	res_reg_B_101_R_001,
	res_reg_B_101_R_010,
	res_reg_B_101_R_011,
	res_reg_B_101_R_100,
	res_reg_B_101_R_101,
	res_hl_B_101,
	res_reg_B_101_R_111,
	res_reg_B_110_R_000,
	res_reg_B_110_R_001,
	res_reg_B_110_R_010,
	res_reg_B_110_R_011,
	res_reg_B_110_R_100,
	res_reg_B_110_R_101,
	res_hl_B_110,
	res_reg_B_110_R_111,
	res_reg_B_111_R_000,
	res_reg_B_111_R_001,
	res_reg_B_111_R_010,
	res_reg_B_111_R_011,
	res_reg_B_111_R_100,
	res_reg_B_111_R_101,
	res_hl_B_111,
	res_reg_B_111_R_111,
	set_reg_B_000_R_000,
	set_reg_B_000_R_001,
	set_reg_B_000_R_010,
	set_reg_B_000_R_011,
	set_reg_B_000_R_100,
	set_reg_B_000_R_101,
	set_hl_B_000,
	set_reg_B_000_R_111,
	set_reg_B_001_R_000,
	set_reg_B_001_R_001,
	set_reg_B_001_R_010,
	set_reg_B_001_R_011,
	set_reg_B_001_R_100,
	set_reg_B_001_R_101,
	set_hl_B_001,
	set_reg_B_001_R_111,
	set_reg_B_010_R_000,
	set_reg_B_010_R_001,
	set_reg_B_010_R_010,
	set_reg_B_010_R_011,
	set_reg_B_010_R_100,
	set_reg_B_010_R_101,
	set_hl_B_010,
	set_reg_B_010_R_111,
	set_reg_B_011_R_000,
	set_reg_B_011_R_001,
	set_reg_B_011_R_010,
	set_reg_B_011_R_011,
	set_reg_B_011_R_100,
	set_reg_B_011_R_101,
	set_hl_B_011,
	set_reg_B_011_R_111,
	set_reg_B_100_R_000,
	set_reg_B_100_R_001,
	set_reg_B_100_R_010,
	set_reg_B_100_R_011,
	set_reg_B_100_R_100,
	set_reg_B_100_R_101,
	set_hl_B_100,
	set_reg_B_100_R_111,
	set_reg_B_101_R_000,
	set_reg_B_101_R_001,
	set_reg_B_101_R_010,
	set_reg_B_101_R_011,
	set_reg_B_101_R_100,
	set_reg_B_101_R_101,
	set_hl_B_101,
	set_reg_B_101_R_111,
	set_reg_B_110_R_000,
	set_reg_B_110_R_001,
	set_reg_B_110_R_010,
	set_reg_B_110_R_011,
	set_reg_B_110_R_100,
	set_reg_B_110_R_101,
	set_hl_B_110,
	set_reg_B_110_R_111,
	set_reg_B_111_R_000,
	set_reg_B_111_R_001,
	set_reg_B_111_R_010,
	set_reg_B_111_R_011,
	set_reg_B_111_R_100,
	set_reg_B_111_R_101,
	set_hl_B_111,
	set_reg_B_111_R_111,
};
void in_bc_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[0] = context->scratch1;
}
void out_bc_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[0];
	z80_io_write8(context);
}
void sbc_hl_bc(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	uint16_t bcw;
	bcw = context->main[0] << 8;
	bcw = context->main[1] | bcw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = hlw - bcw - ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((hlw ^ bcw)) & (hlw ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((hlw ^ bcw ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 1;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_bc_to_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[1];
	z80_write_8(context);
	context->wz = 1 + context->wz;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
	context->wz = 1 + context->wz;
}
void neg_D_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void im0_D_0(z80_context *context, uint32_t target_cycle)
{
	context->imode = 0;
}
void ld_i_a(z80_context *context, uint32_t target_cycle)
{
	context->i = context->main[7];
	context->cycles += context->opts->gen.clock_divider * 1;
}
void in_bc_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[1] = context->scratch1;
}
void out_bc_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[1];
	z80_io_write8(context);
}
void adc_hl_bc(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	uint16_t bcw;
	bcw = context->main[0] << 8;
	bcw = context->main[1] | bcw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = bcw + hlw + ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((bcw ^ (~hlw))) & (bcw ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((bcw ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_bc_from_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[1] = context->scratch1;
	context->wz = 1 + context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[0] = context->scratch1;
	context->wz = 1 + context->wz;
}
void neg_D_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void reti(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
}
void im3_D_0(z80_context *context, uint32_t target_cycle)
{
	context->imode = 0;
}
void ld_r_a(z80_context *context, uint32_t target_cycle)
{
	context->r = context->main[7];
	context->rhigh = 128 & context->main[7];
	context->cycles += context->opts->gen.clock_divider * 1;
}
void in_bc_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[2] = context->scratch1;
}
void out_bc_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[2];
	z80_io_write8(context);
}
void sbc_hl_de(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	uint16_t dew;
	dew = context->main[2] << 8;
	dew = context->main[3] | dew;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = hlw - dew - ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((hlw ^ dew)) & (hlw ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((hlw ^ dew ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 1;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_de_to_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[3];
	z80_write_8(context);
	context->wz = 1 + context->wz;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
	context->wz = 1 + context->wz;
}
void neg_D_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void im1_D_0(z80_context *context, uint32_t target_cycle)
{
	context->imode = 1;
}
void ld_a_i(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->i;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	context->chflags &= ~8;
	context->nflag = 0;
	context->pvflag = context->iff2;
}
void in_bc_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[3] = context->scratch1;
}
void out_bc_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[3];
	z80_io_write8(context);
}
void adc_hl_de(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	uint16_t dew;
	dew = context->main[2] << 8;
	dew = context->main[3] | dew;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = dew + hlw + ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((dew ^ (~hlw))) & (dew ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((dew ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_de_from_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[3] = context->scratch1;
	context->wz = 1 + context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[2] = context->scratch1;
	context->wz = 1 + context->wz;
}
void neg_D_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void retn_N_01(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->iff1 = context->iff2;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
}
void im2_D_0(z80_context *context, uint32_t target_cycle)
{
	context->imode = 2;
}
void ld_a_r(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = 127 & context->r;
	context->main[7] = context->rhigh | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	context->chflags &= ~8;
	context->nflag = 0;
	context->pvflag = context->iff2;
}
void in_bc_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[4] = context->scratch1;
}
void out_bc_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[4];
	z80_io_write8(context);
}
void sbc_hl_hl(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = hlw - hlw - ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((hlw ^ hlw)) & (hlw ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((hlw ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 1;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_hl_to_immed_slow(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[5];
	z80_write_8(context);
	context->wz = 1 + context->wz;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
	context->wz = 1 + context->wz;
}
void neg_D_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void im0_D_1(z80_context *context, uint32_t target_cycle)
{
	context->imode = 0;
}
void rrd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	uint8_t tmp2;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 4;
	tmp = 15 & context->scratch1;
	context->scratch1 = context->scratch1 >> 4;
	tmp2 = context->main[7] << 4;
	context->scratch1 = tmp2 | context->scratch1;
	context->main[7] = 240 & context->main[7];
	context->main[7] = tmp | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void in_bc_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[5] = context->scratch1;
}
void out_bc_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[5];
	z80_io_write8(context);
}
void adc_hl_hl(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = hlw + hlw + ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((hlw ^ (~hlw))) & (hlw ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((hlw ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_hl_from_immed_slow(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[5] = context->scratch1;
	context->wz = 1 + context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[4] = context->scratch1;
	context->wz = 1 + context->wz;
}
void neg_D_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void retn_N_10(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->iff1 = context->iff2;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
}
void im3_D_1(z80_context *context, uint32_t target_cycle)
{
	context->imode = 0;
}
void rld(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	uint8_t tmp2;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 4;
	tmp = context->scratch1 >> 4;
	context->scratch1 = context->scratch1 << 4;
	tmp2 = 15 & context->main[7];
	context->scratch1 = tmp2 | context->scratch1;
	context->main[7] = 240 & context->main[7];
	context->main[7] = tmp | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void in_bc_R_110(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[6] = context->scratch1;
}
void out_bc_R_110(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[6];
	z80_io_write8(context);
}
void sbc_hl_sp(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = hlw - context->sp - ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((hlw ^ context->sp)) & (hlw ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((hlw ^ context->sp ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 1;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_sp_to_immed(z80_context *context, uint32_t target_cycle)
{
	uint8_t sph;
	sph = context->sp >> 8;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->sp;
	z80_write_8(context);
	context->wz = 1 + context->wz;
	context->scratch1 = sph;
	context->scratch2 = context->wz;
	z80_write_8(context);
	context->wz = 1 + context->wz;
}
void neg_D_110(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void im1_D_1(z80_context *context, uint32_t target_cycle)
{
	context->imode = 1;
}
void in_bc_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->main[7] = context->scratch1;
}
void out_bc_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[7];
	z80_io_write8(context);
}
void adc_hl_sp(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = context->sp + hlw + ((context->chflags & 1 << 7) ? 1 : 0);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->pvflag = (((context->sp ^ (~hlw))) & (context->sp ^ gen_tmp32__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp32__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((context->sp ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->zflag = (gen_tmp32__ & 65535) == 0;
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_sp_from_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->sp = context->scratch1;
	context->wz = 1 + context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->scratch1 = context->scratch1 << 8;
	context->sp = context->scratch1 | context->sp;
	context->wz = 1 + context->wz;
}
void neg_D_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = -context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((0 ^ context->main[7])) & (0 ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((0 ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void retn_N_11(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->iff1 = context->iff2;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
}
void im2_D_1(z80_context *context, uint32_t target_cycle)
{
	context->imode = 2;
}
void ldi(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_ldd_ldi_tmp;
	uint8_t z80_ldd_ldi_tmp8;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = 1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	z80_ldd_ldi_tmp8 = context->main[7] + context->scratch1;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_ldd_ldi_tmp8 & 8U);
	context->chflags &= ~8;
	context->nflag = 0;
	z80_ldd_ldi_tmp8 = 2 & z80_ldd_ldi_tmp8;
	z80_ldd_ldi_tmp8 = z80_ldd_ldi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_ldd_ldi_tmp8 | context->last_flag_result;
	z80_ldd_ldi_tmp = context->main[2] << 8;
	z80_ldd_ldi_tmp = context->main[3] | z80_ldd_ldi_tmp;
	context->scratch2 = z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = 1 + z80_ldd_ldi_tmp;
	context->main[3] = z80_ldd_ldi_tmp;
	context->main[2] = z80_ldd_ldi_tmp >> 8;
	z80_write_8(context);
	z80_ldd_ldi_tmp = context->main[0] << 8;
	z80_ldd_ldi_tmp = context->main[1] | z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = z80_ldd_ldi_tmp - 1;
	context->main[1] = z80_ldd_ldi_tmp;
	context->main[0] = z80_ldd_ldi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
}
void cpi(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint16_t z80_cpd_cpi_tmp;
	uint8_t z80_cpd_cpi_tmp8;
	uint8_t z80_cpd_cpi_hf;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = 1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	gen_tmp8__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp8__ & 128U);
	z80_cpd_cpi_tmp8 = gen_tmp8__;
	context->nflag = 1;
	z80_cpd_cpi_hf = context->chflags >> 3;
	z80_cpd_cpi_hf = 1 & z80_cpd_cpi_hf;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 - z80_cpd_cpi_hf;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_cpd_cpi_tmp8 & 8U);
	z80_cpd_cpi_tmp8 = 2 & z80_cpd_cpi_tmp8;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_cpd_cpi_tmp8 | context->last_flag_result;
	z80_cpd_cpi_tmp = context->main[0] << 8;
	z80_cpd_cpi_tmp = context->main[1] | z80_cpd_cpi_tmp;
	z80_cpd_cpi_tmp = z80_cpd_cpi_tmp - 1;
	context->main[1] = z80_cpd_cpi_tmp;
	context->main[0] = z80_cpd_cpi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
	context->cycles += context->opts->gen.clock_divider * 5;
}
void ini(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_ini_ind_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = 1 + context->wz;
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->nflag = 128 & context->scratch1;
	z80_ini_ind_tmp = context->wz;
	gen_tmp16__ = z80_ini_ind_tmp + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_ini_ind_tmp = gen_tmp16__;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = 1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	z80_ini_ind_tmp = 7 & z80_ini_ind_tmp;
	z80_ini_ind_tmp = context->main[0] ^ z80_ini_ind_tmp;
	gen_tmp8__ = (z80_ini_ind_tmp ^ (z80_ini_ind_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_ini_ind_tmp = context->chflags >> 4;
	context->chflags = z80_ini_ind_tmp | context->chflags;
}
void outi(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_outi_outd_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->nflag = 128 & context->scratch1;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = 1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	gen_tmp16__ = context->main[5] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_outi_outd_tmp = gen_tmp16__;
	z80_outi_outd_tmp = 7 & z80_outi_outd_tmp;
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	z80_io_write8(context);
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = 1 + context->wz;
	z80_outi_outd_tmp = context->main[0] ^ z80_outi_outd_tmp;
	gen_tmp8__ = (z80_outi_outd_tmp ^ (z80_outi_outd_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_outi_outd_tmp = context->chflags >> 4;
	context->chflags = z80_outi_outd_tmp | context->chflags;
}
void ldd(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_ldd_ldi_tmp;
	uint8_t z80_ldd_ldi_tmp8;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = -1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	z80_ldd_ldi_tmp8 = context->main[7] + context->scratch1;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_ldd_ldi_tmp8 & 8U);
	context->chflags &= ~8;
	context->nflag = 0;
	z80_ldd_ldi_tmp8 = 2 & z80_ldd_ldi_tmp8;
	z80_ldd_ldi_tmp8 = z80_ldd_ldi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_ldd_ldi_tmp8 | context->last_flag_result;
	z80_ldd_ldi_tmp = context->main[2] << 8;
	z80_ldd_ldi_tmp = context->main[3] | z80_ldd_ldi_tmp;
	context->scratch2 = z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = -1 + z80_ldd_ldi_tmp;
	context->main[3] = z80_ldd_ldi_tmp;
	context->main[2] = z80_ldd_ldi_tmp >> 8;
	z80_write_8(context);
	z80_ldd_ldi_tmp = context->main[0] << 8;
	z80_ldd_ldi_tmp = context->main[1] | z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = z80_ldd_ldi_tmp - 1;
	context->main[1] = z80_ldd_ldi_tmp;
	context->main[0] = z80_ldd_ldi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
}
void cpd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint16_t z80_cpd_cpi_tmp;
	uint8_t z80_cpd_cpi_tmp8;
	uint8_t z80_cpd_cpi_hf;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = -1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	gen_tmp8__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp8__ & 128U);
	z80_cpd_cpi_tmp8 = gen_tmp8__;
	context->nflag = 1;
	z80_cpd_cpi_hf = context->chflags >> 3;
	z80_cpd_cpi_hf = 1 & z80_cpd_cpi_hf;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 - z80_cpd_cpi_hf;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_cpd_cpi_tmp8 & 8U);
	z80_cpd_cpi_tmp8 = 2 & z80_cpd_cpi_tmp8;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_cpd_cpi_tmp8 | context->last_flag_result;
	z80_cpd_cpi_tmp = context->main[0] << 8;
	z80_cpd_cpi_tmp = context->main[1] | z80_cpd_cpi_tmp;
	z80_cpd_cpi_tmp = z80_cpd_cpi_tmp - 1;
	context->main[1] = z80_cpd_cpi_tmp;
	context->main[0] = z80_cpd_cpi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
	context->cycles += context->opts->gen.clock_divider * 5;
}
void ind(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_ini_ind_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = -1 + context->wz;
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->nflag = 128 & context->scratch1;
	z80_ini_ind_tmp = context->wz;
	gen_tmp16__ = z80_ini_ind_tmp + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_ini_ind_tmp = gen_tmp16__;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = -1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	z80_ini_ind_tmp = 7 & z80_ini_ind_tmp;
	z80_ini_ind_tmp = context->main[0] ^ z80_ini_ind_tmp;
	gen_tmp8__ = (z80_ini_ind_tmp ^ (z80_ini_ind_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_ini_ind_tmp = context->chflags >> 4;
	context->chflags = z80_ini_ind_tmp | context->chflags;
}
void outd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_outi_outd_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->nflag = 128 & context->scratch1;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = -1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	gen_tmp16__ = context->main[5] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_outi_outd_tmp = gen_tmp16__;
	z80_outi_outd_tmp = 7 & z80_outi_outd_tmp;
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	z80_io_write8(context);
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = -1 + context->wz;
	z80_outi_outd_tmp = context->main[0] ^ z80_outi_outd_tmp;
	gen_tmp8__ = (z80_outi_outd_tmp ^ (z80_outi_outd_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_outi_outd_tmp = context->chflags >> 4;
	context->chflags = z80_outi_outd_tmp | context->chflags;
}
void ldir(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_ldd_ldi_tmp;
	uint8_t z80_ldd_ldi_tmp8;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = 1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	z80_ldd_ldi_tmp8 = context->main[7] + context->scratch1;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_ldd_ldi_tmp8 & 8U);
	context->chflags &= ~8;
	context->nflag = 0;
	z80_ldd_ldi_tmp8 = 2 & z80_ldd_ldi_tmp8;
	z80_ldd_ldi_tmp8 = z80_ldd_ldi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_ldd_ldi_tmp8 | context->last_flag_result;
	z80_ldd_ldi_tmp = context->main[2] << 8;
	z80_ldd_ldi_tmp = context->main[3] | z80_ldd_ldi_tmp;
	context->scratch2 = z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = 1 + z80_ldd_ldi_tmp;
	context->main[3] = z80_ldd_ldi_tmp;
	context->main[2] = z80_ldd_ldi_tmp >> 8;
	z80_write_8(context);
	z80_ldd_ldi_tmp = context->main[0] << 8;
	z80_ldd_ldi_tmp = context->main[1] | z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = z80_ldd_ldi_tmp - 1;
	context->main[1] = z80_ldd_ldi_tmp;
	context->main[0] = z80_ldd_ldi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
	if (context->pvflag) {
	context->wz = 1 + context->pc;
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void cpir(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint16_t z80_cpd_cpi_tmp;
	uint8_t z80_cpd_cpi_tmp8;
	uint8_t z80_cpd_cpi_hf;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = 1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	gen_tmp8__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp8__ & 128U);
	z80_cpd_cpi_tmp8 = gen_tmp8__;
	context->nflag = 1;
	z80_cpd_cpi_hf = context->chflags >> 3;
	z80_cpd_cpi_hf = 1 & z80_cpd_cpi_hf;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 - z80_cpd_cpi_hf;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_cpd_cpi_tmp8 & 8U);
	z80_cpd_cpi_tmp8 = 2 & z80_cpd_cpi_tmp8;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_cpd_cpi_tmp8 | context->last_flag_result;
	z80_cpd_cpi_tmp = context->main[0] << 8;
	z80_cpd_cpi_tmp = context->main[1] | z80_cpd_cpi_tmp;
	z80_cpd_cpi_tmp = z80_cpd_cpi_tmp - 1;
	context->main[1] = z80_cpd_cpi_tmp;
	context->main[0] = z80_cpd_cpi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
	context->cycles += context->opts->gen.clock_divider * 5;
	if (context->pvflag) {
	if (context->zflag) {
	} else {
	context->wz = 1 + context->pc;
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
	}
}
void inir(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_ini_ind_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = 1 + context->wz;
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->nflag = 128 & context->scratch1;
	z80_ini_ind_tmp = context->wz;
	gen_tmp16__ = z80_ini_ind_tmp + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_ini_ind_tmp = gen_tmp16__;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = 1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	z80_ini_ind_tmp = 7 & z80_ini_ind_tmp;
	z80_ini_ind_tmp = context->main[0] ^ z80_ini_ind_tmp;
	gen_tmp8__ = (z80_ini_ind_tmp ^ (z80_ini_ind_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_ini_ind_tmp = context->chflags >> 4;
	context->chflags = z80_ini_ind_tmp | context->chflags;
	if (context->zflag) {
	} else {
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void otir(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_outi_outd_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->nflag = 128 & context->scratch1;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = 1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	gen_tmp16__ = context->main[5] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_outi_outd_tmp = gen_tmp16__;
	z80_outi_outd_tmp = 7 & z80_outi_outd_tmp;
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	z80_io_write8(context);
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = 1 + context->wz;
	z80_outi_outd_tmp = context->main[0] ^ z80_outi_outd_tmp;
	gen_tmp8__ = (z80_outi_outd_tmp ^ (z80_outi_outd_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_outi_outd_tmp = context->chflags >> 4;
	context->chflags = z80_outi_outd_tmp | context->chflags;
	if (context->zflag) {
	} else {
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void lddr(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_ldd_ldi_tmp;
	uint8_t z80_ldd_ldi_tmp8;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = -1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	z80_ldd_ldi_tmp8 = context->main[7] + context->scratch1;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_ldd_ldi_tmp8 & 8U);
	context->chflags &= ~8;
	context->nflag = 0;
	z80_ldd_ldi_tmp8 = 2 & z80_ldd_ldi_tmp8;
	z80_ldd_ldi_tmp8 = z80_ldd_ldi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_ldd_ldi_tmp8 | context->last_flag_result;
	z80_ldd_ldi_tmp = context->main[2] << 8;
	z80_ldd_ldi_tmp = context->main[3] | z80_ldd_ldi_tmp;
	context->scratch2 = z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = -1 + z80_ldd_ldi_tmp;
	context->main[3] = z80_ldd_ldi_tmp;
	context->main[2] = z80_ldd_ldi_tmp >> 8;
	z80_write_8(context);
	z80_ldd_ldi_tmp = context->main[0] << 8;
	z80_ldd_ldi_tmp = context->main[1] | z80_ldd_ldi_tmp;
	z80_ldd_ldi_tmp = z80_ldd_ldi_tmp - 1;
	context->main[1] = z80_ldd_ldi_tmp;
	context->main[0] = z80_ldd_ldi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
	if (context->pvflag) {
	context->wz = 1 + context->pc;
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void cpdr(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint16_t z80_cpd_cpi_tmp;
	uint8_t z80_cpd_cpi_tmp8;
	uint8_t z80_cpd_cpi_hf;
	uint16_t z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = context->main[4] << 8;
	z80_fetch_mod_hl_tmp = context->main[5] | z80_fetch_mod_hl_tmp;
	context->scratch1 = z80_fetch_mod_hl_tmp;
	z80_fetch_mod_hl_tmp = -1 + z80_fetch_mod_hl_tmp;
	context->main[5] = z80_fetch_mod_hl_tmp;
	context->main[4] = z80_fetch_mod_hl_tmp >> 8;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 2;
	gen_tmp8__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp8__ & 128U);
	z80_cpd_cpi_tmp8 = gen_tmp8__;
	context->nflag = 1;
	z80_cpd_cpi_hf = context->chflags >> 3;
	z80_cpd_cpi_hf = 1 & z80_cpd_cpi_hf;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 - z80_cpd_cpi_hf;
	context->last_flag_result = (context->last_flag_result & ~8U) | (z80_cpd_cpi_tmp8 & 8U);
	z80_cpd_cpi_tmp8 = 2 & z80_cpd_cpi_tmp8;
	z80_cpd_cpi_tmp8 = z80_cpd_cpi_tmp8 << 4;
	context->last_flag_result = 136 & context->last_flag_result;
	context->last_flag_result = z80_cpd_cpi_tmp8 | context->last_flag_result;
	z80_cpd_cpi_tmp = context->main[0] << 8;
	z80_cpd_cpi_tmp = context->main[1] | z80_cpd_cpi_tmp;
	z80_cpd_cpi_tmp = z80_cpd_cpi_tmp - 1;
	context->main[1] = z80_cpd_cpi_tmp;
	context->main[0] = z80_cpd_cpi_tmp >> 8;
	context->pvflag = context->main[1];
	context->pvflag = context->main[0] | context->pvflag;
	context->cycles += context->opts->gen.clock_divider * 5;
	if (context->pvflag) {
	if (context->zflag) {
	} else {
	context->wz = 1 + context->pc;
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
	}
}
void indr(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_ini_ind_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = -1 + context->wz;
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	z80_io_read8(context);
	context->nflag = 128 & context->scratch1;
	z80_ini_ind_tmp = context->wz;
	gen_tmp16__ = z80_ini_ind_tmp + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_ini_ind_tmp = gen_tmp16__;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = -1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	z80_ini_ind_tmp = 7 & z80_ini_ind_tmp;
	z80_ini_ind_tmp = context->main[0] ^ z80_ini_ind_tmp;
	gen_tmp8__ = (z80_ini_ind_tmp ^ (z80_ini_ind_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_ini_ind_tmp = context->chflags >> 4;
	context->chflags = z80_ini_ind_tmp | context->chflags;
	if (context->zflag) {
	} else {
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void otdr(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t z80_outi_outd_tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->nflag = 128 & context->scratch1;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	context->scratch2 = -1 + context->scratch2;
	context->main[5] = context->scratch2;
	context->main[4] = context->scratch2 >> 8;
	gen_tmp16__ = context->main[5] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	z80_outi_outd_tmp = gen_tmp16__;
	z80_outi_outd_tmp = 7 & z80_outi_outd_tmp;
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	z80_io_write8(context);
	context->main[0] = context->main[0] - 1;
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->wz = 8 << context->main[0];
	context->wz = context->main[1] | context->wz;
	context->wz = -1 + context->wz;
	z80_outi_outd_tmp = context->main[0] ^ z80_outi_outd_tmp;
	gen_tmp8__ = (z80_outi_outd_tmp ^ (z80_outi_outd_tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	z80_outi_outd_tmp = context->chflags >> 4;
	context->chflags = z80_outi_outd_tmp | context->chflags;
	if (context->zflag) {
	} else {
	context->pc = context->pc - 2;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
static impl_fun impl_ed[256] = {
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	in_bc_R_000,
	out_bc_R_000,
	sbc_hl_bc,
	ld_bc_to_immed,
	neg_D_000,
	unimplemented,
	im0_D_0,
	ld_i_a,
	in_bc_R_001,
	out_bc_R_001,
	adc_hl_bc,
	ld_bc_from_immed,
	neg_D_001,
	reti,
	im3_D_0,
	ld_r_a,
	in_bc_R_010,
	out_bc_R_010,
	sbc_hl_de,
	ld_de_to_immed,
	neg_D_010,
	unimplemented,
	im1_D_0,
	ld_a_i,
	in_bc_R_011,
	out_bc_R_011,
	adc_hl_de,
	ld_de_from_immed,
	neg_D_011,
	retn_N_01,
	im2_D_0,
	ld_a_r,
	in_bc_R_100,
	out_bc_R_100,
	sbc_hl_hl,
	ld_hl_to_immed_slow,
	neg_D_100,
	unimplemented,
	im0_D_1,
	rrd,
	in_bc_R_101,
	out_bc_R_101,
	adc_hl_hl,
	ld_hl_from_immed_slow,
	neg_D_101,
	retn_N_10,
	im3_D_1,
	rld,
	in_bc_R_110,
	out_bc_R_110,
	sbc_hl_sp,
	ld_sp_to_immed,
	neg_D_110,
	unimplemented,
	im1_D_1,
	unimplemented,
	in_bc_R_111,
	out_bc_R_111,
	adc_hl_sp,
	ld_sp_from_immed,
	neg_D_111,
	retn_N_11,
	im2_D_1,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	ldi,
	cpi,
	ini,
	outi,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	ldd,
	cpd,
	ind,
	outd,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	ldir,
	cpir,
	inir,
	otir,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	lddr,
	cpdr,
	indr,
	otdr,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
};
static impl_fun impl_dded[256] = {
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
};
static impl_fun impl_fded[256] = {
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
	unimplemented,
};
void rlc_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1 | context->main[0] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1 | context->main[1] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1 | context->main[2] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1 | context->main[3] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1 | context->main[4] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1 | context->main[5] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1 | tmp >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	context->main[0] = context->main[0] >> 1 | context->main[0] << (8 - 1);
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->chflags = (context->chflags & ~128U) | (context->main[0] & 128U);
	gen_tmp8__ = (context->main[0] ^ (context->main[0] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	context->main[1] = context->main[1] >> 1 | context->main[1] << (8 - 1);
	context->zflag = context->main[1] == 0;
	context->last_flag_result = context->main[1];
	context->chflags = (context->chflags & ~128U) | (context->main[1] & 128U);
	gen_tmp8__ = (context->main[1] ^ (context->main[1] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	context->main[2] = context->main[2] >> 1 | context->main[2] << (8 - 1);
	context->zflag = context->main[2] == 0;
	context->last_flag_result = context->main[2];
	context->chflags = (context->chflags & ~128U) | (context->main[2] & 128U);
	gen_tmp8__ = (context->main[2] ^ (context->main[2] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	context->main[3] = context->main[3] >> 1 | context->main[3] << (8 - 1);
	context->zflag = context->main[3] == 0;
	context->last_flag_result = context->main[3];
	context->chflags = (context->chflags & ~128U) | (context->main[3] & 128U);
	gen_tmp8__ = (context->main[3] ^ (context->main[3] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	context->main[4] = context->main[4] >> 1 | context->main[4] << (8 - 1);
	context->zflag = context->main[4] == 0;
	context->last_flag_result = context->main[4];
	context->chflags = (context->chflags & ~128U) | (context->main[4] & 128U);
	gen_tmp8__ = (context->main[4] ^ (context->main[4] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	context->main[5] = context->main[5] >> 1 | context->main[5] << (8 - 1);
	context->zflag = context->main[5] == 0;
	context->last_flag_result = context->main[5];
	context->chflags = (context->chflags & ~128U) | (context->main[5] & 128U);
	gen_tmp8__ = (context->main[5] ^ (context->main[5] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	tmp = tmp >> 1 | tmp << (8 - 1);
	context->zflag = tmp == 0;
	context->last_flag_result = tmp;
	context->chflags = (context->chflags & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	context->main[7] = context->main[7] >> 1 | context->main[7] << (8 - 1);
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	context->chflags = (context->chflags & ~128U) | (context->main[7] & 128U);
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1 | context->main[0] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1 | context->main[1] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1 | context->main[2] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1 | context->main[3] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1 | context->main[4] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1 | context->main[5] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1 | tmp >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] >> 1 | context->main[0] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] >> 1 | context->main[1] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] >> 1 | context->main[2] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] >> 1 | context->main[3] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] >> 1 | context->main[4] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] >> 1 | context->main[5] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp >> 1 | tmp << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] >> 1 | context->main[7] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = (context->main[0] >> 1) | (context->main[0] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[0] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = (context->main[1] >> 1) | (context->main[1] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[1] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = (context->main[2] >> 1) | (context->main[2] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[2] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = (context->main[3] >> 1) | (context->main[3] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[3] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = (context->main[4] >> 1) | (context->main[4] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[4] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = (context->main[5] >> 1) | (context->main[5] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[5] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = (tmp >> 1) | (tmp & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (tmp << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = (context->main[7] >> 1) | (context->main[7] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[7] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[0] = 1 | context->main[0];
	gen_tmp8__ = (context->main[0] ^ (context->main[0] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[1] = 1 | context->main[1];
	gen_tmp8__ = (context->main[1] ^ (context->main[1] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[2] = 1 | context->main[2];
	gen_tmp8__ = (context->main[2] ^ (context->main[2] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[3] = 1 | context->main[3];
	gen_tmp8__ = (context->main[3] ^ (context->main[3] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[4] = 1 | context->main[4];
	gen_tmp8__ = (context->main[4] ^ (context->main[4] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[5] = 1 | context->main[5];
	gen_tmp8__ = (context->main[5] ^ (context->main[5] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	tmp = 1 | tmp;
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[7] = 1 | context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[0] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[1] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[2] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[3] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[4] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[5] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp >> 1;
	context->chflags = (context->chflags & ~128U) | (tmp << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_ixd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[7] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void bit_ixd_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_000_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_ixd_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void res_ixd_reg_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -2;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -2;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -2;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -2;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -2;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -2;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -2;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -2;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -3;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -3;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -3;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -3;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -3;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -3;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -3;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -3;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -5;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -5;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -5;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -5;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -5;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -5;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -5;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -5;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -9;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -9;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -9;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -9;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -9;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -9;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -9;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -9;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -17;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -17;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -17;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -17;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -17;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -17;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -17;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -17;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -33;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -33;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -33;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -33;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -33;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -33;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -33;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -33;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -65;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -65;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -65;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -65;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -65;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -65;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -65;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -65;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -129;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -129;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -129;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -129;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -129;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -129;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_B_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -129;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_ixd_reg_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -129;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 1;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 1;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 1;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 1;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 1;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 1;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 1;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 1;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 2;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 2;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 2;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 2;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 2;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 2;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 2;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 2;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 4;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 4;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 4;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 4;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 4;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 4;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 4;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 4;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 8;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 8;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 8;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 8;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 8;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 8;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 8;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 8;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 16;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 16;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 16;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 16;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 16;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 16;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 16;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 16;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 32;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 32;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 32;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 32;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 32;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 32;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 32;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 32;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 64;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 64;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 64;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 64;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 64;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 64;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 64;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 64;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 128;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 128;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 128;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 128;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 128;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 128;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_B_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 128;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_ixd_reg_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 128;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
static impl_fun impl_ddcb[256] = {
	rlc_ixd_reg_R_000,
	rlc_ixd_reg_R_001,
	rlc_ixd_reg_R_010,
	rlc_ixd_reg_R_011,
	rlc_ixd_reg_R_100,
	rlc_ixd_reg_R_101,
	rlc_ixd,
	rlc_ixd_reg_R_111,
	rrc_ixd_reg_R_000,
	rrc_ixd_reg_R_001,
	rrc_ixd_reg_R_010,
	rrc_ixd_reg_R_011,
	rrc_ixd_reg_R_100,
	rrc_ixd_reg_R_101,
	rrc_ixd,
	rrc_ixd_reg_R_111,
	rl_ixd_reg_R_000,
	rl_ixd_reg_R_001,
	rl_ixd_reg_R_010,
	rl_ixd_reg_R_011,
	rl_ixd_reg_R_100,
	rl_ixd_reg_R_101,
	rl_ixd,
	rl_ixd_reg_R_111,
	rr_ixd_reg_R_000,
	rr_ixd_reg_R_001,
	rr_ixd_reg_R_010,
	rr_ixd_reg_R_011,
	rr_ixd_reg_R_100,
	rr_ixd_reg_R_101,
	rr_ixd,
	rr_ixd_reg_R_111,
	sla_ixd_reg_R_000,
	sla_ixd_reg_R_001,
	sla_ixd_reg_R_010,
	sla_ixd_reg_R_011,
	sla_ixd_reg_R_100,
	sla_ixd_reg_R_101,
	sla_ixd,
	sla_ixd_reg_R_111,
	sra_ixd_reg_R_000,
	sra_ixd_reg_R_001,
	sra_ixd_reg_R_010,
	sra_ixd_reg_R_011,
	sra_ixd_reg_R_100,
	sra_ixd_reg_R_101,
	sra_ixd,
	sra_ixd_reg_R_111,
	sll_ixd_reg_R_000,
	sll_ixd_reg_R_001,
	sll_ixd_reg_R_010,
	sll_ixd_reg_R_011,
	sll_ixd_reg_R_100,
	sll_ixd_reg_R_101,
	sll_ixd,
	sll_ixd_reg_R_111,
	srl_ixd_reg_R_000,
	srl_ixd_reg_R_001,
	srl_ixd_reg_R_010,
	srl_ixd_reg_R_011,
	srl_ixd_reg_R_100,
	srl_ixd_reg_R_101,
	srl_ixd,
	srl_ixd_reg_R_111,
	bit_ixd_B_000_R_000,
	bit_ixd_B_000_R_001,
	bit_ixd_B_000_R_010,
	bit_ixd_B_000_R_011,
	bit_ixd_B_000_R_100,
	bit_ixd_B_000_R_101,
	bit_ixd_B_000_R_110,
	bit_ixd_B_000_R_111,
	bit_ixd_B_001_R_000,
	bit_ixd_B_001_R_001,
	bit_ixd_B_001_R_010,
	bit_ixd_B_001_R_011,
	bit_ixd_B_001_R_100,
	bit_ixd_B_001_R_101,
	bit_ixd_B_001_R_110,
	bit_ixd_B_001_R_111,
	bit_ixd_B_010_R_000,
	bit_ixd_B_010_R_001,
	bit_ixd_B_010_R_010,
	bit_ixd_B_010_R_011,
	bit_ixd_B_010_R_100,
	bit_ixd_B_010_R_101,
	bit_ixd_B_010_R_110,
	bit_ixd_B_010_R_111,
	bit_ixd_B_011_R_000,
	bit_ixd_B_011_R_001,
	bit_ixd_B_011_R_010,
	bit_ixd_B_011_R_011,
	bit_ixd_B_011_R_100,
	bit_ixd_B_011_R_101,
	bit_ixd_B_011_R_110,
	bit_ixd_B_011_R_111,
	bit_ixd_B_100_R_000,
	bit_ixd_B_100_R_001,
	bit_ixd_B_100_R_010,
	bit_ixd_B_100_R_011,
	bit_ixd_B_100_R_100,
	bit_ixd_B_100_R_101,
	bit_ixd_B_100_R_110,
	bit_ixd_B_100_R_111,
	bit_ixd_B_101_R_000,
	bit_ixd_B_101_R_001,
	bit_ixd_B_101_R_010,
	bit_ixd_B_101_R_011,
	bit_ixd_B_101_R_100,
	bit_ixd_B_101_R_101,
	bit_ixd_B_101_R_110,
	bit_ixd_B_101_R_111,
	bit_ixd_B_110_R_000,
	bit_ixd_B_110_R_001,
	bit_ixd_B_110_R_010,
	bit_ixd_B_110_R_011,
	bit_ixd_B_110_R_100,
	bit_ixd_B_110_R_101,
	bit_ixd_B_110_R_110,
	bit_ixd_B_110_R_111,
	bit_ixd_B_111_R_000,
	bit_ixd_B_111_R_001,
	bit_ixd_B_111_R_010,
	bit_ixd_B_111_R_011,
	bit_ixd_B_111_R_100,
	bit_ixd_B_111_R_101,
	bit_ixd_B_111_R_110,
	bit_ixd_B_111_R_111,
	res_ixd_reg_B_000_R_000,
	res_ixd_reg_B_000_R_001,
	res_ixd_reg_B_000_R_010,
	res_ixd_reg_B_000_R_011,
	res_ixd_reg_B_000_R_100,
	res_ixd_reg_B_000_R_101,
	res_ixd_B_000,
	res_ixd_reg_B_000_R_111,
	res_ixd_reg_B_001_R_000,
	res_ixd_reg_B_001_R_001,
	res_ixd_reg_B_001_R_010,
	res_ixd_reg_B_001_R_011,
	res_ixd_reg_B_001_R_100,
	res_ixd_reg_B_001_R_101,
	res_ixd_B_001,
	res_ixd_reg_B_001_R_111,
	res_ixd_reg_B_010_R_000,
	res_ixd_reg_B_010_R_001,
	res_ixd_reg_B_010_R_010,
	res_ixd_reg_B_010_R_011,
	res_ixd_reg_B_010_R_100,
	res_ixd_reg_B_010_R_101,
	res_ixd_B_010,
	res_ixd_reg_B_010_R_111,
	res_ixd_reg_B_011_R_000,
	res_ixd_reg_B_011_R_001,
	res_ixd_reg_B_011_R_010,
	res_ixd_reg_B_011_R_011,
	res_ixd_reg_B_011_R_100,
	res_ixd_reg_B_011_R_101,
	res_ixd_B_011,
	res_ixd_reg_B_011_R_111,
	res_ixd_reg_B_100_R_000,
	res_ixd_reg_B_100_R_001,
	res_ixd_reg_B_100_R_010,
	res_ixd_reg_B_100_R_011,
	res_ixd_reg_B_100_R_100,
	res_ixd_reg_B_100_R_101,
	res_ixd_B_100,
	res_ixd_reg_B_100_R_111,
	res_ixd_reg_B_101_R_000,
	res_ixd_reg_B_101_R_001,
	res_ixd_reg_B_101_R_010,
	res_ixd_reg_B_101_R_011,
	res_ixd_reg_B_101_R_100,
	res_ixd_reg_B_101_R_101,
	res_ixd_B_101,
	res_ixd_reg_B_101_R_111,
	res_ixd_reg_B_110_R_000,
	res_ixd_reg_B_110_R_001,
	res_ixd_reg_B_110_R_010,
	res_ixd_reg_B_110_R_011,
	res_ixd_reg_B_110_R_100,
	res_ixd_reg_B_110_R_101,
	res_ixd_B_110,
	res_ixd_reg_B_110_R_111,
	res_ixd_reg_B_111_R_000,
	res_ixd_reg_B_111_R_001,
	res_ixd_reg_B_111_R_010,
	res_ixd_reg_B_111_R_011,
	res_ixd_reg_B_111_R_100,
	res_ixd_reg_B_111_R_101,
	res_ixd_B_111,
	res_ixd_reg_B_111_R_111,
	set_ixd_reg_B_000_R_000,
	set_ixd_reg_B_000_R_001,
	set_ixd_reg_B_000_R_010,
	set_ixd_reg_B_000_R_011,
	set_ixd_reg_B_000_R_100,
	set_ixd_reg_B_000_R_101,
	set_ixd_B_000,
	set_ixd_reg_B_000_R_111,
	set_ixd_reg_B_001_R_000,
	set_ixd_reg_B_001_R_001,
	set_ixd_reg_B_001_R_010,
	set_ixd_reg_B_001_R_011,
	set_ixd_reg_B_001_R_100,
	set_ixd_reg_B_001_R_101,
	set_ixd_B_001,
	set_ixd_reg_B_001_R_111,
	set_ixd_reg_B_010_R_000,
	set_ixd_reg_B_010_R_001,
	set_ixd_reg_B_010_R_010,
	set_ixd_reg_B_010_R_011,
	set_ixd_reg_B_010_R_100,
	set_ixd_reg_B_010_R_101,
	set_ixd_B_010,
	set_ixd_reg_B_010_R_111,
	set_ixd_reg_B_011_R_000,
	set_ixd_reg_B_011_R_001,
	set_ixd_reg_B_011_R_010,
	set_ixd_reg_B_011_R_011,
	set_ixd_reg_B_011_R_100,
	set_ixd_reg_B_011_R_101,
	set_ixd_B_011,
	set_ixd_reg_B_011_R_111,
	set_ixd_reg_B_100_R_000,
	set_ixd_reg_B_100_R_001,
	set_ixd_reg_B_100_R_010,
	set_ixd_reg_B_100_R_011,
	set_ixd_reg_B_100_R_100,
	set_ixd_reg_B_100_R_101,
	set_ixd_B_100,
	set_ixd_reg_B_100_R_111,
	set_ixd_reg_B_101_R_000,
	set_ixd_reg_B_101_R_001,
	set_ixd_reg_B_101_R_010,
	set_ixd_reg_B_101_R_011,
	set_ixd_reg_B_101_R_100,
	set_ixd_reg_B_101_R_101,
	set_ixd_B_101,
	set_ixd_reg_B_101_R_111,
	set_ixd_reg_B_110_R_000,
	set_ixd_reg_B_110_R_001,
	set_ixd_reg_B_110_R_010,
	set_ixd_reg_B_110_R_011,
	set_ixd_reg_B_110_R_100,
	set_ixd_reg_B_110_R_101,
	set_ixd_B_110,
	set_ixd_reg_B_110_R_111,
	set_ixd_reg_B_111_R_000,
	set_ixd_reg_B_111_R_001,
	set_ixd_reg_B_111_R_010,
	set_ixd_reg_B_111_R_011,
	set_ixd_reg_B_111_R_100,
	set_ixd_reg_B_111_R_101,
	set_ixd_B_111,
	set_ixd_reg_B_111_R_111,
};
void rlc_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1 | context->main[0] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1 | context->main[1] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1 | context->main[2] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1 | context->main[3] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1 | context->main[4] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1 | context->main[5] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1 | tmp >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rlc_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	context->main[0] = context->main[0] >> 1 | context->main[0] << (8 - 1);
	context->zflag = context->main[0] == 0;
	context->last_flag_result = context->main[0];
	context->chflags = (context->chflags & ~128U) | (context->main[0] & 128U);
	gen_tmp8__ = (context->main[0] ^ (context->main[0] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	context->main[1] = context->main[1] >> 1 | context->main[1] << (8 - 1);
	context->zflag = context->main[1] == 0;
	context->last_flag_result = context->main[1];
	context->chflags = (context->chflags & ~128U) | (context->main[1] & 128U);
	gen_tmp8__ = (context->main[1] ^ (context->main[1] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	context->main[2] = context->main[2] >> 1 | context->main[2] << (8 - 1);
	context->zflag = context->main[2] == 0;
	context->last_flag_result = context->main[2];
	context->chflags = (context->chflags & ~128U) | (context->main[2] & 128U);
	gen_tmp8__ = (context->main[2] ^ (context->main[2] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	context->main[3] = context->main[3] >> 1 | context->main[3] << (8 - 1);
	context->zflag = context->main[3] == 0;
	context->last_flag_result = context->main[3];
	context->chflags = (context->chflags & ~128U) | (context->main[3] & 128U);
	gen_tmp8__ = (context->main[3] ^ (context->main[3] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	context->main[4] = context->main[4] >> 1 | context->main[4] << (8 - 1);
	context->zflag = context->main[4] == 0;
	context->last_flag_result = context->main[4];
	context->chflags = (context->chflags & ~128U) | (context->main[4] & 128U);
	gen_tmp8__ = (context->main[4] ^ (context->main[4] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	context->main[5] = context->main[5] >> 1 | context->main[5] << (8 - 1);
	context->zflag = context->main[5] == 0;
	context->last_flag_result = context->main[5];
	context->chflags = (context->chflags & ~128U) | (context->main[5] & 128U);
	gen_tmp8__ = (context->main[5] ^ (context->main[5] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	tmp = tmp >> 1 | tmp << (8 - 1);
	context->zflag = tmp == 0;
	context->last_flag_result = tmp;
	context->chflags = (context->chflags & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rrc_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	context->main[7] = context->main[7] >> 1 | context->main[7] << (8 - 1);
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	context->chflags = (context->chflags & ~128U) | (context->main[7] & 128U);
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1 | context->main[0] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1 | context->main[1] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1 | context->main[2] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1 | context->main[3] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1 | context->main[4] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1 | context->main[5] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1 | tmp >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rl_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] >> 1 | context->main[0] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] >> 1 | context->main[1] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] >> 1 | context->main[2] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] >> 1 | context->main[3] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] >> 1 | context->main[4] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] >> 1 | context->main[5] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp >> 1 | tmp << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void rr_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] >> 1 | context->main[7] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sla_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = (context->main[0] >> 1) | (context->main[0] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[0] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = (context->main[1] >> 1) | (context->main[1] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[1] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = (context->main[2] >> 1) | (context->main[2] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[2] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = (context->main[3] >> 1) | (context->main[3] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[3] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = (context->main[4] >> 1) | (context->main[4] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[4] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = (context->main[5] >> 1) | (context->main[5] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[5] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = (tmp >> 1) | (tmp & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (tmp << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sra_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = (context->main[7] >> 1) | (context->main[7] & 128 ? 0xFFFFFFFFU << (8 - 1) : 0);
	context->chflags = (context->chflags & ~128U) | (context->main[7] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[0] = 1 | context->main[0];
	gen_tmp8__ = (context->main[0] ^ (context->main[0] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[1] = 1 | context->main[1];
	gen_tmp8__ = (context->main[1] ^ (context->main[1] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[2] = 1 | context->main[2];
	gen_tmp8__ = (context->main[2] ^ (context->main[2] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[3] = 1 | context->main[3];
	gen_tmp8__ = (context->main[3] ^ (context->main[3] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[4] = 1 | context->main[4];
	gen_tmp8__ = (context->main[4] ^ (context->main[4] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[5] = 1 | context->main[5];
	gen_tmp8__ = (context->main[5] ^ (context->main[5] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	tmp = 1 | tmp;
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void sll_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t gen_tmp8__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] << 1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->zflag = 0;
	context->chflags &= ~8;
	context->nflag = 0;
	context->main[7] = 1 | context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1;
	gen_tmp16__ = context->main[0] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[0] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[0] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1;
	gen_tmp16__ = context->main[1] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[1] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[1] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1;
	gen_tmp16__ = context->main[2] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[2] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[2] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1;
	gen_tmp16__ = context->main[3] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[3] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[3] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1;
	gen_tmp16__ = context->main[4] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[4] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[4] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1;
	gen_tmp16__ = context->main[5] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[5] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[5] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1;
	gen_tmp16__ = tmp >> 1;
	context->chflags = (context->chflags & ~128U) | (tmp << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	tmp = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void srl_iyd_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1;
	gen_tmp16__ = context->main[7] >> 1;
	context->chflags = (context->chflags & ~128U) | (context->main[7] << 7U & 128U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	gen_tmp16__ = (gen_tmp16__ ^ (gen_tmp16__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp16__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void bit_iyd_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_000_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 1;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 2;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 4;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 8;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 16;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 32;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 64;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void bit_iyd_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->last_flag_result = context->wz >> 8;
	tmp = context->scratch1 & 128;
	context->zflag = tmp == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (tmp & 128U);
	gen_tmp8__ = (tmp ^ (tmp >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
}
void res_iyd_reg_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -2;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -2;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -2;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -2;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -2;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -2;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -2;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -2;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -3;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -3;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -3;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -3;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -3;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -3;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -3;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -3;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -5;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -5;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -5;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -5;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -5;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -5;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -5;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -5;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -9;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -9;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -9;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -9;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -9;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -9;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -9;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -9;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -17;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -17;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -17;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -17;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -17;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -17;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -17;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -17;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -33;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -33;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -33;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -33;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -33;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -33;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -33;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -33;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -65;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -65;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -65;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -65;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -65;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -65;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -65;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -65;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 & -129;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 & -129;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 & -129;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 & -129;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 & -129;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 & -129;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_B_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 & -129;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void res_iyd_reg_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 & -129;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_000_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 1;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_000_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 1;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_000_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 1;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_000_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 1;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_000_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 1;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_000_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 1;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 1;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_000_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 1;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_001_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 2;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_001_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 2;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_001_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 2;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_001_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 2;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_001_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 2;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_001_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 2;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 2;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_001_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 2;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_010_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 4;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_010_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 4;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_010_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 4;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_010_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 4;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_010_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 4;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_010_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 4;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 4;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_010_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 4;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_011_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 8;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_011_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 8;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_011_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 8;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_011_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 8;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_011_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 8;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_011_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 8;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 8;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_011_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 8;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_100_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 16;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_100_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 16;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_100_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 16;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_100_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 16;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_100_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 16;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_100_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 16;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 16;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_100_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 16;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_101_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 32;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_101_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 32;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_101_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 32;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_101_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 32;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_101_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 32;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_101_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 32;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 32;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_101_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 32;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_110_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 64;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_110_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 64;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_110_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 64;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_110_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 64;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_110_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 64;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_110_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 64;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 64;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_110_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 64;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_111_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[0] = context->scratch1 | 128;
	context->scratch1 = context->main[0];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_111_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[1] = context->scratch1 | 128;
	context->scratch1 = context->main[1];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_111_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[2] = context->scratch1 | 128;
	context->scratch1 = context->main[2];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_111_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[3] = context->scratch1 | 128;
	context->scratch1 = context->main[3];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_111_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[4] = context->scratch1 | 128;
	context->scratch1 = context->main[4];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_111_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[5] = context->scratch1 | 128;
	context->scratch1 = context->main[5];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_B_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	tmp = context->scratch1 | 128;
	context->scratch1 = tmp;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void set_iyd_reg_B_111_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->cycles += context->opts->gen.clock_divider * 1;
	context->main[7] = context->scratch1 | 128;
	context->scratch1 = context->main[7];
	context->scratch2 = context->wz;
	z80_write_8(context);
}
static impl_fun impl_fdcb[256] = {
	rlc_iyd_reg_R_000,
	rlc_iyd_reg_R_001,
	rlc_iyd_reg_R_010,
	rlc_iyd_reg_R_011,
	rlc_iyd_reg_R_100,
	rlc_iyd_reg_R_101,
	rlc_iyd,
	rlc_iyd_reg_R_111,
	rrc_iyd_reg_R_000,
	rrc_iyd_reg_R_001,
	rrc_iyd_reg_R_010,
	rrc_iyd_reg_R_011,
	rrc_iyd_reg_R_100,
	rrc_iyd_reg_R_101,
	rrc_iyd,
	rrc_iyd_reg_R_111,
	rl_iyd_reg_R_000,
	rl_iyd_reg_R_001,
	rl_iyd_reg_R_010,
	rl_iyd_reg_R_011,
	rl_iyd_reg_R_100,
	rl_iyd_reg_R_101,
	rl_iyd,
	rl_iyd_reg_R_111,
	rr_iyd_reg_R_000,
	rr_iyd_reg_R_001,
	rr_iyd_reg_R_010,
	rr_iyd_reg_R_011,
	rr_iyd_reg_R_100,
	rr_iyd_reg_R_101,
	rr_iyd,
	rr_iyd_reg_R_111,
	sla_iyd_reg_R_000,
	sla_iyd_reg_R_001,
	sla_iyd_reg_R_010,
	sla_iyd_reg_R_011,
	sla_iyd_reg_R_100,
	sla_iyd_reg_R_101,
	sla_iyd,
	sla_iyd_reg_R_111,
	sra_iyd_reg_R_000,
	sra_iyd_reg_R_001,
	sra_iyd_reg_R_010,
	sra_iyd_reg_R_011,
	sra_iyd_reg_R_100,
	sra_iyd_reg_R_101,
	sra_iyd,
	sra_iyd_reg_R_111,
	sll_iyd_reg_R_000,
	sll_iyd_reg_R_001,
	sll_iyd_reg_R_010,
	sll_iyd_reg_R_011,
	sll_iyd_reg_R_100,
	sll_iyd_reg_R_101,
	sll_iyd,
	sll_iyd_reg_R_111,
	srl_iyd_reg_R_000,
	srl_iyd_reg_R_001,
	srl_iyd_reg_R_010,
	srl_iyd_reg_R_011,
	srl_iyd_reg_R_100,
	srl_iyd_reg_R_101,
	srl_iyd,
	srl_iyd_reg_R_111,
	bit_iyd_B_000_R_000,
	bit_iyd_B_000_R_001,
	bit_iyd_B_000_R_010,
	bit_iyd_B_000_R_011,
	bit_iyd_B_000_R_100,
	bit_iyd_B_000_R_101,
	bit_iyd_B_000_R_110,
	bit_iyd_B_000_R_111,
	bit_iyd_B_001_R_000,
	bit_iyd_B_001_R_001,
	bit_iyd_B_001_R_010,
	bit_iyd_B_001_R_011,
	bit_iyd_B_001_R_100,
	bit_iyd_B_001_R_101,
	bit_iyd_B_001_R_110,
	bit_iyd_B_001_R_111,
	bit_iyd_B_010_R_000,
	bit_iyd_B_010_R_001,
	bit_iyd_B_010_R_010,
	bit_iyd_B_010_R_011,
	bit_iyd_B_010_R_100,
	bit_iyd_B_010_R_101,
	bit_iyd_B_010_R_110,
	bit_iyd_B_010_R_111,
	bit_iyd_B_011_R_000,
	bit_iyd_B_011_R_001,
	bit_iyd_B_011_R_010,
	bit_iyd_B_011_R_011,
	bit_iyd_B_011_R_100,
	bit_iyd_B_011_R_101,
	bit_iyd_B_011_R_110,
	bit_iyd_B_011_R_111,
	bit_iyd_B_100_R_000,
	bit_iyd_B_100_R_001,
	bit_iyd_B_100_R_010,
	bit_iyd_B_100_R_011,
	bit_iyd_B_100_R_100,
	bit_iyd_B_100_R_101,
	bit_iyd_B_100_R_110,
	bit_iyd_B_100_R_111,
	bit_iyd_B_101_R_000,
	bit_iyd_B_101_R_001,
	bit_iyd_B_101_R_010,
	bit_iyd_B_101_R_011,
	bit_iyd_B_101_R_100,
	bit_iyd_B_101_R_101,
	bit_iyd_B_101_R_110,
	bit_iyd_B_101_R_111,
	bit_iyd_B_110_R_000,
	bit_iyd_B_110_R_001,
	bit_iyd_B_110_R_010,
	bit_iyd_B_110_R_011,
	bit_iyd_B_110_R_100,
	bit_iyd_B_110_R_101,
	bit_iyd_B_110_R_110,
	bit_iyd_B_110_R_111,
	bit_iyd_B_111_R_000,
	bit_iyd_B_111_R_001,
	bit_iyd_B_111_R_010,
	bit_iyd_B_111_R_011,
	bit_iyd_B_111_R_100,
	bit_iyd_B_111_R_101,
	bit_iyd_B_111_R_110,
	bit_iyd_B_111_R_111,
	res_iyd_reg_B_000_R_000,
	res_iyd_reg_B_000_R_001,
	res_iyd_reg_B_000_R_010,
	res_iyd_reg_B_000_R_011,
	res_iyd_reg_B_000_R_100,
	res_iyd_reg_B_000_R_101,
	res_iyd_B_000,
	res_iyd_reg_B_000_R_111,
	res_iyd_reg_B_001_R_000,
	res_iyd_reg_B_001_R_001,
	res_iyd_reg_B_001_R_010,
	res_iyd_reg_B_001_R_011,
	res_iyd_reg_B_001_R_100,
	res_iyd_reg_B_001_R_101,
	res_iyd_B_001,
	res_iyd_reg_B_001_R_111,
	res_iyd_reg_B_010_R_000,
	res_iyd_reg_B_010_R_001,
	res_iyd_reg_B_010_R_010,
	res_iyd_reg_B_010_R_011,
	res_iyd_reg_B_010_R_100,
	res_iyd_reg_B_010_R_101,
	res_iyd_B_010,
	res_iyd_reg_B_010_R_111,
	res_iyd_reg_B_011_R_000,
	res_iyd_reg_B_011_R_001,
	res_iyd_reg_B_011_R_010,
	res_iyd_reg_B_011_R_011,
	res_iyd_reg_B_011_R_100,
	res_iyd_reg_B_011_R_101,
	res_iyd_B_011,
	res_iyd_reg_B_011_R_111,
	res_iyd_reg_B_100_R_000,
	res_iyd_reg_B_100_R_001,
	res_iyd_reg_B_100_R_010,
	res_iyd_reg_B_100_R_011,
	res_iyd_reg_B_100_R_100,
	res_iyd_reg_B_100_R_101,
	res_iyd_B_100,
	res_iyd_reg_B_100_R_111,
	res_iyd_reg_B_101_R_000,
	res_iyd_reg_B_101_R_001,
	res_iyd_reg_B_101_R_010,
	res_iyd_reg_B_101_R_011,
	res_iyd_reg_B_101_R_100,
	res_iyd_reg_B_101_R_101,
	res_iyd_B_101,
	res_iyd_reg_B_101_R_111,
	res_iyd_reg_B_110_R_000,
	res_iyd_reg_B_110_R_001,
	res_iyd_reg_B_110_R_010,
	res_iyd_reg_B_110_R_011,
	res_iyd_reg_B_110_R_100,
	res_iyd_reg_B_110_R_101,
	res_iyd_B_110,
	res_iyd_reg_B_110_R_111,
	res_iyd_reg_B_111_R_000,
	res_iyd_reg_B_111_R_001,
	res_iyd_reg_B_111_R_010,
	res_iyd_reg_B_111_R_011,
	res_iyd_reg_B_111_R_100,
	res_iyd_reg_B_111_R_101,
	res_iyd_B_111,
	res_iyd_reg_B_111_R_111,
	set_iyd_reg_B_000_R_000,
	set_iyd_reg_B_000_R_001,
	set_iyd_reg_B_000_R_010,
	set_iyd_reg_B_000_R_011,
	set_iyd_reg_B_000_R_100,
	set_iyd_reg_B_000_R_101,
	set_iyd_B_000,
	set_iyd_reg_B_000_R_111,
	set_iyd_reg_B_001_R_000,
	set_iyd_reg_B_001_R_001,
	set_iyd_reg_B_001_R_010,
	set_iyd_reg_B_001_R_011,
	set_iyd_reg_B_001_R_100,
	set_iyd_reg_B_001_R_101,
	set_iyd_B_001,
	set_iyd_reg_B_001_R_111,
	set_iyd_reg_B_010_R_000,
	set_iyd_reg_B_010_R_001,
	set_iyd_reg_B_010_R_010,
	set_iyd_reg_B_010_R_011,
	set_iyd_reg_B_010_R_100,
	set_iyd_reg_B_010_R_101,
	set_iyd_B_010,
	set_iyd_reg_B_010_R_111,
	set_iyd_reg_B_011_R_000,
	set_iyd_reg_B_011_R_001,
	set_iyd_reg_B_011_R_010,
	set_iyd_reg_B_011_R_011,
	set_iyd_reg_B_011_R_100,
	set_iyd_reg_B_011_R_101,
	set_iyd_B_011,
	set_iyd_reg_B_011_R_111,
	set_iyd_reg_B_100_R_000,
	set_iyd_reg_B_100_R_001,
	set_iyd_reg_B_100_R_010,
	set_iyd_reg_B_100_R_011,
	set_iyd_reg_B_100_R_100,
	set_iyd_reg_B_100_R_101,
	set_iyd_B_100,
	set_iyd_reg_B_100_R_111,
	set_iyd_reg_B_101_R_000,
	set_iyd_reg_B_101_R_001,
	set_iyd_reg_B_101_R_010,
	set_iyd_reg_B_101_R_011,
	set_iyd_reg_B_101_R_100,
	set_iyd_reg_B_101_R_101,
	set_iyd_B_101,
	set_iyd_reg_B_101_R_111,
	set_iyd_reg_B_110_R_000,
	set_iyd_reg_B_110_R_001,
	set_iyd_reg_B_110_R_010,
	set_iyd_reg_B_110_R_011,
	set_iyd_reg_B_110_R_100,
	set_iyd_reg_B_110_R_101,
	set_iyd_B_110,
	set_iyd_reg_B_110_R_111,
	set_iyd_reg_B_111_R_000,
	set_iyd_reg_B_111_R_001,
	set_iyd_reg_B_111_R_010,
	set_iyd_reg_B_111_R_011,
	set_iyd_reg_B_111_R_100,
	set_iyd_reg_B_111_R_101,
	set_iyd_B_111,
	set_iyd_reg_B_111_R_111,
};
void dd_normal_O_00000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[0](context, target_cycle);
}
void dd_normal_O_00000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[1](context, target_cycle);
}
void dd_normal_O_00000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[2](context, target_cycle);
}
void dd_normal_O_00000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[3](context, target_cycle);
}
void dd_normal_O_00000100(z80_context *context, uint32_t target_cycle)
{
	impl_main[4](context, target_cycle);
}
void dd_normal_O_00000101(z80_context *context, uint32_t target_cycle)
{
	impl_main[5](context, target_cycle);
}
void dd_normal_O_00000110(z80_context *context, uint32_t target_cycle)
{
	impl_main[6](context, target_cycle);
}
void dd_normal_O_00000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[7](context, target_cycle);
}
void dd_normal_O_00001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[8](context, target_cycle);
}
void add_ix_bc(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	gen_tmp32__ = context->scratch1 + context->ix;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->scratch1 ^ context->ix ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->ix = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void dd_normal_O_00001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[10](context, target_cycle);
}
void dd_normal_O_00001011(z80_context *context, uint32_t target_cycle)
{
	impl_main[11](context, target_cycle);
}
void dd_normal_O_00001100(z80_context *context, uint32_t target_cycle)
{
	impl_main[12](context, target_cycle);
}
void dd_normal_O_00001101(z80_context *context, uint32_t target_cycle)
{
	impl_main[13](context, target_cycle);
}
void dd_normal_O_00001110(z80_context *context, uint32_t target_cycle)
{
	impl_main[14](context, target_cycle);
}
void dd_normal_O_00001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[15](context, target_cycle);
}
void dd_normal_O_00010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[16](context, target_cycle);
}
void dd_normal_O_00010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[17](context, target_cycle);
}
void dd_normal_O_00010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[18](context, target_cycle);
}
void dd_normal_O_00010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[19](context, target_cycle);
}
void dd_normal_O_00010100(z80_context *context, uint32_t target_cycle)
{
	impl_main[20](context, target_cycle);
}
void dd_normal_O_00010101(z80_context *context, uint32_t target_cycle)
{
	impl_main[21](context, target_cycle);
}
void dd_normal_O_00010110(z80_context *context, uint32_t target_cycle)
{
	impl_main[22](context, target_cycle);
}
void dd_normal_O_00010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[23](context, target_cycle);
}
void dd_normal_O_00011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[24](context, target_cycle);
}
void add_ix_de(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	context->scratch1 = context->main[2] << 8;
	context->scratch1 = context->main[3] | context->scratch1;
	gen_tmp32__ = context->scratch1 + context->ix;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->scratch1 ^ context->ix ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->ix = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void dd_normal_O_00011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[26](context, target_cycle);
}
void dd_normal_O_00011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[27](context, target_cycle);
}
void dd_normal_O_00011100(z80_context *context, uint32_t target_cycle)
{
	impl_main[28](context, target_cycle);
}
void dd_normal_O_00011101(z80_context *context, uint32_t target_cycle)
{
	impl_main[29](context, target_cycle);
}
void dd_normal_O_00011110(z80_context *context, uint32_t target_cycle)
{
	impl_main[30](context, target_cycle);
}
void dd_normal_O_00011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[31](context, target_cycle);
}
void dd_normal_O_00100000(z80_context *context, uint32_t target_cycle)
{
	impl_main[32](context, target_cycle);
}
void ld_ix_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->ix = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->ix = context->scratch1 | context->ix;
}
void ld_ix_to_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->ix;
	z80_write_8(context);
	context->wz = 1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->ix >> 8;
	z80_write_8(context);
	context->wz = 1 + context->wz;
}
void inc_ix(z80_context *context, uint32_t target_cycle)
{
	context->ix = 1 + context->ix;
}
void inc_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = 256 + context->ix;
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp16__ >> 8U & 32U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp16__ >> 8U & 8U);
	context->pvflag = (((256 ^ (~context->ix))) & (256 ^ gen_tmp16__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp16__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((256 ^ context->ix ^ gen_tmp16__) >> 9U & 8U);
	context->zflag = (gen_tmp16__ & 65535) == 0;
	context->ix = gen_tmp16__;
	context->nflag = 0;
}
void dec_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->ix - 256;
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp16__ >> 8U & 32U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp16__ >> 8U & 8U);
	context->pvflag = (((context->ix ^ 256)) & (context->ix ^ gen_tmp16__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp16__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((context->ix ^ 256 ^ gen_tmp16__) >> 9U & 8U);
	context->zflag = (gen_tmp16__ & 65535) == 0;
	context->ix = gen_tmp16__;
	context->nflag = 1;
}
void ld_immed_ixh(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->ix = 255 & context->ix;
	context->ix = context->scratch1 | context->ix;
}
void dd_normal_O_00100111(z80_context *context, uint32_t target_cycle)
{
	impl_main[39](context, target_cycle);
}
void dd_normal_O_00101000(z80_context *context, uint32_t target_cycle)
{
	impl_main[40](context, target_cycle);
}
void add_ix_ix(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	gen_tmp32__ = context->ix + context->ix;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->ix ^ context->ix ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->ix = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_ix_from_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->ix = context->scratch1;
	context->wz = 1 + context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->scratch1 = context->scratch1 << 8;
	context->ix = context->scratch1 | context->ix;
	context->wz = 1 + context->wz;
}
void dec_ix(z80_context *context, uint32_t target_cycle)
{
	context->ix = context->ix - 1;
}
void inc_ixl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	tmp = context->ix;
	gen_tmp8__ = 1 + tmp;
	context->pvflag = (((1 ^ (~tmp))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ tmp ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 0;
	context->ix = 65280 & context->ix;
	context->ix = tmp | context->ix;
}
void dec_ixl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	tmp = context->ix;
	gen_tmp8__ = tmp - 1;
	context->pvflag = (((tmp ^ 1)) & (tmp ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((tmp ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 1;
	context->ix = 65280 & context->ix;
	context->ix = tmp | context->ix;
}
void ld_immed_ixl(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->ix = 65280 & context->ix;
	context->ix = context->scratch1 | context->ix;
}
void dd_normal_O_00101111(z80_context *context, uint32_t target_cycle)
{
	impl_main[47](context, target_cycle);
}
void dd_normal_O_00110000(z80_context *context, uint32_t target_cycle)
{
	impl_main[48](context, target_cycle);
}
void dd_normal_O_00110001(z80_context *context, uint32_t target_cycle)
{
	impl_main[49](context, target_cycle);
}
void dd_normal_O_00110010(z80_context *context, uint32_t target_cycle)
{
	impl_main[50](context, target_cycle);
}
void dd_normal_O_00110011(z80_context *context, uint32_t target_cycle)
{
	impl_main[51](context, target_cycle);
}
void inc_ixd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp8__ = 1 + tmp;
	context->pvflag = (((1 ^ (~tmp))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ tmp ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void dec_ixd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp8__ = tmp - 1;
	context->pvflag = (((tmp ^ 1)) & (tmp ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((tmp ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 1;
	context->scratch1 = tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void ld_to_ixd_immed(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 2;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void dd_normal_O_00110111(z80_context *context, uint32_t target_cycle)
{
	impl_main[55](context, target_cycle);
}
void dd_normal_O_00111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[56](context, target_cycle);
}
void add_ix_sp(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	gen_tmp32__ = context->sp + context->ix;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->sp ^ context->ix ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->ix = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void dd_normal_O_00111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[58](context, target_cycle);
}
void dd_normal_O_00111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[59](context, target_cycle);
}
void dd_normal_O_00111100(z80_context *context, uint32_t target_cycle)
{
	impl_main[60](context, target_cycle);
}
void dd_normal_O_00111101(z80_context *context, uint32_t target_cycle)
{
	impl_main[61](context, target_cycle);
}
void dd_normal_O_00111110(z80_context *context, uint32_t target_cycle)
{
	impl_main[62](context, target_cycle);
}
void dd_normal_O_00111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[63](context, target_cycle);
}
void dd_normal_O_01000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[64](context, target_cycle);
}
void dd_normal_O_01000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[65](context, target_cycle);
}
void dd_normal_O_01000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[66](context, target_cycle);
}
void dd_normal_O_01000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[67](context, target_cycle);
}
void ld_from_ixh_D_000(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->ix >> 8;
}
void ld_from_ixl_D_000(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->ix;
}
void ld_from_ix_R_000(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[0] = context->scratch1;
}
void dd_normal_O_01000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[71](context, target_cycle);
}
void dd_normal_O_01001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[72](context, target_cycle);
}
void dd_normal_O_01001001(z80_context *context, uint32_t target_cycle)
{
	impl_main[73](context, target_cycle);
}
void dd_normal_O_01001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[74](context, target_cycle);
}
void dd_normal_O_01001011(z80_context *context, uint32_t target_cycle)
{
	impl_main[75](context, target_cycle);
}
void ld_from_ixh_D_001(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->ix >> 8;
}
void ld_from_ixl_D_001(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->ix;
}
void ld_from_ix_R_001(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[1] = context->scratch1;
}
void dd_normal_O_01001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[79](context, target_cycle);
}
void dd_normal_O_01010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[80](context, target_cycle);
}
void dd_normal_O_01010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[81](context, target_cycle);
}
void dd_normal_O_01010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[82](context, target_cycle);
}
void dd_normal_O_01010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[83](context, target_cycle);
}
void ld_from_ixh_D_010(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->ix >> 8;
}
void ld_from_ixl_D_010(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->ix;
}
void ld_from_ix_R_010(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[2] = context->scratch1;
}
void dd_normal_O_01010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[87](context, target_cycle);
}
void dd_normal_O_01011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[88](context, target_cycle);
}
void dd_normal_O_01011001(z80_context *context, uint32_t target_cycle)
{
	impl_main[89](context, target_cycle);
}
void dd_normal_O_01011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[90](context, target_cycle);
}
void dd_normal_O_01011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[91](context, target_cycle);
}
void ld_from_ixh_D_011(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->ix >> 8;
}
void ld_from_ixl_D_011(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->ix;
}
void ld_from_ix_R_011(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[3] = context->scratch1;
}
void dd_normal_O_01011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[95](context, target_cycle);
}
void ld_to_ixh_S_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->ix = 255 & context->ix;
	tmp = context->main[0] << 8;
	context->ix = tmp | context->ix;
}
void ld_to_ixh_S_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->ix = 255 & context->ix;
	tmp = context->main[1] << 8;
	context->ix = tmp | context->ix;
}
void ld_to_ixh_S_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->ix = 255 & context->ix;
	tmp = context->main[2] << 8;
	context->ix = tmp | context->ix;
}
void ld_to_ixh_S_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->ix = 255 & context->ix;
	tmp = context->main[3] << 8;
	context->ix = tmp | context->ix;
}
void ld_ixb_to_ixb_D_0_S_0(z80_context *context, uint32_t target_cycle)
{
}
void ld_ixl_to_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	tmp = context->ix << 8;
	context->ix = 255 & context->ix;
	context->ix = tmp | context->ix;
}
void ld_from_ix_R_100(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[4] = context->scratch1;
}
void ld_to_ixh_S_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->ix = 255 & context->ix;
	tmp = context->main[7] << 8;
	context->ix = tmp | context->ix;
}
void ld_to_ixl_S_000(z80_context *context, uint32_t target_cycle)
{
	context->ix = 65280 & context->ix;
	context->ix = context->main[0] | context->ix;
}
void ld_to_ixl_S_001(z80_context *context, uint32_t target_cycle)
{
	context->ix = 65280 & context->ix;
	context->ix = context->main[1] | context->ix;
}
void ld_to_ixl_S_010(z80_context *context, uint32_t target_cycle)
{
	context->ix = 65280 & context->ix;
	context->ix = context->main[2] | context->ix;
}
void ld_to_ixl_S_011(z80_context *context, uint32_t target_cycle)
{
	context->ix = 65280 & context->ix;
	context->ix = context->main[3] | context->ix;
}
void ld_ixh_to_ixl(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	tmp = context->ix >> 8;
	context->ix = 65280 & context->ix;
	context->ix = tmp | context->ix;
}
void ld_ixb_to_ixb_D_1_S_1(z80_context *context, uint32_t target_cycle)
{
}
void ld_from_ix_R_101(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[5] = context->scratch1;
}
void ld_to_ixl_S_111(z80_context *context, uint32_t target_cycle)
{
	context->ix = 65280 & context->ix;
	context->ix = context->main[7] | context->ix;
}
void ld_to_ix_R_000(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[0];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_ix_R_001(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[1];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_ix_R_010(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[2];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_ix_R_011(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[3];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_ix_R_100(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[4];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_ix_R_101(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[5];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_from_ix_R_110(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[6] = context->scratch1;
}
void ld_to_ix_R_111(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[7];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void dd_normal_O_01111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[120](context, target_cycle);
}
void dd_normal_O_01111001(z80_context *context, uint32_t target_cycle)
{
	impl_main[121](context, target_cycle);
}
void dd_normal_O_01111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[122](context, target_cycle);
}
void dd_normal_O_01111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[123](context, target_cycle);
}
void ld_from_ixh_D_111(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->ix >> 8;
}
void ld_from_ixl_D_111(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->ix;
}
void ld_from_ix_R_111(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->scratch1;
}
void dd_normal_O_01111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[127](context, target_cycle);
}
void dd_normal_O_10000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[128](context, target_cycle);
}
void dd_normal_O_10000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[129](context, target_cycle);
}
void dd_normal_O_10000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[130](context, target_cycle);
}
void dd_normal_O_10000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[131](context, target_cycle);
}
void add_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix >> 8;
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_ixl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix & 255;
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void dd_normal_O_10000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[135](context, target_cycle);
}
void dd_normal_O_10001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[136](context, target_cycle);
}
void dd_normal_O_10001001(z80_context *context, uint32_t target_cycle)
{
	impl_main[137](context, target_cycle);
}
void dd_normal_O_10001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[138](context, target_cycle);
}
void dd_normal_O_10001011(z80_context *context, uint32_t target_cycle)
{
	impl_main[139](context, target_cycle);
}
void adc_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix >> 8;
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_ixl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix & 255;
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void dd_normal_O_10001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[143](context, target_cycle);
}
void dd_normal_O_10010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[144](context, target_cycle);
}
void dd_normal_O_10010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[145](context, target_cycle);
}
void dd_normal_O_10010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[146](context, target_cycle);
}
void dd_normal_O_10010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[147](context, target_cycle);
}
void sub_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix >> 8;
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_ixl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix & 255;
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void dd_normal_O_10010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[151](context, target_cycle);
}
void dd_normal_O_10011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[152](context, target_cycle);
}
void dd_normal_O_10011001(z80_context *context, uint32_t target_cycle)
{
	impl_main[153](context, target_cycle);
}
void dd_normal_O_10011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[154](context, target_cycle);
}
void dd_normal_O_10011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[155](context, target_cycle);
}
void sbc_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix >> 8;
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_ixl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->ix & 255;
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void dd_normal_O_10011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[159](context, target_cycle);
}
void dd_normal_O_10100000(z80_context *context, uint32_t target_cycle)
{
	impl_main[160](context, target_cycle);
}
void dd_normal_O_10100001(z80_context *context, uint32_t target_cycle)
{
	impl_main[161](context, target_cycle);
}
void dd_normal_O_10100010(z80_context *context, uint32_t target_cycle)
{
	impl_main[162](context, target_cycle);
}
void dd_normal_O_10100011(z80_context *context, uint32_t target_cycle)
{
	impl_main[163](context, target_cycle);
}
void and_ixh(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->ix >> 8;
	context->main[7] = context->scratch1 & context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_ixl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->ix & context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_ixd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->main[7] & context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void dd_normal_O_10100111(z80_context *context, uint32_t target_cycle)
{
	impl_main[167](context, target_cycle);
}
void dd_normal_O_10101000(z80_context *context, uint32_t target_cycle)
{
	impl_main[168](context, target_cycle);
}
void dd_normal_O_10101001(z80_context *context, uint32_t target_cycle)
{
	impl_main[169](context, target_cycle);
}
void dd_normal_O_10101010(z80_context *context, uint32_t target_cycle)
{
	impl_main[170](context, target_cycle);
}
void dd_normal_O_10101011(z80_context *context, uint32_t target_cycle)
{
	impl_main[171](context, target_cycle);
}
void xor_ixh(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->ix >> 8;
	context->main[7] = context->scratch1 ^ context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_ixl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->ix ^ context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_ixd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->main[7] ^ context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void dd_normal_O_10101111(z80_context *context, uint32_t target_cycle)
{
	impl_main[175](context, target_cycle);
}
void dd_normal_O_10110000(z80_context *context, uint32_t target_cycle)
{
	impl_main[176](context, target_cycle);
}
void dd_normal_O_10110001(z80_context *context, uint32_t target_cycle)
{
	impl_main[177](context, target_cycle);
}
void dd_normal_O_10110010(z80_context *context, uint32_t target_cycle)
{
	impl_main[178](context, target_cycle);
}
void dd_normal_O_10110011(z80_context *context, uint32_t target_cycle)
{
	impl_main[179](context, target_cycle);
}
void or_ixh(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->ix >> 8;
	context->main[7] = context->scratch1 | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_ixl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->ix | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_ixd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->main[7] | context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void dd_normal_O_10110111(z80_context *context, uint32_t target_cycle)
{
	impl_main[183](context, target_cycle);
}
void dd_normal_O_10111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[184](context, target_cycle);
}
void dd_normal_O_10111001(z80_context *context, uint32_t target_cycle)
{
	impl_main[185](context, target_cycle);
}
void dd_normal_O_10111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[186](context, target_cycle);
}
void dd_normal_O_10111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[187](context, target_cycle);
}
void cp_ixh(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	tmp = context->ix >> 8;
	context->last_flag_result = tmp;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_ixl(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	tmp = context->ix;
	context->last_flag_result = context->ix;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_ixd(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	tmp = context->scratch1;
	context->last_flag_result = context->scratch1;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void dd_normal_O_10111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[191](context, target_cycle);
}
void dd_normal_O_11000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[192](context, target_cycle);
}
void dd_normal_O_11000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[193](context, target_cycle);
}
void dd_normal_O_11000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[194](context, target_cycle);
}
void dd_normal_O_11000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[195](context, target_cycle);
}
void dd_normal_O_11000100(z80_context *context, uint32_t target_cycle)
{
	impl_main[196](context, target_cycle);
}
void dd_normal_O_11000101(z80_context *context, uint32_t target_cycle)
{
	impl_main[197](context, target_cycle);
}
void dd_normal_O_11000110(z80_context *context, uint32_t target_cycle)
{
	impl_main[198](context, target_cycle);
}
void dd_normal_O_11000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[199](context, target_cycle);
}
void dd_normal_O_11001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[200](context, target_cycle);
}
void dd_normal_O_11001001(z80_context *context, uint32_t target_cycle)
{
	impl_main[201](context, target_cycle);
}
void dd_normal_O_11001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[202](context, target_cycle);
}
void ddcb_prefix(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->ix;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->cycles += context->opts->gen.clock_divider * 2;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	impl_ddcb[context->scratch1](context, target_cycle);
}
void dd_normal_O_11001100(z80_context *context, uint32_t target_cycle)
{
	impl_main[204](context, target_cycle);
}
void dd_normal_O_11001101(z80_context *context, uint32_t target_cycle)
{
	impl_main[205](context, target_cycle);
}
void dd_normal_O_11001110(z80_context *context, uint32_t target_cycle)
{
	impl_main[206](context, target_cycle);
}
void dd_normal_O_11001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[207](context, target_cycle);
}
void dd_normal_O_11010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[208](context, target_cycle);
}
void dd_normal_O_11010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[209](context, target_cycle);
}
void dd_normal_O_11010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[210](context, target_cycle);
}
void dd_normal_O_11010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[211](context, target_cycle);
}
void dd_normal_O_11010100(z80_context *context, uint32_t target_cycle)
{
	impl_main[212](context, target_cycle);
}
void dd_normal_O_11010101(z80_context *context, uint32_t target_cycle)
{
	impl_main[213](context, target_cycle);
}
void dd_normal_O_11010110(z80_context *context, uint32_t target_cycle)
{
	impl_main[214](context, target_cycle);
}
void dd_normal_O_11010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[215](context, target_cycle);
}
void dd_normal_O_11011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[216](context, target_cycle);
}
void dd_normal_O_11011001(z80_context *context, uint32_t target_cycle)
{
	impl_main[217](context, target_cycle);
}
void dd_normal_O_11011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[218](context, target_cycle);
}
void dd_normal_O_11011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[219](context, target_cycle);
}
void dd_normal_O_11011100(z80_context *context, uint32_t target_cycle)
{
	impl_main[220](context, target_cycle);
}
void dd_normal_O_11011101(z80_context *context, uint32_t target_cycle)
{
	impl_main[221](context, target_cycle);
}
void dd_normal_O_11011110(z80_context *context, uint32_t target_cycle)
{
	impl_main[222](context, target_cycle);
}
void dd_normal_O_11011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[223](context, target_cycle);
}
void dd_normal_O_11100000(z80_context *context, uint32_t target_cycle)
{
	impl_main[224](context, target_cycle);
}
void pop_ix(z80_context *context, uint32_t target_cycle)
{
	uint16_t ixh;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->ix = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	ixh = context->scratch1;
	ixh = ixh << 8;
	context->ix = ixh | context->ix;
}
void dd_normal_O_11100010(z80_context *context, uint32_t target_cycle)
{
	impl_main[226](context, target_cycle);
}
void ex_sp_ix(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->scratch1 = context->ix;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->sp;
	z80_write_8(context);
	context->scratch1 = 1 + context->sp;
	z80_read_8(context);
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->ix >> 8;
	context->cycles += context->opts->gen.clock_divider * 2;
	context->scratch2 = 1 + context->sp;
	z80_write_8(context);
	context->ix = context->wz;
}
void dd_normal_O_11100100(z80_context *context, uint32_t target_cycle)
{
	impl_main[228](context, target_cycle);
}
void push_ix(z80_context *context, uint32_t target_cycle)
{
	uint8_t ixh;
	ixh = context->ix >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = ixh;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->ix;
	z80_write_8(context);
}
void dd_normal_O_11100110(z80_context *context, uint32_t target_cycle)
{
	impl_main[230](context, target_cycle);
}
void dd_normal_O_11100111(z80_context *context, uint32_t target_cycle)
{
	impl_main[231](context, target_cycle);
}
void dd_normal_O_11101000(z80_context *context, uint32_t target_cycle)
{
	impl_main[232](context, target_cycle);
}
void jp_ix(z80_context *context, uint32_t target_cycle)
{
	context->pc = context->ix;
}
void dd_normal_O_11101010(z80_context *context, uint32_t target_cycle)
{
	impl_main[234](context, target_cycle);
}
void dd_normal_O_11101011(z80_context *context, uint32_t target_cycle)
{
	impl_main[235](context, target_cycle);
}
void dd_normal_O_11101100(z80_context *context, uint32_t target_cycle)
{
	impl_main[236](context, target_cycle);
}
void dd_normal_O_11101101(z80_context *context, uint32_t target_cycle)
{
	impl_main[237](context, target_cycle);
}
void dd_normal_O_11101110(z80_context *context, uint32_t target_cycle)
{
	impl_main[238](context, target_cycle);
}
void dd_normal_O_11101111(z80_context *context, uint32_t target_cycle)
{
	impl_main[239](context, target_cycle);
}
void dd_normal_O_11110000(z80_context *context, uint32_t target_cycle)
{
	impl_main[240](context, target_cycle);
}
void dd_normal_O_11110001(z80_context *context, uint32_t target_cycle)
{
	impl_main[241](context, target_cycle);
}
void dd_normal_O_11110010(z80_context *context, uint32_t target_cycle)
{
	impl_main[242](context, target_cycle);
}
void dd_normal_O_11110011(z80_context *context, uint32_t target_cycle)
{
	impl_main[243](context, target_cycle);
}
void dd_normal_O_11110100(z80_context *context, uint32_t target_cycle)
{
	impl_main[244](context, target_cycle);
}
void dd_normal_O_11110101(z80_context *context, uint32_t target_cycle)
{
	impl_main[245](context, target_cycle);
}
void dd_normal_O_11110110(z80_context *context, uint32_t target_cycle)
{
	impl_main[246](context, target_cycle);
}
void dd_normal_O_11110111(z80_context *context, uint32_t target_cycle)
{
	impl_main[247](context, target_cycle);
}
void dd_normal_O_11111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[248](context, target_cycle);
}
void ld_sp_ix(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 2;
	context->sp = context->ix;
}
void dd_normal_O_11111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[250](context, target_cycle);
}
void dd_normal_O_11111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[251](context, target_cycle);
}
void dd_normal_O_11111100(z80_context *context, uint32_t target_cycle)
{
	impl_main[252](context, target_cycle);
}
void dd_normal_O_11111101(z80_context *context, uint32_t target_cycle)
{
	impl_main[253](context, target_cycle);
}
void dd_normal_O_11111110(z80_context *context, uint32_t target_cycle)
{
	impl_main[254](context, target_cycle);
}
void dd_normal_O_11111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[255](context, target_cycle);
}
static impl_fun impl_dd[256] = {
	dd_normal_O_00000000,
	dd_normal_O_00000001,
	dd_normal_O_00000010,
	dd_normal_O_00000011,
	dd_normal_O_00000100,
	dd_normal_O_00000101,
	dd_normal_O_00000110,
	dd_normal_O_00000111,
	dd_normal_O_00001000,
	add_ix_bc,
	dd_normal_O_00001010,
	dd_normal_O_00001011,
	dd_normal_O_00001100,
	dd_normal_O_00001101,
	dd_normal_O_00001110,
	dd_normal_O_00001111,
	dd_normal_O_00010000,
	dd_normal_O_00010001,
	dd_normal_O_00010010,
	dd_normal_O_00010011,
	dd_normal_O_00010100,
	dd_normal_O_00010101,
	dd_normal_O_00010110,
	dd_normal_O_00010111,
	dd_normal_O_00011000,
	add_ix_de,
	dd_normal_O_00011010,
	dd_normal_O_00011011,
	dd_normal_O_00011100,
	dd_normal_O_00011101,
	dd_normal_O_00011110,
	dd_normal_O_00011111,
	dd_normal_O_00100000,
	ld_ix_immed,
	ld_ix_to_immed,
	inc_ix,
	inc_ixh,
	dec_ixh,
	ld_immed_ixh,
	dd_normal_O_00100111,
	dd_normal_O_00101000,
	add_ix_ix,
	ld_ix_from_immed,
	dec_ix,
	inc_ixl,
	dec_ixl,
	ld_immed_ixl,
	dd_normal_O_00101111,
	dd_normal_O_00110000,
	dd_normal_O_00110001,
	dd_normal_O_00110010,
	dd_normal_O_00110011,
	inc_ixd,
	dec_ixd,
	ld_to_ixd_immed,
	dd_normal_O_00110111,
	dd_normal_O_00111000,
	add_ix_sp,
	dd_normal_O_00111010,
	dd_normal_O_00111011,
	dd_normal_O_00111100,
	dd_normal_O_00111101,
	dd_normal_O_00111110,
	dd_normal_O_00111111,
	dd_normal_O_01000000,
	dd_normal_O_01000001,
	dd_normal_O_01000010,
	dd_normal_O_01000011,
	ld_from_ixh_D_000,
	ld_from_ixl_D_000,
	ld_from_ix_R_000,
	dd_normal_O_01000111,
	dd_normal_O_01001000,
	dd_normal_O_01001001,
	dd_normal_O_01001010,
	dd_normal_O_01001011,
	ld_from_ixh_D_001,
	ld_from_ixl_D_001,
	ld_from_ix_R_001,
	dd_normal_O_01001111,
	dd_normal_O_01010000,
	dd_normal_O_01010001,
	dd_normal_O_01010010,
	dd_normal_O_01010011,
	ld_from_ixh_D_010,
	ld_from_ixl_D_010,
	ld_from_ix_R_010,
	dd_normal_O_01010111,
	dd_normal_O_01011000,
	dd_normal_O_01011001,
	dd_normal_O_01011010,
	dd_normal_O_01011011,
	ld_from_ixh_D_011,
	ld_from_ixl_D_011,
	ld_from_ix_R_011,
	dd_normal_O_01011111,
	ld_to_ixh_S_000,
	ld_to_ixh_S_001,
	ld_to_ixh_S_010,
	ld_to_ixh_S_011,
	ld_ixb_to_ixb_D_0_S_0,
	ld_ixl_to_ixh,
	ld_from_ix_R_100,
	ld_to_ixh_S_111,
	ld_to_ixl_S_000,
	ld_to_ixl_S_001,
	ld_to_ixl_S_010,
	ld_to_ixl_S_011,
	ld_ixh_to_ixl,
	ld_ixb_to_ixb_D_1_S_1,
	ld_from_ix_R_101,
	ld_to_ixl_S_111,
	ld_to_ix_R_000,
	ld_to_ix_R_001,
	ld_to_ix_R_010,
	ld_to_ix_R_011,
	ld_to_ix_R_100,
	ld_to_ix_R_101,
	ld_from_ix_R_110,
	ld_to_ix_R_111,
	dd_normal_O_01111000,
	dd_normal_O_01111001,
	dd_normal_O_01111010,
	dd_normal_O_01111011,
	ld_from_ixh_D_111,
	ld_from_ixl_D_111,
	ld_from_ix_R_111,
	dd_normal_O_01111111,
	dd_normal_O_10000000,
	dd_normal_O_10000001,
	dd_normal_O_10000010,
	dd_normal_O_10000011,
	add_ixh,
	add_ixl,
	add_ixd,
	dd_normal_O_10000111,
	dd_normal_O_10001000,
	dd_normal_O_10001001,
	dd_normal_O_10001010,
	dd_normal_O_10001011,
	adc_ixh,
	adc_ixl,
	adc_ixd,
	dd_normal_O_10001111,
	dd_normal_O_10010000,
	dd_normal_O_10010001,
	dd_normal_O_10010010,
	dd_normal_O_10010011,
	sub_ixh,
	sub_ixl,
	sub_ixd,
	dd_normal_O_10010111,
	dd_normal_O_10011000,
	dd_normal_O_10011001,
	dd_normal_O_10011010,
	dd_normal_O_10011011,
	sbc_ixh,
	sbc_ixl,
	sbc_ixd,
	dd_normal_O_10011111,
	dd_normal_O_10100000,
	dd_normal_O_10100001,
	dd_normal_O_10100010,
	dd_normal_O_10100011,
	and_ixh,
	and_ixl,
	and_ixd,
	dd_normal_O_10100111,
	dd_normal_O_10101000,
	dd_normal_O_10101001,
	dd_normal_O_10101010,
	dd_normal_O_10101011,
	xor_ixh,
	xor_ixl,
	xor_ixd,
	dd_normal_O_10101111,
	dd_normal_O_10110000,
	dd_normal_O_10110001,
	dd_normal_O_10110010,
	dd_normal_O_10110011,
	or_ixh,
	or_ixl,
	or_ixd,
	dd_normal_O_10110111,
	dd_normal_O_10111000,
	dd_normal_O_10111001,
	dd_normal_O_10111010,
	dd_normal_O_10111011,
	cp_ixh,
	cp_ixl,
	cp_ixd,
	dd_normal_O_10111111,
	dd_normal_O_11000000,
	dd_normal_O_11000001,
	dd_normal_O_11000010,
	dd_normal_O_11000011,
	dd_normal_O_11000100,
	dd_normal_O_11000101,
	dd_normal_O_11000110,
	dd_normal_O_11000111,
	dd_normal_O_11001000,
	dd_normal_O_11001001,
	dd_normal_O_11001010,
	ddcb_prefix,
	dd_normal_O_11001100,
	dd_normal_O_11001101,
	dd_normal_O_11001110,
	dd_normal_O_11001111,
	dd_normal_O_11010000,
	dd_normal_O_11010001,
	dd_normal_O_11010010,
	dd_normal_O_11010011,
	dd_normal_O_11010100,
	dd_normal_O_11010101,
	dd_normal_O_11010110,
	dd_normal_O_11010111,
	dd_normal_O_11011000,
	dd_normal_O_11011001,
	dd_normal_O_11011010,
	dd_normal_O_11011011,
	dd_normal_O_11011100,
	dd_normal_O_11011101,
	dd_normal_O_11011110,
	dd_normal_O_11011111,
	dd_normal_O_11100000,
	pop_ix,
	dd_normal_O_11100010,
	ex_sp_ix,
	dd_normal_O_11100100,
	push_ix,
	dd_normal_O_11100110,
	dd_normal_O_11100111,
	dd_normal_O_11101000,
	jp_ix,
	dd_normal_O_11101010,
	dd_normal_O_11101011,
	dd_normal_O_11101100,
	dd_normal_O_11101101,
	dd_normal_O_11101110,
	dd_normal_O_11101111,
	dd_normal_O_11110000,
	dd_normal_O_11110001,
	dd_normal_O_11110010,
	dd_normal_O_11110011,
	dd_normal_O_11110100,
	dd_normal_O_11110101,
	dd_normal_O_11110110,
	dd_normal_O_11110111,
	dd_normal_O_11111000,
	ld_sp_ix,
	dd_normal_O_11111010,
	dd_normal_O_11111011,
	dd_normal_O_11111100,
	dd_normal_O_11111101,
	dd_normal_O_11111110,
	dd_normal_O_11111111,
};
void fd_normal_O_00000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[0](context, target_cycle);
}
void fd_normal_O_00000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[1](context, target_cycle);
}
void fd_normal_O_00000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[2](context, target_cycle);
}
void fd_normal_O_00000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[3](context, target_cycle);
}
void fd_normal_O_00000100(z80_context *context, uint32_t target_cycle)
{
	impl_main[4](context, target_cycle);
}
void fd_normal_O_00000101(z80_context *context, uint32_t target_cycle)
{
	impl_main[5](context, target_cycle);
}
void fd_normal_O_00000110(z80_context *context, uint32_t target_cycle)
{
	impl_main[6](context, target_cycle);
}
void fd_normal_O_00000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[7](context, target_cycle);
}
void fd_normal_O_00001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[8](context, target_cycle);
}
void add_iy_bc(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	context->scratch1 = context->main[0] << 8;
	context->scratch1 = context->main[1] | context->scratch1;
	gen_tmp32__ = context->scratch1 + context->iy;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->scratch1 ^ context->iy ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->iy = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void fd_normal_O_00001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[10](context, target_cycle);
}
void fd_normal_O_00001011(z80_context *context, uint32_t target_cycle)
{
	impl_main[11](context, target_cycle);
}
void fd_normal_O_00001100(z80_context *context, uint32_t target_cycle)
{
	impl_main[12](context, target_cycle);
}
void fd_normal_O_00001101(z80_context *context, uint32_t target_cycle)
{
	impl_main[13](context, target_cycle);
}
void fd_normal_O_00001110(z80_context *context, uint32_t target_cycle)
{
	impl_main[14](context, target_cycle);
}
void fd_normal_O_00001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[15](context, target_cycle);
}
void fd_normal_O_00010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[16](context, target_cycle);
}
void fd_normal_O_00010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[17](context, target_cycle);
}
void fd_normal_O_00010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[18](context, target_cycle);
}
void fd_normal_O_00010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[19](context, target_cycle);
}
void fd_normal_O_00010100(z80_context *context, uint32_t target_cycle)
{
	impl_main[20](context, target_cycle);
}
void fd_normal_O_00010101(z80_context *context, uint32_t target_cycle)
{
	impl_main[21](context, target_cycle);
}
void fd_normal_O_00010110(z80_context *context, uint32_t target_cycle)
{
	impl_main[22](context, target_cycle);
}
void fd_normal_O_00010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[23](context, target_cycle);
}
void fd_normal_O_00011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[24](context, target_cycle);
}
void add_iy_de(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	context->scratch1 = context->main[2] << 8;
	context->scratch1 = context->main[3] | context->scratch1;
	gen_tmp32__ = context->scratch1 + context->iy;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->scratch1 ^ context->iy ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->iy = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void fd_normal_O_00011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[26](context, target_cycle);
}
void fd_normal_O_00011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[27](context, target_cycle);
}
void fd_normal_O_00011100(z80_context *context, uint32_t target_cycle)
{
	impl_main[28](context, target_cycle);
}
void fd_normal_O_00011101(z80_context *context, uint32_t target_cycle)
{
	impl_main[29](context, target_cycle);
}
void fd_normal_O_00011110(z80_context *context, uint32_t target_cycle)
{
	impl_main[30](context, target_cycle);
}
void fd_normal_O_00011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[31](context, target_cycle);
}
void fd_normal_O_00100000(z80_context *context, uint32_t target_cycle)
{
	impl_main[32](context, target_cycle);
}
void ld_iy_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->iy = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->iy = context->scratch1 | context->iy;
}
void ld_iy_to_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->iy;
	z80_write_8(context);
	context->wz = 1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->iy >> 8;
	z80_write_8(context);
	context->wz = 1 + context->wz;
}
void inc_iy(z80_context *context, uint32_t target_cycle)
{
	context->iy = 1 + context->iy;
}
void inc_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = 256 + context->iy;
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp16__ >> 8U & 32U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp16__ >> 8U & 8U);
	context->pvflag = (((256 ^ (~context->iy))) & (256 ^ gen_tmp16__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp16__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((256 ^ context->iy ^ gen_tmp16__) >> 9U & 8U);
	context->zflag = (gen_tmp16__ & 65535) == 0;
	context->iy = gen_tmp16__;
	context->nflag = 0;
}
void dec_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->iy - 256;
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp16__ >> 8U & 32U);
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp16__ >> 8U & 8U);
	context->pvflag = (((context->iy ^ 256)) & (context->iy ^ gen_tmp16__)) >> 8 & 128U;
	context->last_flag_result = (context->last_flag_result & ~128U) | (gen_tmp16__ >> 8U & 128U);
	context->chflags = (context->chflags & ~8U) | ((context->iy ^ 256 ^ gen_tmp16__) >> 9U & 8U);
	context->zflag = (gen_tmp16__ & 65535) == 0;
	context->iy = gen_tmp16__;
	context->nflag = 1;
}
void ld_immed_iyh(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->iy = 255 & context->iy;
	context->iy = context->scratch1 | context->iy;
}
void fd_normal_O_00100111(z80_context *context, uint32_t target_cycle)
{
	impl_main[39](context, target_cycle);
}
void fd_normal_O_00101000(z80_context *context, uint32_t target_cycle)
{
	impl_main[40](context, target_cycle);
}
void add_iy_iy(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	gen_tmp32__ = context->iy + context->iy;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->iy ^ context->iy ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->iy = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_iy_from_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->iy = context->scratch1;
	context->wz = 1 + context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->scratch1 = context->scratch1 << 8;
	context->iy = context->scratch1 | context->iy;
	context->wz = 1 + context->wz;
}
void dec_iy(z80_context *context, uint32_t target_cycle)
{
	context->iy = context->iy - 1;
}
void inc_iyl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	tmp = context->iy;
	gen_tmp8__ = 1 + tmp;
	context->pvflag = (((1 ^ (~tmp))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ tmp ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 0;
	context->iy = 65280 & context->iy;
	context->iy = tmp | context->iy;
}
void dec_iyl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	tmp = context->iy;
	gen_tmp8__ = tmp - 1;
	context->pvflag = (((tmp ^ 1)) & (tmp ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((tmp ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 1;
	context->iy = 65280 & context->iy;
	context->iy = tmp | context->iy;
}
void ld_immed_iyl(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->iy = 65280 & context->iy;
	context->iy = context->scratch1 | context->iy;
}
void fd_normal_O_00101111(z80_context *context, uint32_t target_cycle)
{
	impl_main[47](context, target_cycle);
}
void fd_normal_O_00110000(z80_context *context, uint32_t target_cycle)
{
	impl_main[48](context, target_cycle);
}
void fd_normal_O_00110001(z80_context *context, uint32_t target_cycle)
{
	impl_main[49](context, target_cycle);
}
void fd_normal_O_00110010(z80_context *context, uint32_t target_cycle)
{
	impl_main[50](context, target_cycle);
}
void fd_normal_O_00110011(z80_context *context, uint32_t target_cycle)
{
	impl_main[51](context, target_cycle);
}
void inc_iyd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp8__ = 1 + tmp;
	context->pvflag = (((1 ^ (~tmp))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ tmp ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void dec_iyd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp8__ = tmp - 1;
	context->pvflag = (((tmp ^ 1)) & (tmp ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((tmp ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 1;
	context->scratch1 = tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void ld_to_iyd_immed(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 2;
	context->scratch2 = context->wz;
	z80_write_8(context);
}
void fd_normal_O_00110111(z80_context *context, uint32_t target_cycle)
{
	impl_main[55](context, target_cycle);
}
void fd_normal_O_00111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[56](context, target_cycle);
}
void add_iy_sp(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	gen_tmp32__ = context->sp + context->iy;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->sp ^ context->iy ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	context->iy = gen_tmp32__;
	context->nflag = 0;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void fd_normal_O_00111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[58](context, target_cycle);
}
void fd_normal_O_00111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[59](context, target_cycle);
}
void fd_normal_O_00111100(z80_context *context, uint32_t target_cycle)
{
	impl_main[60](context, target_cycle);
}
void fd_normal_O_00111101(z80_context *context, uint32_t target_cycle)
{
	impl_main[61](context, target_cycle);
}
void fd_normal_O_00111110(z80_context *context, uint32_t target_cycle)
{
	impl_main[62](context, target_cycle);
}
void fd_normal_O_00111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[63](context, target_cycle);
}
void fd_normal_O_01000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[64](context, target_cycle);
}
void fd_normal_O_01000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[65](context, target_cycle);
}
void fd_normal_O_01000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[66](context, target_cycle);
}
void fd_normal_O_01000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[67](context, target_cycle);
}
void ld_from_iyh_D_000(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->iy >> 8;
}
void ld_from_iyl_D_000(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->iy;
}
void ld_from_iy_R_000(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[0] = context->scratch1;
}
void fd_normal_O_01000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[71](context, target_cycle);
}
void fd_normal_O_01001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[72](context, target_cycle);
}
void fd_normal_O_01001001(z80_context *context, uint32_t target_cycle)
{
	impl_main[73](context, target_cycle);
}
void fd_normal_O_01001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[74](context, target_cycle);
}
void fd_normal_O_01001011(z80_context *context, uint32_t target_cycle)
{
	impl_main[75](context, target_cycle);
}
void ld_from_iyh_D_001(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->iy >> 8;
}
void ld_from_iyl_D_001(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->iy;
}
void ld_from_iy_R_001(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[1] = context->scratch1;
}
void fd_normal_O_01001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[79](context, target_cycle);
}
void fd_normal_O_01010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[80](context, target_cycle);
}
void fd_normal_O_01010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[81](context, target_cycle);
}
void fd_normal_O_01010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[82](context, target_cycle);
}
void fd_normal_O_01010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[83](context, target_cycle);
}
void ld_from_iyh_D_010(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->iy >> 8;
}
void ld_from_iyl_D_010(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->iy;
}
void ld_from_iy_R_010(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[2] = context->scratch1;
}
void fd_normal_O_01010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[87](context, target_cycle);
}
void fd_normal_O_01011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[88](context, target_cycle);
}
void fd_normal_O_01011001(z80_context *context, uint32_t target_cycle)
{
	impl_main[89](context, target_cycle);
}
void fd_normal_O_01011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[90](context, target_cycle);
}
void fd_normal_O_01011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[91](context, target_cycle);
}
void ld_from_iyh_D_011(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->iy >> 8;
}
void ld_from_iyl_D_011(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->iy;
}
void ld_from_iy_R_011(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[3] = context->scratch1;
}
void fd_normal_O_01011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[95](context, target_cycle);
}
void ld_to_iyh_S_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->iy = 255 & context->iy;
	tmp = context->main[0] << 8;
	context->iy = tmp | context->iy;
}
void ld_to_iyh_S_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->iy = 255 & context->iy;
	tmp = context->main[1] << 8;
	context->iy = tmp | context->iy;
}
void ld_to_iyh_S_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->iy = 255 & context->iy;
	tmp = context->main[2] << 8;
	context->iy = tmp | context->iy;
}
void ld_to_iyh_S_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->iy = 255 & context->iy;
	tmp = context->main[3] << 8;
	context->iy = tmp | context->iy;
}
void ld_iyb_to_iyb_D_0_S_0(z80_context *context, uint32_t target_cycle)
{
}
void ld_iyl_to_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	tmp = context->iy << 8;
	context->iy = 255 & context->iy;
	context->iy = tmp | context->iy;
}
void ld_from_iy_R_100(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[4] = context->scratch1;
}
void ld_to_iyh_S_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->iy = 255 & context->iy;
	tmp = context->main[7] << 8;
	context->iy = tmp | context->iy;
}
void ld_to_iyl_S_000(z80_context *context, uint32_t target_cycle)
{
	context->iy = 65280 & context->iy;
	context->iy = context->main[0] | context->iy;
}
void ld_to_iyl_S_001(z80_context *context, uint32_t target_cycle)
{
	context->iy = 65280 & context->iy;
	context->iy = context->main[1] | context->iy;
}
void ld_to_iyl_S_010(z80_context *context, uint32_t target_cycle)
{
	context->iy = 65280 & context->iy;
	context->iy = context->main[2] | context->iy;
}
void ld_to_iyl_S_011(z80_context *context, uint32_t target_cycle)
{
	context->iy = 65280 & context->iy;
	context->iy = context->main[3] | context->iy;
}
void ld_iyh_to_iyl(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	tmp = context->iy >> 8;
	context->iy = 65280 & context->iy;
	context->iy = tmp | context->iy;
}
void ld_iyb_to_iyb_D_1_S_1(z80_context *context, uint32_t target_cycle)
{
}
void ld_from_iy_R_101(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[5] = context->scratch1;
}
void ld_to_iyl_S_111(z80_context *context, uint32_t target_cycle)
{
	context->iy = 65280 & context->iy;
	context->iy = context->main[7] | context->iy;
}
void ld_to_iy_R_000(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[0];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_iy_R_001(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[1];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_iy_R_010(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[2];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_iy_R_011(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[3];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_iy_R_100(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[4];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_to_iy_R_101(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[5];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void ld_from_iy_R_110(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[6] = context->scratch1;
}
void ld_to_iy_R_111(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[7];
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_write_8(context);
}
void fd_normal_O_01111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[120](context, target_cycle);
}
void fd_normal_O_01111001(z80_context *context, uint32_t target_cycle)
{
	impl_main[121](context, target_cycle);
}
void fd_normal_O_01111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[122](context, target_cycle);
}
void fd_normal_O_01111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[123](context, target_cycle);
}
void ld_from_iyh_D_111(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->iy >> 8;
}
void ld_from_iyl_D_111(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->iy;
}
void ld_from_iy_R_111(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->scratch1;
}
void fd_normal_O_01111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[127](context, target_cycle);
}
void fd_normal_O_10000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[128](context, target_cycle);
}
void fd_normal_O_10000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[129](context, target_cycle);
}
void fd_normal_O_10000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[130](context, target_cycle);
}
void fd_normal_O_10000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[131](context, target_cycle);
}
void add_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy >> 8;
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_iyl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy & 255;
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void fd_normal_O_10000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[135](context, target_cycle);
}
void fd_normal_O_10001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[136](context, target_cycle);
}
void fd_normal_O_10001001(z80_context *context, uint32_t target_cycle)
{
	impl_main[137](context, target_cycle);
}
void fd_normal_O_10001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[138](context, target_cycle);
}
void fd_normal_O_10001011(z80_context *context, uint32_t target_cycle)
{
	impl_main[139](context, target_cycle);
}
void adc_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy >> 8;
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_iyl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy & 255;
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void fd_normal_O_10001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[143](context, target_cycle);
}
void fd_normal_O_10010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[144](context, target_cycle);
}
void fd_normal_O_10010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[145](context, target_cycle);
}
void fd_normal_O_10010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[146](context, target_cycle);
}
void fd_normal_O_10010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[147](context, target_cycle);
}
void sub_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy >> 8;
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_iyl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy & 255;
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void fd_normal_O_10010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[151](context, target_cycle);
}
void fd_normal_O_10011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[152](context, target_cycle);
}
void fd_normal_O_10011001(z80_context *context, uint32_t target_cycle)
{
	impl_main[153](context, target_cycle);
}
void fd_normal_O_10011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[154](context, target_cycle);
}
void fd_normal_O_10011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[155](context, target_cycle);
}
void sbc_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy >> 8;
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_iyl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->iy & 255;
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void fd_normal_O_10011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[159](context, target_cycle);
}
void fd_normal_O_10100000(z80_context *context, uint32_t target_cycle)
{
	impl_main[160](context, target_cycle);
}
void fd_normal_O_10100001(z80_context *context, uint32_t target_cycle)
{
	impl_main[161](context, target_cycle);
}
void fd_normal_O_10100010(z80_context *context, uint32_t target_cycle)
{
	impl_main[162](context, target_cycle);
}
void fd_normal_O_10100011(z80_context *context, uint32_t target_cycle)
{
	impl_main[163](context, target_cycle);
}
void and_iyh(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->iy >> 8;
	context->main[7] = context->scratch1 & context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_iyl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->iy & context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_iyd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->main[7] & context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void fd_normal_O_10100111(z80_context *context, uint32_t target_cycle)
{
	impl_main[167](context, target_cycle);
}
void fd_normal_O_10101000(z80_context *context, uint32_t target_cycle)
{
	impl_main[168](context, target_cycle);
}
void fd_normal_O_10101001(z80_context *context, uint32_t target_cycle)
{
	impl_main[169](context, target_cycle);
}
void fd_normal_O_10101010(z80_context *context, uint32_t target_cycle)
{
	impl_main[170](context, target_cycle);
}
void fd_normal_O_10101011(z80_context *context, uint32_t target_cycle)
{
	impl_main[171](context, target_cycle);
}
void xor_iyh(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->iy >> 8;
	context->main[7] = context->scratch1 ^ context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_iyl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->iy ^ context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_iyd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->main[7] ^ context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void fd_normal_O_10101111(z80_context *context, uint32_t target_cycle)
{
	impl_main[175](context, target_cycle);
}
void fd_normal_O_10110000(z80_context *context, uint32_t target_cycle)
{
	impl_main[176](context, target_cycle);
}
void fd_normal_O_10110001(z80_context *context, uint32_t target_cycle)
{
	impl_main[177](context, target_cycle);
}
void fd_normal_O_10110010(z80_context *context, uint32_t target_cycle)
{
	impl_main[178](context, target_cycle);
}
void fd_normal_O_10110011(z80_context *context, uint32_t target_cycle)
{
	impl_main[179](context, target_cycle);
}
void or_iyh(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->iy >> 8;
	context->main[7] = context->scratch1 | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_iyl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->iy | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_iyd(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	context->main[7] = context->main[7] | context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void fd_normal_O_10110111(z80_context *context, uint32_t target_cycle)
{
	impl_main[183](context, target_cycle);
}
void fd_normal_O_10111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[184](context, target_cycle);
}
void fd_normal_O_10111001(z80_context *context, uint32_t target_cycle)
{
	impl_main[185](context, target_cycle);
}
void fd_normal_O_10111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[186](context, target_cycle);
}
void fd_normal_O_10111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[187](context, target_cycle);
}
void cp_iyh(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	tmp = context->iy >> 8;
	context->last_flag_result = tmp;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_iyl(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	tmp = context->iy;
	context->last_flag_result = context->iy;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_iyd(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->scratch1 = context->wz;
	context->cycles += context->opts->gen.clock_divider * 5;
	z80_read_8(context);
	tmp = context->scratch1;
	context->last_flag_result = context->scratch1;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void fd_normal_O_10111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[191](context, target_cycle);
}
void fd_normal_O_11000000(z80_context *context, uint32_t target_cycle)
{
	impl_main[192](context, target_cycle);
}
void fd_normal_O_11000001(z80_context *context, uint32_t target_cycle)
{
	impl_main[193](context, target_cycle);
}
void fd_normal_O_11000010(z80_context *context, uint32_t target_cycle)
{
	impl_main[194](context, target_cycle);
}
void fd_normal_O_11000011(z80_context *context, uint32_t target_cycle)
{
	impl_main[195](context, target_cycle);
}
void fd_normal_O_11000100(z80_context *context, uint32_t target_cycle)
{
	impl_main[196](context, target_cycle);
}
void fd_normal_O_11000101(z80_context *context, uint32_t target_cycle)
{
	impl_main[197](context, target_cycle);
}
void fd_normal_O_11000110(z80_context *context, uint32_t target_cycle)
{
	impl_main[198](context, target_cycle);
}
void fd_normal_O_11000111(z80_context *context, uint32_t target_cycle)
{
	impl_main[199](context, target_cycle);
}
void fd_normal_O_11001000(z80_context *context, uint32_t target_cycle)
{
	impl_main[200](context, target_cycle);
}
void fd_normal_O_11001001(z80_context *context, uint32_t target_cycle)
{
	impl_main[201](context, target_cycle);
}
void fd_normal_O_11001010(z80_context *context, uint32_t target_cycle)
{
	impl_main[202](context, target_cycle);
}
void fdcb_prefix(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->iy;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->wz = context->scratch1 + context->wz;
	context->cycles += context->opts->gen.clock_divider * 2;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	impl_fdcb[context->scratch1](context, target_cycle);
}
void fd_normal_O_11001100(z80_context *context, uint32_t target_cycle)
{
	impl_main[204](context, target_cycle);
}
void fd_normal_O_11001101(z80_context *context, uint32_t target_cycle)
{
	impl_main[205](context, target_cycle);
}
void fd_normal_O_11001110(z80_context *context, uint32_t target_cycle)
{
	impl_main[206](context, target_cycle);
}
void fd_normal_O_11001111(z80_context *context, uint32_t target_cycle)
{
	impl_main[207](context, target_cycle);
}
void fd_normal_O_11010000(z80_context *context, uint32_t target_cycle)
{
	impl_main[208](context, target_cycle);
}
void fd_normal_O_11010001(z80_context *context, uint32_t target_cycle)
{
	impl_main[209](context, target_cycle);
}
void fd_normal_O_11010010(z80_context *context, uint32_t target_cycle)
{
	impl_main[210](context, target_cycle);
}
void fd_normal_O_11010011(z80_context *context, uint32_t target_cycle)
{
	impl_main[211](context, target_cycle);
}
void fd_normal_O_11010100(z80_context *context, uint32_t target_cycle)
{
	impl_main[212](context, target_cycle);
}
void fd_normal_O_11010101(z80_context *context, uint32_t target_cycle)
{
	impl_main[213](context, target_cycle);
}
void fd_normal_O_11010110(z80_context *context, uint32_t target_cycle)
{
	impl_main[214](context, target_cycle);
}
void fd_normal_O_11010111(z80_context *context, uint32_t target_cycle)
{
	impl_main[215](context, target_cycle);
}
void fd_normal_O_11011000(z80_context *context, uint32_t target_cycle)
{
	impl_main[216](context, target_cycle);
}
void fd_normal_O_11011001(z80_context *context, uint32_t target_cycle)
{
	impl_main[217](context, target_cycle);
}
void fd_normal_O_11011010(z80_context *context, uint32_t target_cycle)
{
	impl_main[218](context, target_cycle);
}
void fd_normal_O_11011011(z80_context *context, uint32_t target_cycle)
{
	impl_main[219](context, target_cycle);
}
void fd_normal_O_11011100(z80_context *context, uint32_t target_cycle)
{
	impl_main[220](context, target_cycle);
}
void fd_normal_O_11011101(z80_context *context, uint32_t target_cycle)
{
	impl_main[221](context, target_cycle);
}
void fd_normal_O_11011110(z80_context *context, uint32_t target_cycle)
{
	impl_main[222](context, target_cycle);
}
void fd_normal_O_11011111(z80_context *context, uint32_t target_cycle)
{
	impl_main[223](context, target_cycle);
}
void fd_normal_O_11100000(z80_context *context, uint32_t target_cycle)
{
	impl_main[224](context, target_cycle);
}
void pop_iy(z80_context *context, uint32_t target_cycle)
{
	uint16_t iyh;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->iy = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	iyh = context->scratch1;
	iyh = iyh << 8;
	context->iy = iyh | context->iy;
}
void fd_normal_O_11100010(z80_context *context, uint32_t target_cycle)
{
	impl_main[226](context, target_cycle);
}
void ex_sp_iy(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->scratch1 = context->iy;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->sp;
	z80_write_8(context);
	context->scratch1 = 1 + context->sp;
	z80_read_8(context);
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->iy >> 8;
	context->cycles += context->opts->gen.clock_divider * 2;
	context->scratch2 = 1 + context->sp;
	z80_write_8(context);
	context->iy = context->wz;
}
void fd_normal_O_11100100(z80_context *context, uint32_t target_cycle)
{
	impl_main[228](context, target_cycle);
}
void push_iy(z80_context *context, uint32_t target_cycle)
{
	uint8_t iyh;
	iyh = context->iy >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = iyh;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->iy;
	z80_write_8(context);
}
void fd_normal_O_11100110(z80_context *context, uint32_t target_cycle)
{
	impl_main[230](context, target_cycle);
}
void fd_normal_O_11100111(z80_context *context, uint32_t target_cycle)
{
	impl_main[231](context, target_cycle);
}
void fd_normal_O_11101000(z80_context *context, uint32_t target_cycle)
{
	impl_main[232](context, target_cycle);
}
void jp_iy(z80_context *context, uint32_t target_cycle)
{
	context->pc = context->iy;
}
void fd_normal_O_11101010(z80_context *context, uint32_t target_cycle)
{
	impl_main[234](context, target_cycle);
}
void fd_normal_O_11101011(z80_context *context, uint32_t target_cycle)
{
	impl_main[235](context, target_cycle);
}
void fd_normal_O_11101100(z80_context *context, uint32_t target_cycle)
{
	impl_main[236](context, target_cycle);
}
void fd_normal_O_11101101(z80_context *context, uint32_t target_cycle)
{
	impl_main[237](context, target_cycle);
}
void fd_normal_O_11101110(z80_context *context, uint32_t target_cycle)
{
	impl_main[238](context, target_cycle);
}
void fd_normal_O_11101111(z80_context *context, uint32_t target_cycle)
{
	impl_main[239](context, target_cycle);
}
void fd_normal_O_11110000(z80_context *context, uint32_t target_cycle)
{
	impl_main[240](context, target_cycle);
}
void fd_normal_O_11110001(z80_context *context, uint32_t target_cycle)
{
	impl_main[241](context, target_cycle);
}
void fd_normal_O_11110010(z80_context *context, uint32_t target_cycle)
{
	impl_main[242](context, target_cycle);
}
void fd_normal_O_11110011(z80_context *context, uint32_t target_cycle)
{
	impl_main[243](context, target_cycle);
}
void fd_normal_O_11110100(z80_context *context, uint32_t target_cycle)
{
	impl_main[244](context, target_cycle);
}
void fd_normal_O_11110101(z80_context *context, uint32_t target_cycle)
{
	impl_main[245](context, target_cycle);
}
void fd_normal_O_11110110(z80_context *context, uint32_t target_cycle)
{
	impl_main[246](context, target_cycle);
}
void fd_normal_O_11110111(z80_context *context, uint32_t target_cycle)
{
	impl_main[247](context, target_cycle);
}
void fd_normal_O_11111000(z80_context *context, uint32_t target_cycle)
{
	impl_main[248](context, target_cycle);
}
void ld_sp_iy(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 2;
	context->sp = context->iy;
}
void fd_normal_O_11111010(z80_context *context, uint32_t target_cycle)
{
	impl_main[250](context, target_cycle);
}
void fd_normal_O_11111011(z80_context *context, uint32_t target_cycle)
{
	impl_main[251](context, target_cycle);
}
void fd_normal_O_11111100(z80_context *context, uint32_t target_cycle)
{
	impl_main[252](context, target_cycle);
}
void fd_normal_O_11111101(z80_context *context, uint32_t target_cycle)
{
	impl_main[253](context, target_cycle);
}
void fd_normal_O_11111110(z80_context *context, uint32_t target_cycle)
{
	impl_main[254](context, target_cycle);
}
void fd_normal_O_11111111(z80_context *context, uint32_t target_cycle)
{
	impl_main[255](context, target_cycle);
}
static impl_fun impl_fd[256] = {
	fd_normal_O_00000000,
	fd_normal_O_00000001,
	fd_normal_O_00000010,
	fd_normal_O_00000011,
	fd_normal_O_00000100,
	fd_normal_O_00000101,
	fd_normal_O_00000110,
	fd_normal_O_00000111,
	fd_normal_O_00001000,
	add_iy_bc,
	fd_normal_O_00001010,
	fd_normal_O_00001011,
	fd_normal_O_00001100,
	fd_normal_O_00001101,
	fd_normal_O_00001110,
	fd_normal_O_00001111,
	fd_normal_O_00010000,
	fd_normal_O_00010001,
	fd_normal_O_00010010,
	fd_normal_O_00010011,
	fd_normal_O_00010100,
	fd_normal_O_00010101,
	fd_normal_O_00010110,
	fd_normal_O_00010111,
	fd_normal_O_00011000,
	add_iy_de,
	fd_normal_O_00011010,
	fd_normal_O_00011011,
	fd_normal_O_00011100,
	fd_normal_O_00011101,
	fd_normal_O_00011110,
	fd_normal_O_00011111,
	fd_normal_O_00100000,
	ld_iy_immed,
	ld_iy_to_immed,
	inc_iy,
	inc_iyh,
	dec_iyh,
	ld_immed_iyh,
	fd_normal_O_00100111,
	fd_normal_O_00101000,
	add_iy_iy,
	ld_iy_from_immed,
	dec_iy,
	inc_iyl,
	dec_iyl,
	ld_immed_iyl,
	fd_normal_O_00101111,
	fd_normal_O_00110000,
	fd_normal_O_00110001,
	fd_normal_O_00110010,
	fd_normal_O_00110011,
	inc_iyd,
	dec_iyd,
	ld_to_iyd_immed,
	fd_normal_O_00110111,
	fd_normal_O_00111000,
	add_iy_sp,
	fd_normal_O_00111010,
	fd_normal_O_00111011,
	fd_normal_O_00111100,
	fd_normal_O_00111101,
	fd_normal_O_00111110,
	fd_normal_O_00111111,
	fd_normal_O_01000000,
	fd_normal_O_01000001,
	fd_normal_O_01000010,
	fd_normal_O_01000011,
	ld_from_iyh_D_000,
	ld_from_iyl_D_000,
	ld_from_iy_R_000,
	fd_normal_O_01000111,
	fd_normal_O_01001000,
	fd_normal_O_01001001,
	fd_normal_O_01001010,
	fd_normal_O_01001011,
	ld_from_iyh_D_001,
	ld_from_iyl_D_001,
	ld_from_iy_R_001,
	fd_normal_O_01001111,
	fd_normal_O_01010000,
	fd_normal_O_01010001,
	fd_normal_O_01010010,
	fd_normal_O_01010011,
	ld_from_iyh_D_010,
	ld_from_iyl_D_010,
	ld_from_iy_R_010,
	fd_normal_O_01010111,
	fd_normal_O_01011000,
	fd_normal_O_01011001,
	fd_normal_O_01011010,
	fd_normal_O_01011011,
	ld_from_iyh_D_011,
	ld_from_iyl_D_011,
	ld_from_iy_R_011,
	fd_normal_O_01011111,
	ld_to_iyh_S_000,
	ld_to_iyh_S_001,
	ld_to_iyh_S_010,
	ld_to_iyh_S_011,
	ld_iyb_to_iyb_D_0_S_0,
	ld_iyl_to_iyh,
	ld_from_iy_R_100,
	ld_to_iyh_S_111,
	ld_to_iyl_S_000,
	ld_to_iyl_S_001,
	ld_to_iyl_S_010,
	ld_to_iyl_S_011,
	ld_iyh_to_iyl,
	ld_iyb_to_iyb_D_1_S_1,
	ld_from_iy_R_101,
	ld_to_iyl_S_111,
	ld_to_iy_R_000,
	ld_to_iy_R_001,
	ld_to_iy_R_010,
	ld_to_iy_R_011,
	ld_to_iy_R_100,
	ld_to_iy_R_101,
	ld_from_iy_R_110,
	ld_to_iy_R_111,
	fd_normal_O_01111000,
	fd_normal_O_01111001,
	fd_normal_O_01111010,
	fd_normal_O_01111011,
	ld_from_iyh_D_111,
	ld_from_iyl_D_111,
	ld_from_iy_R_111,
	fd_normal_O_01111111,
	fd_normal_O_10000000,
	fd_normal_O_10000001,
	fd_normal_O_10000010,
	fd_normal_O_10000011,
	add_iyh,
	add_iyl,
	add_iyd,
	fd_normal_O_10000111,
	fd_normal_O_10001000,
	fd_normal_O_10001001,
	fd_normal_O_10001010,
	fd_normal_O_10001011,
	adc_iyh,
	adc_iyl,
	adc_iyd,
	fd_normal_O_10001111,
	fd_normal_O_10010000,
	fd_normal_O_10010001,
	fd_normal_O_10010010,
	fd_normal_O_10010011,
	sub_iyh,
	sub_iyl,
	sub_iyd,
	fd_normal_O_10010111,
	fd_normal_O_10011000,
	fd_normal_O_10011001,
	fd_normal_O_10011010,
	fd_normal_O_10011011,
	sbc_iyh,
	sbc_iyl,
	sbc_iyd,
	fd_normal_O_10011111,
	fd_normal_O_10100000,
	fd_normal_O_10100001,
	fd_normal_O_10100010,
	fd_normal_O_10100011,
	and_iyh,
	and_iyl,
	and_iyd,
	fd_normal_O_10100111,
	fd_normal_O_10101000,
	fd_normal_O_10101001,
	fd_normal_O_10101010,
	fd_normal_O_10101011,
	xor_iyh,
	xor_iyl,
	xor_iyd,
	fd_normal_O_10101111,
	fd_normal_O_10110000,
	fd_normal_O_10110001,
	fd_normal_O_10110010,
	fd_normal_O_10110011,
	or_iyh,
	or_iyl,
	or_iyd,
	fd_normal_O_10110111,
	fd_normal_O_10111000,
	fd_normal_O_10111001,
	fd_normal_O_10111010,
	fd_normal_O_10111011,
	cp_iyh,
	cp_iyl,
	cp_iyd,
	fd_normal_O_10111111,
	fd_normal_O_11000000,
	fd_normal_O_11000001,
	fd_normal_O_11000010,
	fd_normal_O_11000011,
	fd_normal_O_11000100,
	fd_normal_O_11000101,
	fd_normal_O_11000110,
	fd_normal_O_11000111,
	fd_normal_O_11001000,
	fd_normal_O_11001001,
	fd_normal_O_11001010,
	fdcb_prefix,
	fd_normal_O_11001100,
	fd_normal_O_11001101,
	fd_normal_O_11001110,
	fd_normal_O_11001111,
	fd_normal_O_11010000,
	fd_normal_O_11010001,
	fd_normal_O_11010010,
	fd_normal_O_11010011,
	fd_normal_O_11010100,
	fd_normal_O_11010101,
	fd_normal_O_11010110,
	fd_normal_O_11010111,
	fd_normal_O_11011000,
	fd_normal_O_11011001,
	fd_normal_O_11011010,
	fd_normal_O_11011011,
	fd_normal_O_11011100,
	fd_normal_O_11011101,
	fd_normal_O_11011110,
	fd_normal_O_11011111,
	fd_normal_O_11100000,
	pop_iy,
	fd_normal_O_11100010,
	ex_sp_iy,
	fd_normal_O_11100100,
	push_iy,
	fd_normal_O_11100110,
	fd_normal_O_11100111,
	fd_normal_O_11101000,
	jp_iy,
	fd_normal_O_11101010,
	fd_normal_O_11101011,
	fd_normal_O_11101100,
	fd_normal_O_11101101,
	fd_normal_O_11101110,
	fd_normal_O_11101111,
	fd_normal_O_11110000,
	fd_normal_O_11110001,
	fd_normal_O_11110010,
	fd_normal_O_11110011,
	fd_normal_O_11110100,
	fd_normal_O_11110101,
	fd_normal_O_11110110,
	fd_normal_O_11110111,
	fd_normal_O_11111000,
	ld_sp_iy,
	fd_normal_O_11111010,
	fd_normal_O_11111011,
	fd_normal_O_11111100,
	fd_normal_O_11111101,
	fd_normal_O_11111110,
	fd_normal_O_11111111,
};
void nop(z80_context *context, uint32_t target_cycle)
{
}
void ld_bc_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->main[1] = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->main[0] = context->scratch1;
	context->pc = 1 + context->pc;
}
void ld_a_to_bc(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch2 = context->main[0] << 8;
	context->scratch2 = context->main[1] | context->scratch2;
	context->scratch1 = context->main[7];
	tmp = context->main[1] + 1;
	context->wz = context->main[7] << 8;
	context->wz = tmp | context->wz;
	z80_write_8(context);
}
void inc_bc(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_inc_pair_word;
	context->cycles += context->opts->gen.clock_divider * 2;
	z80_inc_pair_word = context->main[0] << 8;
	z80_inc_pair_word = context->main[1] | z80_inc_pair_word;
	z80_inc_pair_word = 1 + z80_inc_pair_word;
	context->main[1] = z80_inc_pair_word;
	context->main[0] = z80_inc_pair_word >> 8;
}
void inc_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = 1 + context->main[0];
	context->pvflag = (((1 ^ (~context->main[0]))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ context->main[0] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[0] = gen_tmp8__;
	context->nflag = 0;
}
void dec_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[0] - 1;
	context->pvflag = (((context->main[0] ^ 1)) & (context->main[0] ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[0] ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[0] = gen_tmp8__;
	context->nflag = 1;
}
void ld_immed_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[0] = context->scratch1;
}
void rlca(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = (context->last_flag_result & ~40U) | (gen_tmp16__ & 40U);
	context->main[7] = gen_tmp16__;
	context->chflags &= ~8;
	context->nflag = 0;
}
void ex_af_af(z80_context *context, uint32_t target_cycle)
{
	context->main[6] = 0;
	if (context->zflag) {
		context->main[6] |= 1 << 6;
	}
	if (context->pvflag) {
		context->main[6] |= 1 << 2;
	}
	if (context->nflag) {
		context->main[6] |= 1 << 1;
	}
	context->main[6] |= context->last_flag_result & 168;
	if (context->chflags & (1 << 3)) {
		context->main[6] |= 1 << 4;
	}
	if (context->chflags & (1 << 7)) {
		context->main[6] |= 1 << 0;
	}
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[7];
	context->main[7] = context->alt[7];
	context->alt[7] = gen_tmp8__;
	gen_tmp8__ = context->main[6];
	context->main[6] = context->alt[6];
	context->alt[6] = gen_tmp8__;
	context->zflag = context->main[6] & 64;
	context->pvflag = context->main[6] & 4;
	context->nflag = context->main[6] & 2;
	context->last_flag_result = context->main[6];
	context->chflags = 0;
	context->chflags |= context->main[6] >> 1 & 8;
	context->chflags |= context->main[6] << 7 & 128;
}
void add_hl_bc(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	uint16_t bcw;
	bcw = context->main[0] << 8;
	bcw = context->main[1] | bcw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = bcw + hlw;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((bcw ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_a_from_bc(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->main[0] << 8;
	context->wz = context->main[1] | context->wz;
	context->scratch1 = context->wz;
	context->wz = 1 + context->wz;
	z80_read_8(context);
	context->main[7] = context->scratch1;
}
void dec_bc(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_dec_pair_word;
	z80_dec_pair_word = context->main[0] << 8;
	z80_dec_pair_word = context->main[1] | z80_dec_pair_word;
	z80_dec_pair_word = z80_dec_pair_word - 1;
	context->main[1] = z80_dec_pair_word;
	context->main[0] = z80_dec_pair_word >> 8;
	context->cycles += context->opts->gen.clock_divider * 2;
}
void inc_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = 1 + context->main[1];
	context->pvflag = (((1 ^ (~context->main[1]))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ context->main[1] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[1] = gen_tmp8__;
	context->nflag = 0;
}
void dec_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[1] - 1;
	context->pvflag = (((context->main[1] ^ 1)) & (context->main[1] ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[1] ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[1] = gen_tmp8__;
	context->nflag = 1;
}
void ld_immed_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[1] = context->scratch1;
}
void rrca(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[7] >> 1 | context->main[7] << (8 - 1);
	context->last_flag_result = (context->last_flag_result & ~40U) | (context->main[7] & 40U);
	context->chflags = (context->chflags & ~128U) | (context->main[7] & 128U);
	context->chflags &= ~8;
	context->nflag = 0;
}
void djnz(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[0] = context->main[0] - 1;
	if (context->main[0]) {
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->pc = context->scratch1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void ld_de_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->main[3] = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->main[2] = context->scratch1;
	context->pc = 1 + context->pc;
}
void ld_a_to_de(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->scratch2 = context->main[2] << 8;
	context->scratch2 = context->main[3] | context->scratch2;
	context->scratch1 = context->main[7];
	tmp = context->main[3] + 1;
	context->wz = context->main[7] << 8;
	context->wz = tmp | context->wz;
	z80_write_8(context);
}
void inc_de(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_inc_pair_word;
	context->cycles += context->opts->gen.clock_divider * 2;
	z80_inc_pair_word = context->main[2] << 8;
	z80_inc_pair_word = context->main[3] | z80_inc_pair_word;
	z80_inc_pair_word = 1 + z80_inc_pair_word;
	context->main[3] = z80_inc_pair_word;
	context->main[2] = z80_inc_pair_word >> 8;
}
void inc_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = 1 + context->main[2];
	context->pvflag = (((1 ^ (~context->main[2]))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ context->main[2] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[2] = gen_tmp8__;
	context->nflag = 0;
}
void dec_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[2] - 1;
	context->pvflag = (((context->main[2] ^ 1)) & (context->main[2] ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[2] ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[2] = gen_tmp8__;
	context->nflag = 1;
}
void ld_immed_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[2] = context->scratch1;
}
void rla(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] << 1 | context->main[7] >> (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (1 - 1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = (context->last_flag_result & ~40U) | (gen_tmp16__ & 40U);
	context->main[7] = gen_tmp16__;
	context->chflags &= ~8;
	context->nflag = 0;
}
void jr(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->pc = context->scratch1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 5;
}
void add_hl_de(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	uint16_t dew;
	dew = context->main[2] << 8;
	dew = context->main[3] | dew;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = dew + hlw;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((dew ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_a_from_de(z80_context *context, uint32_t target_cycle)
{
	context->wz = context->main[2] << 8;
	context->wz = context->main[3] | context->wz;
	context->scratch1 = context->wz;
	context->wz = 1 + context->wz;
	z80_read_8(context);
	context->main[7] = context->scratch1;
}
void dec_de(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_dec_pair_word;
	z80_dec_pair_word = context->main[2] << 8;
	z80_dec_pair_word = context->main[3] | z80_dec_pair_word;
	z80_dec_pair_word = z80_dec_pair_word - 1;
	context->main[3] = z80_dec_pair_word;
	context->main[2] = z80_dec_pair_word >> 8;
	context->cycles += context->opts->gen.clock_divider * 2;
}
void inc_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = 1 + context->main[3];
	context->pvflag = (((1 ^ (~context->main[3]))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ context->main[3] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[3] = gen_tmp8__;
	context->nflag = 0;
}
void dec_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[3] - 1;
	context->pvflag = (((context->main[3] ^ 1)) & (context->main[3] ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[3] ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[3] = gen_tmp8__;
	context->nflag = 1;
}
void ld_immed_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[3] = context->scratch1;
}
void rra(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] >> 1 | context->main[7] << (8 + 1 - 1) | ((context->chflags & 1 << 7) ? 1 : 0) << (8-1);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->last_flag_result = (context->last_flag_result & ~40U) | (gen_tmp16__ & 40U);
	context->main[7] = gen_tmp16__;
	context->chflags &= ~8;
	context->nflag = 0;
}
void jr_cc_C_00(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = !context->zflag;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	if (z80_check_cond_invert) {
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->pc = context->scratch1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void ld_hl_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->main[5] = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->main[4] = context->scratch1;
	context->pc = 1 + context->pc;
}
void ld_hl_to_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[5];
	z80_write_8(context);
	context->wz = 1 + context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[4];
	z80_write_8(context);
	context->wz = 1 + context->wz;
}
void inc16_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_inc_pair_word;
	context->cycles += context->opts->gen.clock_divider * 2;
	z80_inc_pair_word = context->main[4] << 8;
	z80_inc_pair_word = context->main[5] | z80_inc_pair_word;
	z80_inc_pair_word = 1 + z80_inc_pair_word;
	context->main[5] = z80_inc_pair_word;
	context->main[4] = z80_inc_pair_word >> 8;
}
void inc_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = 1 + context->main[4];
	context->pvflag = (((1 ^ (~context->main[4]))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ context->main[4] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[4] = gen_tmp8__;
	context->nflag = 0;
}
void dec_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[4] - 1;
	context->pvflag = (((context->main[4] ^ 1)) & (context->main[4] ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[4] ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[4] = gen_tmp8__;
	context->nflag = 1;
}
void ld_immed_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[4] = context->scratch1;
}
void daa(z80_context *context, uint32_t target_cycle)
{
	uint8_t cmp_tmp8__;
	uint8_t gen_tmp8__;
	uint8_t diff;
	uint8_t tmp;
	uint8_t low;
	low = 15 & context->main[7];
	tmp = 8 & context->chflags;
	if (tmp) {
	diff = 6;
	} else {
	if (low >= 10) {
	diff = 6;
	} else {
	diff = 0;
	}
	}
	tmp = 128 & context->chflags;
	if (tmp) {
	diff = 96 | diff;
	context->chflags |= 128;
	} else {
	if (context->main[7] >= 154) {
	diff = 96 | diff;
	context->chflags |= 128;
	} else {
	context->chflags &= ~128;
	}
	}
	if (context->nflag) {
	gen_tmp8__ = context->main[7] - diff;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ diff ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[7] = gen_tmp8__;
	gen_tmp8__ = (gen_tmp8__ ^ (gen_tmp8__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	} else {
	gen_tmp8__ = diff + context->main[7];
	context->chflags = (context->chflags & ~8U) | ((diff ^ context->main[7] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[7] = gen_tmp8__;
	gen_tmp8__ = (gen_tmp8__ ^ (gen_tmp8__ >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	}
}
void jr_cc_C_01(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	if (context->zflag) {
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->pc = context->scratch1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void add_hl_hl(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = hlw + hlw;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((hlw ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_hl_from_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[5] = context->scratch1;
	context->wz = 1 + context->wz;
	context->scratch1 = context->wz;
	z80_read_8(context);
	context->main[4] = context->scratch1;
	context->wz = 1 + context->wz;
}
void dec16_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t z80_dec_pair_word;
	z80_dec_pair_word = context->main[4] << 8;
	z80_dec_pair_word = context->main[5] | z80_dec_pair_word;
	z80_dec_pair_word = z80_dec_pair_word - 1;
	context->main[5] = z80_dec_pair_word;
	context->main[4] = z80_dec_pair_word >> 8;
	context->cycles += context->opts->gen.clock_divider * 2;
}
void inc_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = 1 + context->main[5];
	context->pvflag = (((1 ^ (~context->main[5]))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ context->main[5] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[5] = gen_tmp8__;
	context->nflag = 0;
}
void dec_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[5] - 1;
	context->pvflag = (((context->main[5] ^ 1)) & (context->main[5] ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[5] ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[5] = gen_tmp8__;
	context->nflag = 1;
}
void ld_immed_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[5] = context->scratch1;
}
void cpl(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = ~context->main[7];
	context->last_flag_result = (context->last_flag_result & ~40U) | (context->main[7] & 40U);
	context->chflags |= 8;
	context->nflag = 1;
}
void jr_cc_C_10(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = ~context->chflags;
	z80_check_cond_invert = 128 & z80_check_cond_invert;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	if (z80_check_cond_invert) {
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->pc = context->scratch1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void ld_sp_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->sp = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->sp = context->scratch1 | context->sp;
}
void ld_a_to_immed(z80_context *context, uint32_t target_cycle)
{
	uint16_t tmp;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch2 = context->wz;
	context->scratch1 = context->main[7];
	context->wz = 1 + context->wz;
	z80_write_8(context);
	context->wz = 255 & context->wz;
	tmp = context->main[7] << 8;
	context->wz = tmp | context->wz;
}
void inc_sp(z80_context *context, uint32_t target_cycle)
{
	context->sp = 1 + context->sp;
}
void inc_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp8__ = 1 + tmp;
	context->pvflag = (((1 ^ (~tmp))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ tmp ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 0;
	context->scratch1 = tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void dec_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	gen_tmp8__ = tmp - 1;
	context->pvflag = (((tmp ^ 1)) & (tmp ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((tmp ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	tmp = gen_tmp8__;
	context->nflag = 1;
	context->scratch1 = tmp;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void ld_to_hl_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void scf(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->last_flag_result = 128 & context->last_flag_result;
	tmp = 127 & context->main[7];
	context->last_flag_result = tmp | context->last_flag_result;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags |= 128;
}
void jr_cc_C_11(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = 128 & context->chflags;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	if (z80_check_cond_invert) {
	context->scratch1 = context->scratch1 & 0x80 ? context->scratch1 | 0xFF00 : context->scratch1 & 0x7F;
	context->pc = context->scratch1 + context->pc;
	context->cycles += context->opts->gen.clock_divider * 5;
	}
}
void add_hl_sp(z80_context *context, uint32_t target_cycle)
{
	uint32_t gen_tmp32__;
	uint16_t hlw;
	hlw = context->main[4] << 8;
	hlw = context->main[5] | hlw;
	context->wz = 1 + hlw;
	gen_tmp32__ = context->sp + hlw;
	context->last_flag_result = (context->last_flag_result & ~8U) | (gen_tmp32__ >> 8U & 8U);
	context->chflags = (context->chflags & ~8U) | ((context->sp ^ hlw ^ gen_tmp32__) >> 9U & 8U);
	context->last_flag_result = (context->last_flag_result & ~32U) | (gen_tmp32__ >> 8U & 32U);
	context->chflags = (context->chflags & ~128U) | (gen_tmp32__ >> 9U & 128U);
	hlw = gen_tmp32__;
	context->nflag = 0;
	context->main[5] = hlw;
	context->main[4] = hlw >> 8;
	context->cycles += context->opts->gen.clock_divider * 7;
}
void ld_a_from_immed(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->scratch1 = context->wz;
	context->wz = 1 + context->wz;
	z80_read_8(context);
	context->main[7] = context->scratch1;
}
void dec_sp(z80_context *context, uint32_t target_cycle)
{
	context->sp = context->sp - 1;
}
void inc_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = 1 + context->main[7];
	context->pvflag = (((1 ^ (~context->main[7]))) & (1 ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((1 ^ context->main[7] ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[7] = gen_tmp8__;
	context->nflag = 0;
}
void dec_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[7] - 1;
	context->pvflag = (((context->main[7] ^ 1)) & (context->main[7] ^ gen_tmp8__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ 1 ^ gen_tmp8__) >> 1U & 8U);
	context->zflag = (gen_tmp8__ & 255) == 0;
	context->last_flag_result = gen_tmp8__;
	context->main[7] = gen_tmp8__;
	context->nflag = 1;
}
void ld_immed_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[7] = context->scratch1;
}
void ccf(z80_context *context, uint32_t target_cycle)
{
	uint8_t tmp;
	context->last_flag_result = 128 & context->last_flag_result;
	tmp = 127 & context->main[7];
	context->last_flag_result = tmp | context->last_flag_result;
	context->chflags = 128 & context->chflags;
	tmp = context->chflags >> 4;
	context->chflags = tmp | context->chflags;
	context->chflags = 128 ^ context->chflags;
	context->nflag = 0;
}
void ld_from_reg_D_000_S_000(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->main[0];
}
void ld_from_reg_D_000_S_001(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->main[1];
}
void ld_from_reg_D_000_S_010(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->main[2];
}
void ld_from_reg_D_000_S_011(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->main[3];
}
void ld_from_reg_D_000_S_100(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->main[4];
}
void ld_from_reg_D_000_S_101(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->main[5];
}
void ld_from_hl_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[0] = context->scratch1;
}
void ld_from_reg_D_000_S_111(z80_context *context, uint32_t target_cycle)
{
	context->main[0] = context->main[7];
}
void ld_from_reg_D_001_S_000(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->main[0];
}
void ld_from_reg_D_001_S_001(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->main[1];
}
void ld_from_reg_D_001_S_010(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->main[2];
}
void ld_from_reg_D_001_S_011(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->main[3];
}
void ld_from_reg_D_001_S_100(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->main[4];
}
void ld_from_reg_D_001_S_101(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->main[5];
}
void ld_from_hl_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[1] = context->scratch1;
}
void ld_from_reg_D_001_S_111(z80_context *context, uint32_t target_cycle)
{
	context->main[1] = context->main[7];
}
void ld_from_reg_D_010_S_000(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->main[0];
}
void ld_from_reg_D_010_S_001(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->main[1];
}
void ld_from_reg_D_010_S_010(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->main[2];
}
void ld_from_reg_D_010_S_011(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->main[3];
}
void ld_from_reg_D_010_S_100(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->main[4];
}
void ld_from_reg_D_010_S_101(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->main[5];
}
void ld_from_hl_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[2] = context->scratch1;
}
void ld_from_reg_D_010_S_111(z80_context *context, uint32_t target_cycle)
{
	context->main[2] = context->main[7];
}
void ld_from_reg_D_011_S_000(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->main[0];
}
void ld_from_reg_D_011_S_001(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->main[1];
}
void ld_from_reg_D_011_S_010(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->main[2];
}
void ld_from_reg_D_011_S_011(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->main[3];
}
void ld_from_reg_D_011_S_100(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->main[4];
}
void ld_from_reg_D_011_S_101(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->main[5];
}
void ld_from_hl_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[3] = context->scratch1;
}
void ld_from_reg_D_011_S_111(z80_context *context, uint32_t target_cycle)
{
	context->main[3] = context->main[7];
}
void ld_from_reg_D_100_S_000(z80_context *context, uint32_t target_cycle)
{
	context->main[4] = context->main[0];
}
void ld_from_reg_D_100_S_001(z80_context *context, uint32_t target_cycle)
{
	context->main[4] = context->main[1];
}
void ld_from_reg_D_100_S_010(z80_context *context, uint32_t target_cycle)
{
	context->main[4] = context->main[2];
}
void ld_from_reg_D_100_S_011(z80_context *context, uint32_t target_cycle)
{
	context->main[4] = context->main[3];
}
void ld_from_reg_D_100_S_100(z80_context *context, uint32_t target_cycle)
{
	context->main[4] = context->main[4];
}
void ld_from_reg_D_100_S_101(z80_context *context, uint32_t target_cycle)
{
	context->main[4] = context->main[5];
}
void ld_from_hl_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[4] = context->scratch1;
}
void ld_from_reg_D_100_S_111(z80_context *context, uint32_t target_cycle)
{
	context->main[4] = context->main[7];
}
void ld_from_reg_D_101_S_000(z80_context *context, uint32_t target_cycle)
{
	context->main[5] = context->main[0];
}
void ld_from_reg_D_101_S_001(z80_context *context, uint32_t target_cycle)
{
	context->main[5] = context->main[1];
}
void ld_from_reg_D_101_S_010(z80_context *context, uint32_t target_cycle)
{
	context->main[5] = context->main[2];
}
void ld_from_reg_D_101_S_011(z80_context *context, uint32_t target_cycle)
{
	context->main[5] = context->main[3];
}
void ld_from_reg_D_101_S_100(z80_context *context, uint32_t target_cycle)
{
	context->main[5] = context->main[4];
}
void ld_from_reg_D_101_S_101(z80_context *context, uint32_t target_cycle)
{
	context->main[5] = context->main[5];
}
void ld_from_hl_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[5] = context->scratch1;
}
void ld_from_reg_D_101_S_111(z80_context *context, uint32_t target_cycle)
{
	context->main[5] = context->main[7];
}
void ld_to_hl_R_000(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[0];
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void ld_to_hl_R_001(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[1];
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void ld_to_hl_R_010(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[2];
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void ld_to_hl_R_011(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[3];
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void ld_to_hl_R_100(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4];
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void ld_to_hl_R_101(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[5];
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void halt(z80_context *context, uint32_t target_cycle)
{
	uint32_t cmp_tmp32__;
	if (context->cycles >= context->nmi_cycle) {
	} else {
	if (context->cycles >= context->int_cycle) {
	if (context->iff1) {
	} else {
	context->pc = context->pc - 1;
	}
	} else {
	context->pc = context->pc - 1;
	}
	}
}
void ld_to_hl_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[7];
	context->scratch2 = context->main[4] << 8;
	context->scratch2 = context->main[5] | context->scratch2;
	z80_write_8(context);
}
void ld_from_reg_D_111_S_000(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[0];
}
void ld_from_reg_D_111_S_001(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[1];
}
void ld_from_reg_D_111_S_010(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[2];
}
void ld_from_reg_D_111_S_011(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[3];
}
void ld_from_reg_D_111_S_100(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[4];
}
void ld_from_reg_D_111_S_101(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[5];
}
void ld_from_hl_R_111(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[7] = context->scratch1;
}
void ld_from_reg_D_111_S_111(z80_context *context, uint32_t target_cycle)
{
	context->main[7] = context->main[7];
}
void add_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[0];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[0]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[0] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[1];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[1]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[1] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[2];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[2]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[2] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[3];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[3]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[3] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[4];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[4]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[4] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[5];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[5]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[5] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void add_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[7]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[0] + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[0]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[0] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[1] + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[1]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[1] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[2] + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[2]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[2] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[3] + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[3]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[3] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[4] + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[4]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[4] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[5] + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[5]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[5] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void adc_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] + context->main[7] + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->main[7]))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void sub_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[0];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[0])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[0] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[1];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[1])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[1] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[2];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[2])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[2] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[3];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[3])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[3] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[4];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[4])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[4] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[5];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[5])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[5] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sub_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[7];
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[7])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[0] - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[0])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[0] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[1] - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[1])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[1] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[2] - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[2])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[2] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[3] - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[3])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[3] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[4] - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[4])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[4] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[5] - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[5])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[5] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void sbc_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	gen_tmp16__ = context->main[7] - context->main[7] - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[7])) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[7] ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void and_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] & context->main[0];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] & context->main[1];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] & context->main[2];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] & context->main[3];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] & context->main[4];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] & context->main[5];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[7] = context->main[7] & context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void and_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] & context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] ^ context->main[0];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] ^ context->main[1];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] ^ context->main[2];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] ^ context->main[3];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] ^ context->main[4];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] ^ context->main[5];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[7] = context->main[7] ^ context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void xor_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] ^ context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] | context->main[0];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] | context->main[1];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] | context->main[2];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] | context->main[3];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] | context->main[4];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] | context->main[5];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	context->main[7] = context->main[7] | context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void or_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->main[7] = context->main[7] | context->main[7];
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void cp_reg_R_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	context->last_flag_result = context->main[0];
	cmp_tmp16__ = context->main[7] - context->main[0];
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[0])) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[0] ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_reg_R_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	context->last_flag_result = context->main[1];
	cmp_tmp16__ = context->main[7] - context->main[1];
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[1])) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[1] ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_reg_R_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	context->last_flag_result = context->main[2];
	cmp_tmp16__ = context->main[7] - context->main[2];
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[2])) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[2] ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_reg_R_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	context->last_flag_result = context->main[3];
	cmp_tmp16__ = context->main[7] - context->main[3];
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[3])) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[3] ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_reg_R_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	context->last_flag_result = context->main[4];
	cmp_tmp16__ = context->main[7] - context->main[4];
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[4])) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[4] ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_reg_R_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	context->last_flag_result = context->main[5];
	cmp_tmp16__ = context->main[7] - context->main[5];
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[5])) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[5] ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_hl(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->main[4] << 8;
	context->scratch1 = context->main[5] | context->scratch1;
	z80_read_8(context);
	tmp = context->scratch1;
	context->last_flag_result = context->scratch1;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void cp_reg_R_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	context->last_flag_result = context->main[7];
	cmp_tmp16__ = context->main[7] - context->main[7];
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->main[7])) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->main[7] ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void ret_cond_C_000(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = !context->zflag;
	}
	if (z80_check_cond_invert) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void pop_bc(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[1] = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[0] = context->scratch1;
}
void jp_cc_C_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = !context->zflag;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (z80_check_cond_invert) {
	context->pc = context->wz;
	}
}
void jp(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	context->pc = context->wz;
}
void call_cond_C_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = !context->zflag;
	}
	if (z80_check_cond_invert) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void push_bc(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[0];
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[1];
	z80_write_8(context);
}
void add_immed(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	gen_tmp16__ = context->main[7] + context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void rst_T_000(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 0;
	context->pc = 0;
}
void ret_cond_C_001(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	}
	if (context->zflag) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void ret(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
}
void jp_cc_C_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (context->zflag) {
	context->pc = context->wz;
	}
}
void cb_prefix(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->r = 1 + context->r;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	impl_cb[context->scratch1](context, target_cycle);
}
void call_cond_C_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	}
	if (context->zflag) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void call_uncond(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
}
void adc_immed(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	gen_tmp16__ = context->main[7] + context->scratch1 + ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ (~context->scratch1))) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 0;
}
void rst_T_001(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 1;
	context->pc = 8;
}
void ret_cond_C_010(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = ~context->chflags;
	z80_check_cond_invert = 128 & z80_check_cond_invert;
	}
	if (z80_check_cond_invert) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void pop_de(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[3] = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[2] = context->scratch1;
}
void jp_cc_C_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = ~context->chflags;
	z80_check_cond_invert = 128 & z80_check_cond_invert;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (z80_check_cond_invert) {
	context->pc = context->wz;
	}
}
void out_abs(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch2 = context->scratch1;
	context->scratch1 = context->main[7];
	z80_io_write8(context);
}
void call_cond_C_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = ~context->chflags;
	z80_check_cond_invert = 128 & z80_check_cond_invert;
	}
	if (z80_check_cond_invert) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void push_de(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[2];
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[3];
	z80_write_8(context);
}
void sub_immed(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	gen_tmp16__ = context->main[7] - context->scratch1;
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void rst_T_010(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 2;
	context->pc = 16;
}
void ret_cond_C_011(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = 128 & context->chflags;
	}
	if (z80_check_cond_invert) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void exx(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[0];
	context->main[0] = context->alt[0];
	context->alt[0] = gen_tmp8__;
	gen_tmp8__ = context->main[1];
	context->main[1] = context->alt[1];
	context->alt[1] = gen_tmp8__;
	gen_tmp8__ = context->main[2];
	context->main[2] = context->alt[2];
	context->alt[2] = gen_tmp8__;
	gen_tmp8__ = context->main[3];
	context->main[3] = context->alt[3];
	context->alt[3] = gen_tmp8__;
	gen_tmp8__ = context->main[4];
	context->main[4] = context->alt[4];
	context->alt[4] = gen_tmp8__;
	gen_tmp8__ = context->main[5];
	context->main[5] = context->alt[5];
	context->alt[5] = gen_tmp8__;
}
void jp_cc_C_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = 128 & context->chflags;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (z80_check_cond_invert) {
	context->pc = context->wz;
	}
}
void in_abs(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	z80_io_read8(context);
	context->main[7] = context->scratch1;
}
void call_cond_C_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = 128 & context->chflags;
	}
	if (z80_check_cond_invert) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void dd_prefix(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->r = 1 + context->r;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	impl_dd[context->scratch1](context, target_cycle);
}
void sbc_immed(z80_context *context, uint32_t target_cycle)
{
	uint16_t gen_tmp16__;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	gen_tmp16__ = context->main[7] - context->scratch1 - ((context->chflags & 1 << 7) ? 1 : 0);
	context->chflags = (context->chflags & ~128U) | (gen_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ context->scratch1)) & (context->main[7] ^ gen_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ context->scratch1 ^ gen_tmp16__) >> 1U & 8U);
	context->zflag = (gen_tmp16__ & 255) == 0;
	context->last_flag_result = gen_tmp16__;
	context->main[7] = gen_tmp16__;
	context->nflag = 1;
}
void rst_T_011(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 3;
	context->pc = 24;
}
void ret_cond_C_100(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = !context->pvflag;
	}
	if (z80_check_cond_invert) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void pop_hl(z80_context *context, uint32_t target_cycle)
{
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[5] = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[4] = context->scratch1;
}
void jp_cc_C_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = !context->pvflag;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (z80_check_cond_invert) {
	context->pc = context->wz;
	}
}
void ex_sp_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->sp;
	z80_read_8(context);
	gen_tmp8__ = context->main[5];
	context->main[5] = context->scratch1;
	context->scratch1 = gen_tmp8__;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->scratch2 = context->sp;
	z80_write_8(context);
	context->scratch1 = 1 + context->sp;
	z80_read_8(context);
	gen_tmp8__ = context->main[4];
	context->main[4] = context->scratch1;
	context->scratch1 = gen_tmp8__;
	context->cycles += context->opts->gen.clock_divider * 2;
	context->scratch2 = 1 + context->sp;
	z80_write_8(context);
	context->wz = context->main[4] << 8;
	context->wz = context->main[5] | context->wz;
}
void call_cond_C_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = !context->pvflag;
	}
	if (z80_check_cond_invert) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void push_hl(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[4];
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[5];
	z80_write_8(context);
}
void and_immed(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[7] = context->main[7] & context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags |= 8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void rst_T_100(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 4;
	context->pc = 32;
}
void ret_cond_C_101(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	}
	if (context->pvflag) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void jp_hl(z80_context *context, uint32_t target_cycle)
{
	context->pc = context->main[4] << 8;
	context->pc = context->main[5] | context->pc;
}
void jp_cc_C_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (context->pvflag) {
	context->pc = context->wz;
	}
}
void ex_de_hl(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	gen_tmp8__ = context->main[3];
	context->main[3] = context->main[5];
	context->main[5] = gen_tmp8__;
	gen_tmp8__ = context->main[2];
	context->main[2] = context->main[4];
	context->main[4] = gen_tmp8__;
}
void call_cond_C_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	}
	if (context->pvflag) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void ed_prefix(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->r = 1 + context->r;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	impl_ed[context->scratch1](context, target_cycle);
}
void xor_immed(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[7] = context->main[7] ^ context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void rst_T_101(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 5;
	context->pc = 40;
}
void ret_cond_C_110(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = ~context->last_flag_result;
	z80_check_cond_invert = 128 & z80_check_cond_invert;
	}
	if (z80_check_cond_invert) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void pop_af(z80_context *context, uint32_t target_cycle)
{
	context->main[6] = 0;
	if (context->zflag) {
		context->main[6] |= 1 << 6;
	}
	if (context->pvflag) {
		context->main[6] |= 1 << 2;
	}
	if (context->nflag) {
		context->main[6] |= 1 << 1;
	}
	context->main[6] |= context->last_flag_result & 168;
	if (context->chflags & (1 << 3)) {
		context->main[6] |= 1 << 4;
	}
	if (context->chflags & (1 << 7)) {
		context->main[6] |= 1 << 0;
	}
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[6] = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->main[7] = context->scratch1;
	context->zflag = context->main[6] & 64;
	context->pvflag = context->main[6] & 4;
	context->nflag = context->main[6] & 2;
	context->last_flag_result = context->main[6];
	context->chflags = 0;
	context->chflags |= context->main[6] >> 1 & 8;
	context->chflags |= context->main[6] << 7 & 128;
}
void jp_cc_C_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = ~context->last_flag_result;
	z80_check_cond_invert = 128 & z80_check_cond_invert;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (z80_check_cond_invert) {
	context->pc = context->wz;
	}
}
void di(z80_context *context, uint32_t target_cycle)
{
	context->iff1 = 0;
	context->iff2 = 0;
	z80_sync_cycle(context, target_cycle);
}
void call_cond_C_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = ~context->last_flag_result;
	z80_check_cond_invert = 128 & z80_check_cond_invert;
	}
	if (z80_check_cond_invert) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void push_af(z80_context *context, uint32_t target_cycle)
{
	context->main[6] = 0;
	if (context->zflag) {
		context->main[6] |= 1 << 6;
	}
	if (context->pvflag) {
		context->main[6] |= 1 << 2;
	}
	if (context->nflag) {
		context->main[6] |= 1 << 1;
	}
	context->main[6] |= context->last_flag_result & 168;
	if (context->chflags & (1 << 3)) {
		context->main[6] |= 1 << 4;
	}
	if (context->chflags & (1 << 7)) {
		context->main[6] |= 1 << 0;
	}
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[7];
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->main[6];
	z80_write_8(context);
}
void or_immed(z80_context *context, uint32_t target_cycle)
{
	uint8_t gen_tmp8__;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->main[7] = context->main[7] | context->scratch1;
	context->zflag = context->main[7] == 0;
	context->last_flag_result = context->main[7];
	gen_tmp8__ = (context->main[7] ^ (context->main[7] >> 4)) & 0xF;
	context->pvflag = 0x9669 >> gen_tmp8__ & 1;
	context->chflags &= ~8;
	context->nflag = 0;
	context->chflags &= ~128;
}
void rst_T_110(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 6;
	context->pc = 48;
}
void ret_cond_C_111(z80_context *context, uint32_t target_cycle)
{
	uint16_t pch;
	context->cycles += context->opts->gen.clock_divider * 1;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = 128 & context->last_flag_result;
	}
	if (z80_check_cond_invert) {
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	context->pc = context->scratch1;
	context->scratch1 = context->sp;
	z80_read_8(context);
	context->sp = 1 + context->sp;
	pch = context->scratch1;
	pch = pch << 8;
	context->pc = pch | context->pc;
	}
}
void ld_sp_hl(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 2;
	context->sp = context->main[4] << 8;
	context->sp = context->main[5] | context->sp;
}
void jp_cc_C_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = 128 & context->last_flag_result;
	}
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	if (z80_check_cond_invert) {
	context->pc = context->wz;
	}
}
void ei(z80_context *context, uint32_t target_cycle)
{
	uint32_t cmp_tmp32__;
	context->iff1 = 1;
	context->iff2 = 1;
	z80_sync_cycle(context, target_cycle);
	if (context->cycles >= context->int_cycle) {
	context->int_cycle = 1 + context->cycles;
	}
}
void call_cond_C_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->wz = context->scratch1;
	context->pc = 1 + context->pc;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	context->scratch1 = context->scratch1 << 8;
	context->wz = context->scratch1 | context->wz;
	uint8_t z80_check_cond_invert;
	{
	z80_check_cond_invert = 128 & context->last_flag_result;
	}
	if (z80_check_cond_invert) {
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = context->wz;
	}
}
void fd_prefix(z80_context *context, uint32_t target_cycle)
{
	context->cycles += context->opts->gen.clock_divider * 1;
	context->r = 1 + context->r;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	impl_fd[context->scratch1](context, target_cycle);
}
void cp_immed(z80_context *context, uint32_t target_cycle)
{
	uint16_t cmp_tmp16__;
	uint8_t tmp;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	tmp = context->scratch1;
	context->last_flag_result = context->scratch1;
	cmp_tmp16__ = context->main[7] - tmp;
	context->chflags = (context->chflags & ~128U) | (cmp_tmp16__ >> 1U & 128U);
	context->pvflag = (((context->main[7] ^ tmp)) & (context->main[7] ^ cmp_tmp16__)) & 128U;
	context->chflags = (context->chflags & ~8U) | ((context->main[7] ^ tmp ^ cmp_tmp16__) >> 1U & 8U);
	context->zflag = (cmp_tmp16__ & 255) == 0;
	context->last_flag_result = (context->last_flag_result & ~128U) | (cmp_tmp16__ & 128U);
	context->nflag = 1;
}
void rst_T_111(z80_context *context, uint32_t target_cycle)
{
	uint8_t pch;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->scratch1 = 7;
	context->pc = 56;
}
static impl_fun impl_main[256] = {
	nop,
	ld_bc_immed,
	ld_a_to_bc,
	inc_bc,
	inc_reg_R_000,
	dec_reg_R_000,
	ld_immed_R_000,
	rlca,
	ex_af_af,
	add_hl_bc,
	ld_a_from_bc,
	dec_bc,
	inc_reg_R_001,
	dec_reg_R_001,
	ld_immed_R_001,
	rrca,
	djnz,
	ld_de_immed,
	ld_a_to_de,
	inc_de,
	inc_reg_R_010,
	dec_reg_R_010,
	ld_immed_R_010,
	rla,
	jr,
	add_hl_de,
	ld_a_from_de,
	dec_de,
	inc_reg_R_011,
	dec_reg_R_011,
	ld_immed_R_011,
	rra,
	jr_cc_C_00,
	ld_hl_immed,
	ld_hl_to_immed,
	inc16_hl,
	inc_reg_R_100,
	dec_reg_R_100,
	ld_immed_R_100,
	daa,
	jr_cc_C_01,
	add_hl_hl,
	ld_hl_from_immed,
	dec16_hl,
	inc_reg_R_101,
	dec_reg_R_101,
	ld_immed_R_101,
	cpl,
	jr_cc_C_10,
	ld_sp_immed,
	ld_a_to_immed,
	inc_sp,
	inc_hl,
	dec_hl,
	ld_to_hl_immed,
	scf,
	jr_cc_C_11,
	add_hl_sp,
	ld_a_from_immed,
	dec_sp,
	inc_reg_R_111,
	dec_reg_R_111,
	ld_immed_R_111,
	ccf,
	ld_from_reg_D_000_S_000,
	ld_from_reg_D_000_S_001,
	ld_from_reg_D_000_S_010,
	ld_from_reg_D_000_S_011,
	ld_from_reg_D_000_S_100,
	ld_from_reg_D_000_S_101,
	ld_from_hl_R_000,
	ld_from_reg_D_000_S_111,
	ld_from_reg_D_001_S_000,
	ld_from_reg_D_001_S_001,
	ld_from_reg_D_001_S_010,
	ld_from_reg_D_001_S_011,
	ld_from_reg_D_001_S_100,
	ld_from_reg_D_001_S_101,
	ld_from_hl_R_001,
	ld_from_reg_D_001_S_111,
	ld_from_reg_D_010_S_000,
	ld_from_reg_D_010_S_001,
	ld_from_reg_D_010_S_010,
	ld_from_reg_D_010_S_011,
	ld_from_reg_D_010_S_100,
	ld_from_reg_D_010_S_101,
	ld_from_hl_R_010,
	ld_from_reg_D_010_S_111,
	ld_from_reg_D_011_S_000,
	ld_from_reg_D_011_S_001,
	ld_from_reg_D_011_S_010,
	ld_from_reg_D_011_S_011,
	ld_from_reg_D_011_S_100,
	ld_from_reg_D_011_S_101,
	ld_from_hl_R_011,
	ld_from_reg_D_011_S_111,
	ld_from_reg_D_100_S_000,
	ld_from_reg_D_100_S_001,
	ld_from_reg_D_100_S_010,
	ld_from_reg_D_100_S_011,
	ld_from_reg_D_100_S_100,
	ld_from_reg_D_100_S_101,
	ld_from_hl_R_100,
	ld_from_reg_D_100_S_111,
	ld_from_reg_D_101_S_000,
	ld_from_reg_D_101_S_001,
	ld_from_reg_D_101_S_010,
	ld_from_reg_D_101_S_011,
	ld_from_reg_D_101_S_100,
	ld_from_reg_D_101_S_101,
	ld_from_hl_R_101,
	ld_from_reg_D_101_S_111,
	ld_to_hl_R_000,
	ld_to_hl_R_001,
	ld_to_hl_R_010,
	ld_to_hl_R_011,
	ld_to_hl_R_100,
	ld_to_hl_R_101,
	halt,
	ld_to_hl_R_111,
	ld_from_reg_D_111_S_000,
	ld_from_reg_D_111_S_001,
	ld_from_reg_D_111_S_010,
	ld_from_reg_D_111_S_011,
	ld_from_reg_D_111_S_100,
	ld_from_reg_D_111_S_101,
	ld_from_hl_R_111,
	ld_from_reg_D_111_S_111,
	add_reg_R_000,
	add_reg_R_001,
	add_reg_R_010,
	add_reg_R_011,
	add_reg_R_100,
	add_reg_R_101,
	add_hl,
	add_reg_R_111,
	adc_reg_R_000,
	adc_reg_R_001,
	adc_reg_R_010,
	adc_reg_R_011,
	adc_reg_R_100,
	adc_reg_R_101,
	adc_hl,
	adc_reg_R_111,
	sub_reg_R_000,
	sub_reg_R_001,
	sub_reg_R_010,
	sub_reg_R_011,
	sub_reg_R_100,
	sub_reg_R_101,
	sub_hl,
	sub_reg_R_111,
	sbc_reg_R_000,
	sbc_reg_R_001,
	sbc_reg_R_010,
	sbc_reg_R_011,
	sbc_reg_R_100,
	sbc_reg_R_101,
	sbc_hl,
	sbc_reg_R_111,
	and_reg_R_000,
	and_reg_R_001,
	and_reg_R_010,
	and_reg_R_011,
	and_reg_R_100,
	and_reg_R_101,
	and_hl,
	and_reg_R_111,
	xor_reg_R_000,
	xor_reg_R_001,
	xor_reg_R_010,
	xor_reg_R_011,
	xor_reg_R_100,
	xor_reg_R_101,
	xor_hl,
	xor_reg_R_111,
	or_reg_R_000,
	or_reg_R_001,
	or_reg_R_010,
	or_reg_R_011,
	or_reg_R_100,
	or_reg_R_101,
	or_hl,
	or_reg_R_111,
	cp_reg_R_000,
	cp_reg_R_001,
	cp_reg_R_010,
	cp_reg_R_011,
	cp_reg_R_100,
	cp_reg_R_101,
	cp_hl,
	cp_reg_R_111,
	ret_cond_C_000,
	pop_bc,
	jp_cc_C_000,
	jp,
	call_cond_C_000,
	push_bc,
	add_immed,
	rst_T_000,
	ret_cond_C_001,
	ret,
	jp_cc_C_001,
	cb_prefix,
	call_cond_C_001,
	call_uncond,
	adc_immed,
	rst_T_001,
	ret_cond_C_010,
	pop_de,
	jp_cc_C_010,
	out_abs,
	call_cond_C_010,
	push_de,
	sub_immed,
	rst_T_010,
	ret_cond_C_011,
	exx,
	jp_cc_C_011,
	in_abs,
	call_cond_C_011,
	dd_prefix,
	sbc_immed,
	rst_T_011,
	ret_cond_C_100,
	pop_hl,
	jp_cc_C_100,
	ex_sp_hl,
	call_cond_C_100,
	push_hl,
	and_immed,
	rst_T_100,
	ret_cond_C_101,
	jp_hl,
	jp_cc_C_101,
	ex_de_hl,
	call_cond_C_101,
	ed_prefix,
	xor_immed,
	rst_T_101,
	ret_cond_C_110,
	pop_af,
	jp_cc_C_110,
	di,
	call_cond_C_110,
	push_af,
	or_immed,
	rst_T_110,
	ret_cond_C_111,
	ld_sp_hl,
	jp_cc_C_111,
	ei,
	call_cond_C_111,
	fd_prefix,
	cp_immed,
	rst_T_111,
};
void z80_execute(z80_context *context, uint32_t target_cycle)
{
	z80_sync_cycle(context, target_cycle);
	while (context->cycles < target_cycle)
	{
		if (context->cycles >= context->sync_cycle) {
	if (context->cycles >= context->int_cycle) {
	context->iff1 = 0;
	context->iff2 = 0;
	context->cycles += context->opts->gen.clock_divider * 6;
	z80_sync_cycle(context, target_cycle);
	switch(context->imode)
	{
	case 0U: {
	impl_main[context->int_value](context, target_cycle);
	break;
	}
	case 1U: {
	impl_main[255](context, target_cycle);
	break;
	}
	case 2U: {
	context->pc = context->i << 8;
	context->pc = context->int_value | context->pc;
	impl_main[205](context, target_cycle);
	break;
	}
	}
	} else {
	if (context->cycles >= context->nmi_cycle) {
	uint8_t pch;
	context->nmi_cycle = 4294967295;
	context->iff1 = 0;
	pch = context->pc >> 8;
	context->cycles += context->opts->gen.clock_divider * 1;
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = pch;
	z80_write_8(context);
	context->sp = context->sp - 1;
	context->scratch2 = context->sp;
	context->scratch1 = context->pc;
	z80_write_8(context);
	context->pc = 102;
	z80_sync_cycle(context, target_cycle);
	}
	}
		}
	context->cycles += context->opts->gen.clock_divider * 1;
	context->r = 1 + context->r;
	context->scratch1 = context->pc;
	z80_read_8(context);
	context->pc = 1 + context->pc;
	impl_main[context->scratch1](context, target_cycle);
	}
}
