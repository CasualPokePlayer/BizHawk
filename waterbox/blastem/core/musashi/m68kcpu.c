// license:BSD-3-Clause
// copyright-holders:Karl Stenerud
/* ======================================================================== */
/* ========================= LICENSING & COPYRIGHT ======================== */
/* ======================================================================== */

#if 0
static const char copyright_notice[] =
"MUSASHI\n"
"Version 4.95 (2012-02-19)\n"
"A portable Motorola M68xxx/CPU32/ColdFire processor emulation engine.\n"
"Copyright Karl Stenerud.  All rights reserved.\n"
;
#endif


/* ======================================================================== */
/* ================================= NOTES ================================ */
/* ======================================================================== */



/* ======================================================================== */
/* ================================ INCLUDES ============================== */
/* ======================================================================== */

#include "m68kcpu.h"
#include "m68kops.h"
#include <stdlib.h>
#include <string.h>


/* ======================================================================== */
/* ================================= DATA ================================= */
/* ======================================================================== */

/* Used by shift & rotate instructions */
const uint8_t m68ki_shift_8_table[65] =
{
	0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff
};
const uint16_t m68ki_shift_16_table[65] =
{
	0x0000, 0x8000, 0xc000, 0xe000, 0xf000, 0xf800, 0xfc00, 0xfe00, 0xff00,
	0xff80, 0xffc0, 0xffe0, 0xfff0, 0xfff8, 0xfffc, 0xfffe, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff
};
const uint32_t m68ki_shift_32_table[65] =
{
	0x00000000, 0x80000000, 0xc0000000, 0xe0000000, 0xf0000000, 0xf8000000,
	0xfc000000, 0xfe000000, 0xff000000, 0xff800000, 0xffc00000, 0xffe00000,
	0xfff00000, 0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000, 0xffff8000,
	0xffffc000, 0xffffe000, 0xfffff000, 0xfffff800, 0xfffffc00, 0xfffffe00,
	0xffffff00, 0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0, 0xfffffff8,
	0xfffffffc, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
};


/* Number of clock cycles to use for exception processing.
 * I used 4 for any vectors that are undocumented for processing times.
 */
const uint8_t m68ki_exception_cycle_table[7][256] =
{
	{ /* 000 */
			40, /*  0: Reset - Initial Stack Pointer                      */
			4, /*  1: Reset - Initial Program Counter                    */
			50, /*  2: Bus Error                             (unemulated) */
			50, /*  3: Address Error                         (unemulated) */
			34, /*  4: Illegal Instruction                                */
			38, /*  5: Divide by Zero                                     */
			40, /*  6: CHK                                                */
			34, /*  7: TRAPV                                              */
			34, /*  8: Privilege Violation                                */
			34, /*  9: Trace                                              */
			4, /* 10: 1010                                               */
			4, /* 11: 1111                                               */
			4, /* 12: RESERVED                                           */
			4, /* 13: Coprocessor Protocol Violation        (unemulated) */
			4, /* 14: Format Error                                       */
			44, /* 15: Uninitialized Interrupt                            */
			4, /* 16: RESERVED                                           */
			4, /* 17: RESERVED                                           */
			4, /* 18: RESERVED                                           */
			4, /* 19: RESERVED                                           */
			4, /* 20: RESERVED                                           */
			4, /* 21: RESERVED                                           */
			4, /* 22: RESERVED                                           */
			4, /* 23: RESERVED                                           */
			44, /* 24: Spurious Interrupt                                 */
			44, /* 25: Level 1 Interrupt Autovector                       */
			44, /* 26: Level 2 Interrupt Autovector                       */
			44, /* 27: Level 3 Interrupt Autovector                       */
			44, /* 28: Level 4 Interrupt Autovector                       */
			44, /* 29: Level 5 Interrupt Autovector                       */
			44, /* 30: Level 6 Interrupt Autovector                       */
			44, /* 31: Level 7 Interrupt Autovector                       */
			34, /* 32: TRAP #0                                            */
			34, /* 33: TRAP #1                                            */
			34, /* 34: TRAP #2                                            */
			34, /* 35: TRAP #3                                            */
			34, /* 36: TRAP #4                                            */
			34, /* 37: TRAP #5                                            */
			34, /* 38: TRAP #6                                            */
			34, /* 39: TRAP #7                                            */
			34, /* 40: TRAP #8                                            */
			34, /* 41: TRAP #9                                            */
			34, /* 42: TRAP #10                                           */
			34, /* 43: TRAP #11                                           */
			34, /* 44: TRAP #12                                           */
			34, /* 45: TRAP #13                                           */
			34, /* 46: TRAP #14                                           */
			34, /* 47: TRAP #15                                           */
			4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
			4, /* 49: FP Inexact Result                     (unemulated) */
			4, /* 50: FP Divide by Zero                     (unemulated) */
			4, /* 51: FP Underflow                          (unemulated) */
			4, /* 52: FP Operand Error                      (unemulated) */
			4, /* 53: FP Overflow                           (unemulated) */
			4, /* 54: FP Signaling NAN                      (unemulated) */
			4, /* 55: FP Unimplemented Data Type            (unemulated) */
			4, /* 56: MMU Configuration Error               (unemulated) */
			4, /* 57: MMU Illegal Operation Error           (unemulated) */
			4, /* 58: MMU Access Level Violation Error      (unemulated) */
			4, /* 59: RESERVED                                           */
			4, /* 60: RESERVED                                           */
			4, /* 61: RESERVED                                           */
			4, /* 62: RESERVED                                           */
			4, /* 63: RESERVED                                           */
				/* 64-255: User Defined                                   */
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 010 */
			40, /*  0: Reset - Initial Stack Pointer                      */
			4, /*  1: Reset - Initial Program Counter                    */
		126, /*  2: Bus Error                             (unemulated) */
		126, /*  3: Address Error                         (unemulated) */
			38, /*  4: Illegal Instruction                                */
			44, /*  5: Divide by Zero                                     */
			44, /*  6: CHK                                                */
			34, /*  7: TRAPV                                              */
			38, /*  8: Privilege Violation                                */
			38, /*  9: Trace                                              */
			4, /* 10: 1010                                               */
			4, /* 11: 1111                                               */
			4, /* 12: RESERVED                                           */
			4, /* 13: Coprocessor Protocol Violation        (unemulated) */
			4, /* 14: Format Error                                       */
			44, /* 15: Uninitialized Interrupt                            */
			4, /* 16: RESERVED                                           */
			4, /* 17: RESERVED                                           */
			4, /* 18: RESERVED                                           */
			4, /* 19: RESERVED                                           */
			4, /* 20: RESERVED                                           */
			4, /* 21: RESERVED                                           */
			4, /* 22: RESERVED                                           */
			4, /* 23: RESERVED                                           */
			46, /* 24: Spurious Interrupt                                 */
			46, /* 25: Level 1 Interrupt Autovector                       */
			46, /* 26: Level 2 Interrupt Autovector                       */
			46, /* 27: Level 3 Interrupt Autovector                       */
			46, /* 28: Level 4 Interrupt Autovector                       */
			46, /* 29: Level 5 Interrupt Autovector                       */
			46, /* 30: Level 6 Interrupt Autovector                       */
			46, /* 31: Level 7 Interrupt Autovector                       */
			38, /* 32: TRAP #0                                            */
			38, /* 33: TRAP #1                                            */
			38, /* 34: TRAP #2                                            */
			38, /* 35: TRAP #3                                            */
			38, /* 36: TRAP #4                                            */
			38, /* 37: TRAP #5                                            */
			38, /* 38: TRAP #6                                            */
			38, /* 39: TRAP #7                                            */
			38, /* 40: TRAP #8                                            */
			38, /* 41: TRAP #9                                            */
			38, /* 42: TRAP #10                                           */
			38, /* 43: TRAP #11                                           */
			38, /* 44: TRAP #12                                           */
			38, /* 45: TRAP #13                                           */
			38, /* 46: TRAP #14                                           */
			38, /* 47: TRAP #15                                           */
			4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
			4, /* 49: FP Inexact Result                     (unemulated) */
			4, /* 50: FP Divide by Zero                     (unemulated) */
			4, /* 51: FP Underflow                          (unemulated) */
			4, /* 52: FP Operand Error                      (unemulated) */
			4, /* 53: FP Overflow                           (unemulated) */
			4, /* 54: FP Signaling NAN                      (unemulated) */
			4, /* 55: FP Unimplemented Data Type            (unemulated) */
			4, /* 56: MMU Configuration Error               (unemulated) */
			4, /* 57: MMU Illegal Operation Error           (unemulated) */
			4, /* 58: MMU Access Level Violation Error      (unemulated) */
			4, /* 59: RESERVED                                           */
			4, /* 60: RESERVED                                           */
			4, /* 61: RESERVED                                           */
			4, /* 62: RESERVED                                           */
			4, /* 63: RESERVED                                           */
				/* 64-255: User Defined                                   */
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 020 */
			4, /*  0: Reset - Initial Stack Pointer                      */
			4, /*  1: Reset - Initial Program Counter                    */
			50, /*  2: Bus Error                             (unemulated) */
			50, /*  3: Address Error                         (unemulated) */
			20, /*  4: Illegal Instruction                                */
			38, /*  5: Divide by Zero                                     */
			40, /*  6: CHK                                                */
			20, /*  7: TRAPV                                              */
			34, /*  8: Privilege Violation                                */
			25, /*  9: Trace                                              */
			20, /* 10: 1010                                               */
			20, /* 11: 1111                                               */
			4, /* 12: RESERVED                                           */
			4, /* 13: Coprocessor Protocol Violation        (unemulated) */
			4, /* 14: Format Error                                       */
			30, /* 15: Uninitialized Interrupt                            */
			4, /* 16: RESERVED                                           */
			4, /* 17: RESERVED                                           */
			4, /* 18: RESERVED                                           */
			4, /* 19: RESERVED                                           */
			4, /* 20: RESERVED                                           */
			4, /* 21: RESERVED                                           */
			4, /* 22: RESERVED                                           */
			4, /* 23: RESERVED                                           */
			30, /* 24: Spurious Interrupt                                 */
			30, /* 25: Level 1 Interrupt Autovector                       */
			30, /* 26: Level 2 Interrupt Autovector                       */
			30, /* 27: Level 3 Interrupt Autovector                       */
			30, /* 28: Level 4 Interrupt Autovector                       */
			30, /* 29: Level 5 Interrupt Autovector                       */
			30, /* 30: Level 6 Interrupt Autovector                       */
			30, /* 31: Level 7 Interrupt Autovector                       */
			20, /* 32: TRAP #0                                            */
			20, /* 33: TRAP #1                                            */
			20, /* 34: TRAP #2                                            */
			20, /* 35: TRAP #3                                            */
			20, /* 36: TRAP #4                                            */
			20, /* 37: TRAP #5                                            */
			20, /* 38: TRAP #6                                            */
			20, /* 39: TRAP #7                                            */
			20, /* 40: TRAP #8                                            */
			20, /* 41: TRAP #9                                            */
			20, /* 42: TRAP #10                                           */
			20, /* 43: TRAP #11                                           */
			20, /* 44: TRAP #12                                           */
			20, /* 45: TRAP #13                                           */
			20, /* 46: TRAP #14                                           */
			20, /* 47: TRAP #15                                           */
			4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
			4, /* 49: FP Inexact Result                     (unemulated) */
			4, /* 50: FP Divide by Zero                     (unemulated) */
			4, /* 51: FP Underflow                          (unemulated) */
			4, /* 52: FP Operand Error                      (unemulated) */
			4, /* 53: FP Overflow                           (unemulated) */
			4, /* 54: FP Signaling NAN                      (unemulated) */
			4, /* 55: FP Unimplemented Data Type            (unemulated) */
			4, /* 56: MMU Configuration Error               (unemulated) */
			4, /* 57: MMU Illegal Operation Error           (unemulated) */
			4, /* 58: MMU Access Level Violation Error      (unemulated) */
			4, /* 59: RESERVED                                           */
			4, /* 60: RESERVED                                           */
			4, /* 61: RESERVED                                           */
			4, /* 62: RESERVED                                           */
			4, /* 63: RESERVED                                           */
				/* 64-255: User Defined                                   */
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 030 - not correct */
			4, /*  0: Reset - Initial Stack Pointer                      */
			4, /*  1: Reset - Initial Program Counter                    */
			50, /*  2: Bus Error                             (unemulated) */
			50, /*  3: Address Error                         (unemulated) */
			20, /*  4: Illegal Instruction                                */
			38, /*  5: Divide by Zero                                     */
			40, /*  6: CHK                                                */
			20, /*  7: TRAPV                                              */
			34, /*  8: Privilege Violation                                */
			25, /*  9: Trace                                              */
			20, /* 10: 1010                                               */
			20, /* 11: 1111                                               */
			4, /* 12: RESERVED                                           */
			4, /* 13: Coprocessor Protocol Violation        (unemulated) */
			4, /* 14: Format Error                                       */
			30, /* 15: Uninitialized Interrupt                            */
			4, /* 16: RESERVED                                           */
			4, /* 17: RESERVED                                           */
			4, /* 18: RESERVED                                           */
			4, /* 19: RESERVED                                           */
			4, /* 20: RESERVED                                           */
			4, /* 21: RESERVED                                           */
			4, /* 22: RESERVED                                           */
			4, /* 23: RESERVED                                           */
			30, /* 24: Spurious Interrupt                                 */
			30, /* 25: Level 1 Interrupt Autovector                       */
			30, /* 26: Level 2 Interrupt Autovector                       */
			30, /* 27: Level 3 Interrupt Autovector                       */
			30, /* 28: Level 4 Interrupt Autovector                       */
			30, /* 29: Level 5 Interrupt Autovector                       */
			30, /* 30: Level 6 Interrupt Autovector                       */
			30, /* 31: Level 7 Interrupt Autovector                       */
			20, /* 32: TRAP #0                                            */
			20, /* 33: TRAP #1                                            */
			20, /* 34: TRAP #2                                            */
			20, /* 35: TRAP #3                                            */
			20, /* 36: TRAP #4                                            */
			20, /* 37: TRAP #5                                            */
			20, /* 38: TRAP #6                                            */
			20, /* 39: TRAP #7                                            */
			20, /* 40: TRAP #8                                            */
			20, /* 41: TRAP #9                                            */
			20, /* 42: TRAP #10                                           */
			20, /* 43: TRAP #11                                           */
			20, /* 44: TRAP #12                                           */
			20, /* 45: TRAP #13                                           */
			20, /* 46: TRAP #14                                           */
			20, /* 47: TRAP #15                                           */
			4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
			4, /* 49: FP Inexact Result                     (unemulated) */
			4, /* 50: FP Divide by Zero                     (unemulated) */
			4, /* 51: FP Underflow                          (unemulated) */
			4, /* 52: FP Operand Error                      (unemulated) */
			4, /* 53: FP Overflow                           (unemulated) */
			4, /* 54: FP Signaling NAN                      (unemulated) */
			4, /* 55: FP Unimplemented Data Type            (unemulated) */
			4, /* 56: MMU Configuration Error               (unemulated) */
			4, /* 57: MMU Illegal Operation Error           (unemulated) */
			4, /* 58: MMU Access Level Violation Error      (unemulated) */
			4, /* 59: RESERVED                                           */
			4, /* 60: RESERVED                                           */
			4, /* 61: RESERVED                                           */
			4, /* 62: RESERVED                                           */
			4, /* 63: RESERVED                                           */
				/* 64-255: User Defined                                   */
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* 040 */ // TODO: these values are not correct
			4, /*  0: Reset - Initial Stack Pointer                      */
			4, /*  1: Reset - Initial Program Counter                    */
			50, /*  2: Bus Error                             (unemulated) */
			50, /*  3: Address Error                         (unemulated) */
			20, /*  4: Illegal Instruction                                */
			38, /*  5: Divide by Zero                                     */
			40, /*  6: CHK                                                */
			20, /*  7: TRAPV                                              */
			34, /*  8: Privilege Violation                                */
			25, /*  9: Trace                                              */
			20, /* 10: 1010                                               */
			20, /* 11: 1111                                               */
			4, /* 12: RESERVED                                           */
			4, /* 13: Coprocessor Protocol Violation        (unemulated) */
			4, /* 14: Format Error                                       */
			30, /* 15: Uninitialized Interrupt                            */
			4, /* 16: RESERVED                                           */
			4, /* 17: RESERVED                                           */
			4, /* 18: RESERVED                                           */
			4, /* 19: RESERVED                                           */
			4, /* 20: RESERVED                                           */
			4, /* 21: RESERVED                                           */
			4, /* 22: RESERVED                                           */
			4, /* 23: RESERVED                                           */
			30, /* 24: Spurious Interrupt                                 */
			30, /* 25: Level 1 Interrupt Autovector                       */
			30, /* 26: Level 2 Interrupt Autovector                       */
			30, /* 27: Level 3 Interrupt Autovector                       */
			30, /* 28: Level 4 Interrupt Autovector                       */
			30, /* 29: Level 5 Interrupt Autovector                       */
			30, /* 30: Level 6 Interrupt Autovector                       */
			30, /* 31: Level 7 Interrupt Autovector                       */
			20, /* 32: TRAP #0                                            */
			20, /* 33: TRAP #1                                            */
			20, /* 34: TRAP #2                                            */
			20, /* 35: TRAP #3                                            */
			20, /* 36: TRAP #4                                            */
			20, /* 37: TRAP #5                                            */
			20, /* 38: TRAP #6                                            */
			20, /* 39: TRAP #7                                            */
			20, /* 40: TRAP #8                                            */
			20, /* 41: TRAP #9                                            */
			20, /* 42: TRAP #10                                           */
			20, /* 43: TRAP #11                                           */
			20, /* 44: TRAP #12                                           */
			20, /* 45: TRAP #13                                           */
			20, /* 46: TRAP #14                                           */
			20, /* 47: TRAP #15                                           */
			4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
			4, /* 49: FP Inexact Result                     (unemulated) */
			4, /* 50: FP Divide by Zero                     (unemulated) */
			4, /* 51: FP Underflow                          (unemulated) */
			4, /* 52: FP Operand Error                      (unemulated) */
			4, /* 53: FP Overflow                           (unemulated) */
			4, /* 54: FP Signaling NAN                      (unemulated) */
			4, /* 55: FP Unimplemented Data Type            (unemulated) */
			4, /* 56: MMU Configuration Error               (unemulated) */
			4, /* 57: MMU Illegal Operation Error           (unemulated) */
			4, /* 58: MMU Access Level Violation Error      (unemulated) */
			4, /* 59: RESERVED                                           */
			4, /* 60: RESERVED                                           */
			4, /* 61: RESERVED                                           */
			4, /* 62: RESERVED                                           */
			4, /* 63: RESERVED                                           */
				/* 64-255: User Defined                                   */
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* CPU32 */
			4, /*  0: Reset - Initial Stack Pointer                      */
			4, /*  1: Reset - Initial Program Counter                    */
			50, /*  2: Bus Error                             (unemulated) */
			50, /*  3: Address Error                         (unemulated) */
			20, /*  4: Illegal Instruction                                */
			38, /*  5: Divide by Zero                                     */
			40, /*  6: CHK                                                */
			20, /*  7: TRAPV                                              */
			34, /*  8: Privilege Violation                                */
			25, /*  9: Trace                                              */
			20, /* 10: 1010                                               */
			20, /* 11: 1111                                               */
			4, /* 12: RESERVED                                           */
			4, /* 13: Coprocessor Protocol Violation        (unemulated) */
			4, /* 14: Format Error                                       */
			30, /* 15: Uninitialized Interrupt                            */
			4, /* 16: RESERVED                                           */
			4, /* 17: RESERVED                                           */
			4, /* 18: RESERVED                                           */
			4, /* 19: RESERVED                                           */
			4, /* 20: RESERVED                                           */
			4, /* 21: RESERVED                                           */
			4, /* 22: RESERVED                                           */
			4, /* 23: RESERVED                                           */
			30, /* 24: Spurious Interrupt                                 */
			30, /* 25: Level 1 Interrupt Autovector                       */
			30, /* 26: Level 2 Interrupt Autovector                       */
			30, /* 27: Level 3 Interrupt Autovector                       */
			30, /* 28: Level 4 Interrupt Autovector                       */
			30, /* 29: Level 5 Interrupt Autovector                       */
			30, /* 30: Level 6 Interrupt Autovector                       */
			30, /* 31: Level 7 Interrupt Autovector                       */
			20, /* 32: TRAP #0                                            */
			20, /* 33: TRAP #1                                            */
			20, /* 34: TRAP #2                                            */
			20, /* 35: TRAP #3                                            */
			20, /* 36: TRAP #4                                            */
			20, /* 37: TRAP #5                                            */
			20, /* 38: TRAP #6                                            */
			20, /* 39: TRAP #7                                            */
			20, /* 40: TRAP #8                                            */
			20, /* 41: TRAP #9                                            */
			20, /* 42: TRAP #10                                           */
			20, /* 43: TRAP #11                                           */
			20, /* 44: TRAP #12                                           */
			20, /* 45: TRAP #13                                           */
			20, /* 46: TRAP #14                                           */
			20, /* 47: TRAP #15                                           */
			4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
			4, /* 49: FP Inexact Result                     (unemulated) */
			4, /* 50: FP Divide by Zero                     (unemulated) */
			4, /* 51: FP Underflow                          (unemulated) */
			4, /* 52: FP Operand Error                      (unemulated) */
			4, /* 53: FP Overflow                           (unemulated) */
			4, /* 54: FP Signaling NAN                      (unemulated) */
			4, /* 55: FP Unimplemented Data Type            (unemulated) */
			4, /* 56: MMU Configuration Error               (unemulated) */
			4, /* 57: MMU Illegal Operation Error           (unemulated) */
			4, /* 58: MMU Access Level Violation Error      (unemulated) */
			4, /* 59: RESERVED                                           */
			4, /* 60: RESERVED                                           */
			4, /* 61: RESERVED                                           */
			4, /* 62: RESERVED                                           */
			4, /* 63: RESERVED                                           */
				/* 64-255: User Defined                                   */
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
	{ /* ColdFire - not correct */
			4, /*  0: Reset - Initial Stack Pointer                      */
			4, /*  1: Reset - Initial Program Counter                    */
			50, /*  2: Bus Error                             (unemulated) */
			50, /*  3: Address Error                         (unemulated) */
			20, /*  4: Illegal Instruction                                */
			38, /*  5: Divide by Zero                                     */
			40, /*  6: CHK                                                */
			20, /*  7: TRAPV                                              */
			34, /*  8: Privilege Violation                                */
			25, /*  9: Trace                                              */
			20, /* 10: 1010                                               */
			20, /* 11: 1111                                               */
			4, /* 12: RESERVED                                           */
			4, /* 13: Coprocessor Protocol Violation        (unemulated) */
			4, /* 14: Format Error                                       */
			30, /* 15: Uninitialized Interrupt                            */
			4, /* 16: RESERVED                                           */
			4, /* 17: RESERVED                                           */
			4, /* 18: RESERVED                                           */
			4, /* 19: RESERVED                                           */
			4, /* 20: RESERVED                                           */
			4, /* 21: RESERVED                                           */
			4, /* 22: RESERVED                                           */
			4, /* 23: RESERVED                                           */
			30, /* 24: Spurious Interrupt                                 */
			30, /* 25: Level 1 Interrupt Autovector                       */
			30, /* 26: Level 2 Interrupt Autovector                       */
			30, /* 27: Level 3 Interrupt Autovector                       */
			30, /* 28: Level 4 Interrupt Autovector                       */
			30, /* 29: Level 5 Interrupt Autovector                       */
			30, /* 30: Level 6 Interrupt Autovector                       */
			30, /* 31: Level 7 Interrupt Autovector                       */
			20, /* 32: TRAP #0                                            */
			20, /* 33: TRAP #1                                            */
			20, /* 34: TRAP #2                                            */
			20, /* 35: TRAP #3                                            */
			20, /* 36: TRAP #4                                            */
			20, /* 37: TRAP #5                                            */
			20, /* 38: TRAP #6                                            */
			20, /* 39: TRAP #7                                            */
			20, /* 40: TRAP #8                                            */
			20, /* 41: TRAP #9                                            */
			20, /* 42: TRAP #10                                           */
			20, /* 43: TRAP #11                                           */
			20, /* 44: TRAP #12                                           */
			20, /* 45: TRAP #13                                           */
			20, /* 46: TRAP #14                                           */
			20, /* 47: TRAP #15                                           */
			4, /* 48: FP Branch or Set on Unknown Condition (unemulated) */
			4, /* 49: FP Inexact Result                     (unemulated) */
			4, /* 50: FP Divide by Zero                     (unemulated) */
			4, /* 51: FP Underflow                          (unemulated) */
			4, /* 52: FP Operand Error                      (unemulated) */
			4, /* 53: FP Overflow                           (unemulated) */
			4, /* 54: FP Signaling NAN                      (unemulated) */
			4, /* 55: FP Unimplemented Data Type            (unemulated) */
			4, /* 56: MMU Configuration Error               (unemulated) */
			4, /* 57: MMU Illegal Operation Error           (unemulated) */
			4, /* 58: MMU Access Level Violation Error      (unemulated) */
			4, /* 59: RESERVED                                           */
			4, /* 60: RESERVED                                           */
			4, /* 61: RESERVED                                           */
			4, /* 62: RESERVED                                           */
			4, /* 63: RESERVED                                           */
				/* 64-255: User Defined                                   */
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
	},
};

const uint8_t m68ki_ea_idx_cycle_table[64] =
{
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0, /* ..01.000 no memory indirect, base nullptr             */
		5, /* ..01..01 memory indirect,    base nullptr, outer nullptr */
		7, /* ..01..10 memory indirect,    base nullptr, outer 16   */
		7, /* ..01..11 memory indirect,    base nullptr, outer 32   */
		0,  5,  7,  7,  0,  5,  7,  7,  0,  5,  7,  7,
		2, /* ..10.000 no memory indirect, base 16               */
		7, /* ..10..01 memory indirect,    base 16,   outer nullptr */
		9, /* ..10..10 memory indirect,    base 16,   outer 16   */
		9, /* ..10..11 memory indirect,    base 16,   outer 32   */
		0,  7,  9,  9,  0,  7,  9,  9,  0,  7,  9,  9,
		6, /* ..11.000 no memory indirect, base 32               */
	11, /* ..11..01 memory indirect,    base 32,   outer nullptr */
	13, /* ..11..10 memory indirect,    base 32,   outer 16   */
	13, /* ..11..11 memory indirect,    base 32,   outer 32   */
		0, 11, 13, 13,  0, 11, 13, 13,  0, 11, 13, 13
};



/***************************************************************************
    CPU STATE DESCRIPTION
***************************************************************************/

#define MASK_ALL                (CPU_TYPE_000 | CPU_TYPE_008 | CPU_TYPE_010 | CPU_TYPE_EC020 | CPU_TYPE_020 | CPU_TYPE_EC030 | CPU_TYPE_030 | CPU_TYPE_EC040 | CPU_TYPE_040 | CPU_TYPE_FSCPU32 )
#define MASK_24BIT_SPACE            (CPU_TYPE_000 | CPU_TYPE_008 | CPU_TYPE_010 | CPU_TYPE_EC020)
#define MASK_32BIT_SPACE            (CPU_TYPE_020 | CPU_TYPE_EC030 | CPU_TYPE_030 | CPU_TYPE_EC040 | CPU_TYPE_040 | CPU_TYPE_FSCPU32 )
#define MASK_010_OR_LATER           (CPU_TYPE_010 | CPU_TYPE_EC020 | CPU_TYPE_020 | CPU_TYPE_030 | CPU_TYPE_EC030 | CPU_TYPE_040 | CPU_TYPE_EC040 | CPU_TYPE_FSCPU32 )
#define MASK_020_OR_LATER           (CPU_TYPE_EC020 | CPU_TYPE_020 | CPU_TYPE_EC030 | CPU_TYPE_030 | CPU_TYPE_EC040 | CPU_TYPE_040 | CPU_TYPE_FSCPU32 )
#define MASK_030_OR_LATER           (CPU_TYPE_030 | CPU_TYPE_EC030 | CPU_TYPE_040 | CPU_TYPE_EC040)
#define MASK_040_OR_LATER           (CPU_TYPE_040 | CPU_TYPE_EC040)



/* ======================================================================== */
/* ================================= API ================================== */
/* ======================================================================== */



void m68k_cpu_execute(m68000_base_device *this)
{
	//this->initial_cycles = this->remaining_cycles;

	/* eat up any reset cycles */
	/*if (this->reset_cycles) {
		int rc = this->reset_cycles;
		this->reset_cycles = 0;
		this->remaining_cycles -= rc;

		if (this->remaining_cycles <= 0) return;
	}*/

	/* See if interrupts came in */
	m68ki_check_interrupts(this);

	/* Make sure we're not stopped */
	if(!this->stopped)
	{
		/* Return point if we had an address error */
		/*check_address_error:
		if (this->m_address_error==1)
		{
			this->m_address_error = 0;
			try {
				m68ki_exception_address_error(this);
			}
			catch(int error)
			{
				if (error==10)
				{
					this->m_address_error = 1;
					REG_PPC(this) = REG_PC(this);
					goto check_address_error;
				}
				else
					throw;
			}
			if(stopped)
			{
				if (remaining_cycles > 0)
					remaining_cycles = 0;
				return;
			}
		}*/


		/* Main loop.  Keep going until we run out of clock cycles */
		while (this->c.current_cycle < this->c.target_cycle)
		{
			/* Set tracing accodring to T1. (T0 is done inside instruction) */
			m68ki_trace_t1(this); /* auto-disable (see m68kcpu.h) */

			/* Record previous program counter */
			REG_PPC(this) = REG_PC(this);
			
			
				this->run_mode = RUN_MODE_NORMAL;
				/* Read an instruction and call its handler */
				this->ir = m68ki_read_imm_16(this);
				this->jump_table[this->ir](this);
				this->c.current_cycle += this->cyc_instruction[this->ir];
			
			/*}
			catch (int error)
			{
				if (error==10)
				{
					m_address_error = 1;
					goto check_address_error;
				}
				else
					throw;
			}*/


			/* Trace m68k_exception, if necessary */
			m68ki_exception_if_trace(this); /* auto-disable (see m68kcpu.h) */
		}

		/* set previous PC to current PC for the next entry into the loop */
		REG_PPC(this) = REG_PC(this);
	}
	else if (this->c.current_cycle < this->c.target_cycle)
		this->c.current_cycle = this->c.target_cycle;
	this->c.status = m68ki_get_sr(this) >> 8;
}



void m68k_init_cpu_common(m68000_base_device *this)
{
	static uint32_t emulation_initialized = 0;


	/* The first call to this function initializes the opcode handler jump table */
	if(!emulation_initialized)
	{
		m68ki_build_opcode_table();
		emulation_initialized = 1;
	}

	

	//m_icountptr = &remaining_cycles;
	this->c.current_cycle = 0;

}

void m68k_reset_cpu(m68000_base_device *this)
{


	/* Clear all stop levels and eat up all remaining cycles */
	this->stopped = 0;

	this->run_mode = RUN_MODE_BERR_AERR_RESET;
	/* Go to supervisor mode */
	m68ki_set_sm_flag(this, SFLAG_SET | MFLAG_CLEAR);

	/* Invalidate the prefetch queue */
	/* Set to arbitrary number since our first fetch is from 0 */
	this->pref_addr = 0x1000;

	/* Read the initial stack pointer and program counter */
	m68ki_jump(this, 0);
	REG_SP(this) = m68ki_read_imm_32(this);
	REG_PC(this) = m68ki_read_imm_32(this);
	m68ki_jump(this, REG_PC(this));

	this->run_mode = RUN_MODE_NORMAL;

	this->c.current_cycle += this->cyc_exception[EXCEPTION_RESET];

}

/****************************************************************************
 * 8-bit data memory interface
 ****************************************************************************/

uint8_t m68ki_read_8(m68000_base_device *m68k, uint32_t address)
{
	address &= 0xFFFFFF;
	uint32_t base = address >> 16;
	if (m68k->read_pointers[base]) {
		uint8_t *chunk = m68k->read_pointers[base];
		return chunk[(address ^ 1) & 0xFFFF];
	}
	return read_byte(address, (void **)m68k->c.mem_pointers, &m68k->c.options->gen, &m68k->c);
}

void m68ki_write_8(m68000_base_device *m68k, uint32_t address, uint8_t value)
{
	address &= 0xFFFFFF;
	uint32_t base = address >> 16;
	if (m68k->write_pointers[base]) {
		uint8_t *chunk = m68k->write_pointers[base];
		chunk[(address ^ 1) & 0xFFFF] = value;
		return;
	}
	write_byte(address, value, (void **)m68k->c.mem_pointers, &m68k->c.options->gen, &m68k->c);
}

/****************************************************************************
 * 16-bit data memory interface
 ****************************************************************************/
 
uint16_t m68ki_read_16(m68000_base_device *m68k, uint32_t address)
{
	address &= 0xFFFFFF;
	uint32_t base = address >> 16;
	if (m68k->read_pointers[base]) {
		uint16_t *chunk = m68k->read_pointers[base];
		return chunk[address >> 1 & 0x7FFF];
	}
	return read_word(address, (void **)m68k->c.mem_pointers, &m68k->c.options->gen, &m68k->c);
}

void m68ki_write_16(m68000_base_device *m68k, uint32_t address, uint16_t value)
{
	address &= 0xFFFFFF;
	uint32_t base = address >> 16;
	if (m68k->write_pointers[base]) {
		uint16_t *chunk = m68k->read_pointers[base];
		chunk[address >> 1 & 0x7FFF] = value;
		return;
	}
	write_word(address, value, (void **)m68k->c.mem_pointers, &m68k->c.options->gen, &m68k->c);
}


/****************
 CPU Inits
****************/


void m68k_init_cpu_m68000(m68000_base_device *this)
{
	m68k_init_cpu_common(this);

	this->cpu_type         = CPU_TYPE_000;
//  dasm_type        = M68K_CPU_TYPE_68000;

	this->sr_mask          = 0xa71f; /* T1 -- S  -- -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
	this->jump_table       = m68ki_instruction_jump_table[0];
	uint8_t *tmp = malloc(sizeof(m68ki_cycles[0]));
	for (uint32_t i = 0; i < sizeof(m68ki_cycles[0]); i++)
	{
		tmp[i] = m68ki_cycles[0][i] * this->c.options->gen.clock_divider;
	}
	this->cyc_instruction  = tmp;
	tmp = malloc(sizeof(m68ki_exception_cycle_table[0]));
	for (uint32_t i = 0; i < sizeof(m68ki_exception_cycle_table[0]); i++)
	{
		tmp[i] = m68ki_exception_cycle_table[0][i] * this->c.options->gen.clock_divider;
	}
	this->cyc_exception    = tmp;
	this->cyc_bcc_notake_b = -2 * this->c.options->gen.clock_divider;
	this->cyc_bcc_notake_w = 2 * this->c.options->gen.clock_divider;
	this->cyc_dbcc_f_noexp = -2 * this->c.options->gen.clock_divider;
	this->cyc_dbcc_f_exp   = 2 * this->c.options->gen.clock_divider;
	this->cyc_scc_r_true   = 2 * this->c.options->gen.clock_divider;
	this->cyc_movem_w      = 2;// * this->c.options->gen.clock_divider;
	this->cyc_movem_l      = 3;// * this->c.options->gen.clock_divider;
	this->cyc_shift        = 1;// * this->c.options->gen.clock_divider;
	this->cyc_reset        = 132 * this->c.options->gen.clock_divider;
	this->int_mask = 7 << 8;
	this->c.status = m68ki_get_sr(this) >> 8;
	for (uint32_t address = 0; address < (24*1024*1024); address += 64*1024)
	{
		this->read_pointers[address >> 16] = NULL;
		this->write_pointers[address >> 16] = NULL;
		memmap_chunk const *chunk = find_map_chunk(address, &this->c.options->gen, 0, NULL);
		if (!chunk || chunk->end < (address + 64*1024) || (chunk->flags & (MMAP_ONLY_ODD | MMAP_ONLY_EVEN)) || !chunk->buffer) {
			continue;
		}
		void *ptr = get_native_pointer(address, (void **)this->c.mem_pointers, &this->c.options->gen);
		if (!ptr) {
			continue;
		}
		if (chunk->flags & MMAP_READ) {
			this->read_pointers[address >> 16] = ptr;
		}
		if (chunk->flags & MMAP_WRITE) {
			this->write_pointers[address >> 16] = ptr;
		}
	}
}

/* Service an interrupt request and start exception processing */
void m68ki_exception_interrupt(m68000_base_device *this, uint32_t int_level)
{
	uint32_t vector;
	uint32_t sr;
	uint32_t new_pc;

	if(CPU_TYPE_IS_000(this->cpu_type))
	{
		this->instr_mode = INSTRUCTION_NO;
	}

	/* Turn off the stopped state */
	this->stopped &= ~STOP_LEVEL_STOP;

	/* If we are halted, don't do anything */
	if(this->stopped)
		return;
		
	if (this->c.int_pending == 255) {
		this->c.int_pending = int_level;
		return;
	} else {
		int_level = this->c.int_pending;
	}

	/* Acknowledge the interrupt */
	this->c.int_ack = int_level;
	this->c.int_pending = 255;
	
	vector = M68K_INT_ACK_AUTOVECTOR;//int_ack_callback(*this, int_level);

	/* Get the interrupt vector */
	if(vector == M68K_INT_ACK_AUTOVECTOR) {
		/* Use the autovectors.  This is the most commonly used implementation */
		vector = EXCEPTION_INTERRUPT_AUTOVECTOR+int_level;
		uint32_t e_clock = this->c.current_cycle / this->c.options->gen.clock_divider;
		this->c.current_cycle += ((9-4) + e_clock % 10) * this->c.options->gen.clock_divider;
	} else if(vector == M68K_INT_ACK_SPURIOUS)
		/* Called if no devices respond to the interrupt acknowledge */
		vector = EXCEPTION_SPURIOUS_INTERRUPT;
	else if(vector > 255)
		return;

	/* Start exception processing */
	sr = m68ki_init_exception(this);

	/* Set the interrupt mask to the level of the one being serviced */
	this->int_mask = int_level<<8;

	/* Get the new PC */
	new_pc = m68ki_read_32(this, (vector<<2) /*+ vbr*/);

	/* If vector is uninitialized, call the uninitialized interrupt vector */
	if(new_pc == 0)
		new_pc = m68ki_read_32(this, (EXCEPTION_UNINITIALIZED_INTERRUPT<<2) /*+ vbr*/);

	/* Generate a stack frame */
	m68ki_stack_frame_0000(this, REG_PC(this), sr, vector);
	if(this->m_flag && CPU_TYPE_IS_EC020_PLUS(this->cpu_type))
	{
		/* Create throwaway frame */
		m68ki_set_sm_flag(this, this->s_flag);  /* clear M */
		sr |= 0x2000; /* Same as SR in master stack frame except S is forced high */
		m68ki_stack_frame_0001(this, REG_PC(this), sr, vector);
	}

	m68ki_jump(this, new_pc);

	/* Defer cycle counting until later */
	this->c.current_cycle += this->cyc_exception[vector];
}


