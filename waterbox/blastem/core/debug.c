#include "debug.h"
#include "genesis.h"
#include "68kinst.h"
#include "segacd.h"
#include "blastem.h"
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <sys/select.h>
#endif
#include "render.h"
#include "util.h"
#include "terminal.h"
#include "z80inst.h"

#ifdef NEW_CORE
#define Z80_OPTS opts
#else
#define Z80_OPTS options
#endif



static debug_root roots[5];
static uint32_t num_roots;
#define MAX_DEBUG_ROOTS (sizeof(roots)/sizeof(*roots))

debug_root *find_root(void *cpu)
{
	for (uint32_t i = 0; i < num_roots; i++)
	{
		if (roots[i].cpu_context == cpu) {
			return roots + i;
		}
	}
	if (num_roots < MAX_DEBUG_ROOTS) {
		num_roots++;
		memset(roots + num_roots - 1, 0, sizeof(debug_root));
		roots[num_roots-1].cpu_context = cpu;
		return roots + num_roots - 1;
	}
	return NULL;
}

bp_def ** find_breakpoint(bp_def ** cur, uint32_t address)
{
	while (*cur) {
		if ((*cur)->address == address) {
			break;
		}
		cur = &((*cur)->next);
	}
	return cur;
}

bp_def ** find_breakpoint_idx(bp_def ** cur, uint32_t index)
{
	while (*cur) {
		if ((*cur)->index == index) {
			break;
		}
		cur = &((*cur)->next);
	}
	return cur;
}

disp_def * displays = NULL;
disp_def * zdisplays = NULL;
uint32_t disp_index = 0;
uint32_t zdisp_index = 0;

void add_display(disp_def ** head, uint32_t *index, char format_char, char * param)
{
	disp_def * ndisp = malloc(sizeof(*ndisp));
	ndisp->format_char = format_char;
	ndisp->param = strdup(param);
	ndisp->next = *head;
	ndisp->index = *index++;
	*head = ndisp;
}

void remove_display(disp_def ** head, uint32_t index)
{
	while (*head) {
		if ((*head)->index == index) {
			disp_def * del_disp = *head;
			*head = del_disp->next;
			free(del_disp->param);
			free(del_disp);
		} else {
			head = &(*head)->next;
		}
	}
}

char * find_param(char * buf)
{
	for (; *buf; buf++) {
		if (*buf == ' ') {
			if (*(buf+1)) {
				return buf+1;
			}
		}
	}
	return NULL;
}

void strip_nl(char * buf)
{
	for(; *buf; buf++) {
		if (*buf == '\n') {
			*buf = 0;
			return;
		}
	}
}

static uint8_t m68k_read_byte(uint32_t address, m68k_context *context)
{
	//TODO: share this implementation with GDB debugger
	return read_byte(address, (void **)context->mem_pointers, &context->options->gen, context);
}

uint16_t m68k_read_word(uint32_t address, m68k_context *context)
{
	return read_word(address, (void **)context->mem_pointers, &context->options->gen, context);
}

uint32_t m68k_read_long(uint32_t address, m68k_context *context)
{
	return m68k_read_word(address, context) << 16 | m68k_read_word(address + 2, context);
}

void debugger_print(m68k_context *context, char format_char, char *param, uint32_t address)
{
}

#ifndef NO_Z80

void zdebugger_print(z80_context * context, char format_char, char * param)
{
}

z80_context * zdebugger(z80_context * context, uint16_t address)
{
	return context;
}

#endif

void debugger(m68k_context * context, uint32_t address)
{
	return;
}
