#ifndef CD_GRAPHICS_H_
#define CD_GRAPHICS_H_

#include "segacd.h"

enum {
	GA_STAMP_SIZE = 0x58/2,
	GA_STAMP_MAP_BASE,
	GA_IMAGE_BUFFER_VCELLS,
	GA_IMAGE_BUFFER_START,
	GA_IMAGE_BUFFER_OFFSET,
	GA_IMAGE_BUFFER_HDOTS,
	GA_IMAGE_BUFFER_LINES,
	GA_TRACE_VECTOR_BASE
};

//GA_STAMP_SIZE
#define BIT_GRON 0x8000
#define BIT_SMS  0x0004
#define BIT_STS  0x0002
#define BIT_RPT  0x0001

void cd_graphics_init(segacd_context *cd);
void cd_graphics_run(segacd_context *cd, uint32_t cycle);
void cd_graphics_start(segacd_context *cd);

#endif //CD_GRAPHICS_H_
