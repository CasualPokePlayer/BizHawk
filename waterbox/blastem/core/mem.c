/*
 Copyright 2013 Michael Pavone
 This file is part of BlastEm.
 BlastEm is free software distributed under the terms of the GNU General Public License version 3 or greater. See COPYING for full license text.
*/
#include <sys/mman.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "mem.h"
#include "arena.h"
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

#ifndef MAP_32BIT
#define MAP_32BIT 0
#endif

_Alignas(PAGE_SIZE) static uint8_t fixedBuffer[16384 * 1024];
static int markedExec = 0;

void * alloc_code(size_t *size)
{
	if (!markedExec) {
		int err = mprotect((void*)fixedBuffer, sizeof (fixedBuffer), PROT_READ | PROT_WRITE | PROT_EXEC);
		if (err) {
			perror("alloc_code");
			return NULL;
		}
		markedExec = 1;
	}

	//start at the 1GB mark to allow plenty of room for sbrk based malloc implementations
	//while still keeping well within 32-bit displacement range for calling code compiled into the executable
	static uint8_t *next = (uint8_t *)fixedBuffer;
	uint8_t *ret = try_alloc_arena();
	if (ret) {
		return ret;
	}
	if (*size & (PAGE_SIZE -1)) {
		*size += PAGE_SIZE - (*size & (PAGE_SIZE - 1));
	}
	/*ret = mmap(next, *size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
	if (ret == MAP_FAILED) {
		perror("alloc_code");
		return NULL;
	}*/
	ret = next;
	track_block(ret);
	next = ret + *size;
	return ret;
}

