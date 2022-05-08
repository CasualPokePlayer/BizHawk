#include "backend.h"
#include "gen_x86.h"
#include <string.h>

void cycles(cpu_options *opts, uint32_t num)
{
	if (opts->limit < 0) {
		sub_ir(&opts->code, num*opts->clock_divider, opts->cycles, SZ_D);
	} else {
		add_ir(&opts->code, num*opts->clock_divider, opts->cycles, SZ_D);
	}
}

void check_cycles_int(cpu_options *opts, uint32_t address)
{
	code_info *code = &opts->code;
	uint8_t cc;
	if (opts->limit < 0) {
		cmp_ir(code, 1, opts->cycles, SZ_D);
		cc = CC_NS;
	} else {
		cmp_rr(code, opts->cycles, opts->limit, SZ_D);
		cc = CC_A;
	}
	code_ptr jmp_off = code->cur+1;
	jcc(code, cc, jmp_off+1);
	mov_ir(code, address, opts->scratch1, SZ_D);
	call(code, opts->handle_cycle_limit_int);
	*jmp_off = code->cur - (jmp_off+1);
}

void retranslate_calc(cpu_options *opts)
{
	code_info *code = &opts->code;
	code_info tmp = *code;
	uint8_t cc;
	if (opts->limit < 0) {
		cmp_ir(code, 1, opts->cycles, SZ_D);
		cc = CC_NS;
	} else {
		cmp_rr(code, opts->cycles, opts->limit, SZ_D);
		cc = CC_A;
	}
	jcc(code, cc, code->cur+2);
	opts->move_pc_off = code->cur - tmp.cur;
	mov_ir(code, 0x1234, opts->scratch1, SZ_D);
	opts->move_pc_size = code->cur - tmp.cur - opts->move_pc_off;
	*code = tmp;
}

void patch_for_retranslate(cpu_options *opts, code_ptr native_address, code_ptr handler)
{
	if (!is_mov_ir(native_address)) {
		//instruction is not already patched for either retranslation or a breakpoint
		//copy original mov_ir instruction containing PC to beginning of native code area
		memmove(native_address, native_address + opts->move_pc_off, opts->move_pc_size);
	}
	//jump to the retranslation handler
	code_info tmp = {
		.cur =  native_address + opts->move_pc_size,
		.last = native_address + 256,
		.stack_off = 0
	};
	jmp(&tmp, handler);
}

void defer_translation(cpu_options *opts, uint32_t address, code_ptr handler)
{
	mov_ir(&opts->code, address, opts->scratch1, SZ_D);
	jmp(&opts->code, handler);
}

void check_cycles(cpu_options * opts)
{
	code_info *code = &opts->code;
	uint8_t cc;
	if (opts->limit < 0) {
		cmp_ir(code, 1, opts->cycles, SZ_D);
		cc = CC_NS;
	} else {
		cmp_rr(code, opts->cycles, opts->limit, SZ_D);
		cc = CC_A;
	}
	check_alloc_code(code, MAX_INST_LEN*2);
	code_ptr jmp_off = code->cur+1;
	jcc(code, cc, jmp_off+1);
	call(code, opts->handle_cycle_limit);
	*jmp_off = code->cur - (jmp_off+1);
}

void log_address(cpu_options *opts, uint32_t address, char * format)
{
	code_info *code = &opts->code;
	call(code, opts->save_context);
	push_r(code, opts->context_reg);
	mov_rr(code, opts->cycles, RDX, SZ_D);
	mov_ir(code, (int64_t)format, RDI, SZ_PTR);
	mov_ir(code, address, RSI, SZ_D);
	call_args_abi(code, (code_ptr)printf, 3, RDI, RSI, RDX);
	pop_r(code, opts->context_reg);
	call(code, opts->load_context);
}

void check_code_prologue(code_info *code)
{
	check_alloc_code(code, MAX_INST_LEN*4);
}

code_ptr gen_mem_fun(cpu_options * opts, memmap_chunk const * memmap, uint32_t num_chunks, ftype fun_type, code_ptr *after_inc)
{
	code_info *code = &opts->code;
	code_ptr start = code->cur;
	check_cycles(opts);
	uint8_t is_write = fun_type == WRITE_16 || fun_type == WRITE_8;
	uint8_t adr_reg = is_write ? opts->scratch2 : opts->scratch1;
	uint8_t size =  (fun_type == READ_16 || fun_type == WRITE_16) ? SZ_W : SZ_B;
	if (size != SZ_B && opts->align_error_mask) {
		test_ir(code, opts->align_error_mask, adr_reg, SZ_D);
		jcc(code, CC_NZ, is_write ? opts->handle_align_error_write : opts->handle_align_error_read);
	}
	cycles(opts, opts->bus_cycles);
	if (after_inc) {
		*after_inc = code->cur;
	}

	if (opts->address_size == SZ_D && opts->address_mask != 0xFFFFFFFF) {
		and_ir(code, opts->address_mask, adr_reg, SZ_D);
	} else if (opts->address_size == SZ_W && opts->address_mask != 0xFFFF) {
		and_ir(code, opts->address_mask, adr_reg, SZ_W);
	}
	code_ptr lb_jcc = NULL, ub_jcc = NULL;
	uint16_t access_flag = is_write ? MMAP_WRITE : MMAP_READ;
	uint32_t ram_flags_off = opts->ram_flags_off;
	uint32_t min_address = 0;
	uint32_t max_address = opts->max_address;
	uint8_t need_wide_jcc = 0;
	for (uint32_t chunk = 0; chunk < num_chunks; chunk++)
	{
		code_info chunk_start = *code;
		if (memmap[chunk].start > min_address) {
			cmp_ir(code, memmap[chunk].start, adr_reg, opts->address_size);
			lb_jcc = code->cur + 1;
			if (need_wide_jcc) {
				jcc(code, CC_C, code->cur + 130);
				lb_jcc++;
			} else {
				jcc(code, CC_C, code->cur + 2);
			}
		} else {
			min_address = memmap[chunk].end;
		}
		if (memmap[chunk].end < max_address) {
			cmp_ir(code, memmap[chunk].end, adr_reg, opts->address_size);
			ub_jcc = code->cur + 1;
			if (need_wide_jcc) {
				jcc(code, CC_NC, code->cur + 130);
				ub_jcc++;
			} else {
				jcc(code, CC_NC, code->cur + 2);
			}
		} else {
			max_address = memmap[chunk].start;
		}

		if (memmap[chunk].mask != opts->address_mask) {
			and_ir(code, memmap[chunk].mask, adr_reg, opts->address_size);
		}
		code_ptr after_normal = NULL;
		uint8_t need_addr_pop = 0;
		if (size == SZ_B && memmap[chunk].shift != 0) {
			if (is_write && (memmap[chunk].flags & MMAP_CODE)) {
				push_r(code, adr_reg);
				need_addr_pop = 1;
			}
			btr_ir(code, 0, adr_reg, opts->address_size);
			code_ptr normal = code->cur+1;
			jcc(code, CC_NC, normal);
			if (memmap[chunk].shift > 0) {
				shl_ir(code, memmap[chunk].shift, adr_reg, opts->address_size);
			} else {
				shr_ir(code, -memmap[chunk].shift, adr_reg, opts->address_size);
			}
			or_ir(code, 1, adr_reg, opts->address_size);
			after_normal = code->cur + 1;
			jmp(code, after_normal);
			*normal = code->cur - (normal + 1);
		}
		if (memmap[chunk].shift > 0) {
			if (!need_addr_pop && is_write && (memmap[chunk].flags & MMAP_CODE)) {
				push_r(code, adr_reg);
				need_addr_pop = 1;
			}
			shl_ir(code, memmap[chunk].shift, adr_reg, opts->address_size);
		} else if (memmap[chunk].shift < 0) {
			if (!need_addr_pop && is_write && (memmap[chunk].flags & MMAP_CODE)) {
				push_r(code, adr_reg);
				need_addr_pop = 1;
			}
			shr_ir(code, -memmap[chunk].shift, adr_reg, opts->address_size);
		}
		if (after_normal) {
			*after_normal = code->cur - (after_normal + 1);
		}
		void * cfun;
		switch (fun_type)
		{
		case READ_16:
			cfun = memmap[chunk].read_16;
			break;
		case READ_8:
			cfun = memmap[chunk].read_8;
			break;
		case WRITE_16:
			cfun = memmap[chunk].write_16;
			break;
		case WRITE_8:
			cfun = memmap[chunk].write_8;
			break;
		default:
			cfun = NULL;
		}
		if(memmap[chunk].flags & access_flag) {
			if (memmap[chunk].flags & MMAP_PTR_IDX) {
				if (memmap[chunk].flags & MMAP_FUNC_NULL) {
					cmp_irdisp(code, 0, opts->context_reg, opts->mem_ptr_off + sizeof(void*) * memmap[chunk].ptr_index, SZ_PTR);
					code_ptr not_null = code->cur + 1;
					jcc(code, CC_NZ, code->cur + 2);
					call(code, opts->save_context);
					if (is_write) {
						call_args_abi(code, cfun, 3, opts->scratch2, opts->context_reg, opts->scratch1);
						mov_rr(code, RAX, opts->context_reg, SZ_PTR);
					} else {
						push_r(code, opts->context_reg);
						call_args_abi(code, cfun, 2, opts->scratch1, opts->context_reg);
						pop_r(code, opts->context_reg);
						mov_rr(code, RAX, opts->scratch1, size);
					}
					jmp(code, opts->load_context);

					*not_null = code->cur - (not_null + 1);
				}
				if ((opts->byte_swap || memmap[chunk].flags & MMAP_BYTESWAP) && size == SZ_B) {
					xor_ir(code, 1, adr_reg, opts->address_size);
				}
				if (opts->address_size != SZ_D) {
					movzx_rr(code, adr_reg, adr_reg, opts->address_size, SZ_D);
				}
				if (!need_addr_pop && is_write && (memmap[chunk].flags & MMAP_CODE)) {
					push_r(code, adr_reg);
					need_addr_pop = 1;
				}
				add_rdispr(code, opts->context_reg, opts->mem_ptr_off + sizeof(void*) * memmap[chunk].ptr_index, adr_reg, SZ_PTR);
				if (is_write) {
					mov_rrind(code, opts->scratch1, opts->scratch2, size);
				} else {
					mov_rindr(code, opts->scratch1, opts->scratch1, size);
				}
			} else {
				uint8_t tmp_size = size;
				if (size == SZ_B) {
					if ((memmap[chunk].flags & MMAP_ONLY_ODD) || (memmap[chunk].flags & MMAP_ONLY_EVEN)) {
						bt_ir(code, 0, adr_reg, opts->address_size);
						code_ptr good_addr = code->cur + 1;
						jcc(code, (memmap[chunk].flags & MMAP_ONLY_ODD) ? CC_C : CC_NC, code->cur + 2);
						if (!is_write) {
							mov_ir(code, 0xFF, opts->scratch1, SZ_B);
						}
						retn(code);
						*good_addr = code->cur - (good_addr + 1);
						shr_ir(code, 1, adr_reg, opts->address_size);
					} else if (opts->byte_swap || memmap[chunk].flags & MMAP_BYTESWAP) {
						xor_ir(code, 1, adr_reg, opts->address_size);
					}
				} else if ((memmap[chunk].flags & MMAP_ONLY_ODD) || (memmap[chunk].flags & MMAP_ONLY_EVEN)) {
					tmp_size = SZ_B;
					shr_ir(code, 1, adr_reg, opts->address_size);
					if ((memmap[chunk].flags & MMAP_ONLY_EVEN) && is_write) {
						shr_ir(code, 8, opts->scratch1, SZ_W);
					}
				}
				if (opts->address_size != SZ_D) {
					movzx_rr(code, adr_reg, adr_reg, opts->address_size, SZ_D);
				}
				if ((intptr_t)memmap[chunk].buffer <= 0x7FFFFFFF && (intptr_t)memmap[chunk].buffer >= -2147483648) {
					if (is_write) {
						mov_rrdisp(code, opts->scratch1, opts->scratch2, (intptr_t)memmap[chunk].buffer, tmp_size);
					} else {
						mov_rdispr(code, opts->scratch1, (intptr_t)memmap[chunk].buffer, opts->scratch1, tmp_size);
					}
				} else {
					if (is_write) {
						push_r(code, opts->scratch2);
						mov_ir(code, (intptr_t)memmap[chunk].buffer, opts->scratch2, SZ_PTR);
						add_rdispr(code, RSP, 0, opts->scratch2, SZ_PTR);
						mov_rrind(code, opts->scratch1, opts->scratch2, tmp_size);
						if (is_write && (memmap[chunk].flags & MMAP_CODE)) {
							need_addr_pop = 1;
						} else {
							add_ir(code, sizeof(void*), RSP, SZ_PTR);
							code->stack_off -= sizeof(void *);
						}
					} else {
						push_r(code, opts->scratch2);
						mov_ir(code, (intptr_t)memmap[chunk].buffer, opts->scratch2, SZ_PTR);
						mov_rindexr(code, opts->scratch2, opts->scratch1, 1, opts->scratch1, tmp_size);
						pop_r(code, opts->scratch2);
					}
				}
				if (size != tmp_size && !is_write) {
					if (memmap[chunk].flags & MMAP_ONLY_EVEN) {
						shl_ir(code, 8, opts->scratch1, SZ_W);
						mov_ir(code, 0xFF, opts->scratch1, SZ_B);
					} else {
						or_ir(code, 0xFF00, opts->scratch1, SZ_W);
					}
				}
			}
			if (is_write && (memmap[chunk].flags & MMAP_CODE)) {
				if (need_addr_pop) {
					pop_r(code, adr_reg);
				}
				mov_rr(code, opts->scratch2, opts->scratch1, opts->address_size);
				shr_ir(code, opts->ram_flags_shift, opts->scratch1, opts->address_size);
				bt_rrdisp(code, opts->scratch1, opts->context_reg, ram_flags_off, opts->address_size);
				code_ptr not_code = code->cur + 1;
				jcc(code, CC_NC, code->cur + 2);
				if (memmap[chunk].mask != opts->address_mask) {
					or_ir(code, memmap[chunk].start, opts->scratch2, opts->address_size);
				}
				call(code, opts->save_context);
				call_args(code, opts->handle_code_write, 2, opts->scratch2, opts->context_reg);
				mov_rr(code, RAX, opts->context_reg, SZ_PTR);
				jmp(code, opts->load_context);
				*not_code = code->cur - (not_code+1);
			}
			retn(code);
		} else if (cfun) {
			call(code, opts->save_context);
			if (is_write) {
				call_args_abi(code, cfun, 3, opts->scratch2, opts->context_reg, opts->scratch1);
				mov_rr(code, RAX, opts->context_reg, SZ_PTR);
			} else {
				push_r(code, opts->context_reg);
				call_args_abi(code, cfun, 2, opts->scratch1, opts->context_reg);
				pop_r(code, opts->context_reg);
				mov_rr(code, RAX, opts->scratch1, size);
			}
			jmp(code, opts->load_context);
		} else {
			//Not sure the best course of action here
			if (!is_write) {
				mov_ir(code, size == SZ_B ? 0xFF : 0xFFFF, opts->scratch1, size);
			}
			retn(code);
		}
		if (lb_jcc) {
			if (need_wide_jcc) {
				*((int32_t*)lb_jcc) = code->cur - (lb_jcc+4);
			} else if (code->cur - (lb_jcc+1) > 0x7f) {
				need_wide_jcc = 1;
				chunk--;
				*code = chunk_start;
				continue;
			} else {
				*lb_jcc = code->cur - (lb_jcc+1);
			}
			lb_jcc = NULL;
		}
		if (ub_jcc) {
			if (need_wide_jcc) {
				*((int32_t*)ub_jcc) = code->cur - (ub_jcc+4);
			} else if (code->cur - (ub_jcc+1) > 0x7f) {
				need_wide_jcc = 1;
				chunk--;
				*code = chunk_start;
				continue;
			} else {
				*ub_jcc = code->cur - (ub_jcc+1);
			}

			ub_jcc = NULL;
		}
		if (memmap[chunk].flags & MMAP_CODE) {
			uint32_t size = chunk_size(opts, memmap + chunk);
			uint32_t size_round_mask = (1 << (opts->ram_flags_shift + 3)) - 1;
			if (size & size_round_mask) {
				size &= ~size_round_mask;
				size += size_round_mask + 1;
			}
			ram_flags_off += size >> (opts->ram_flags_shift + 3);
		}
		if (need_wide_jcc) {
			need_wide_jcc = 0;
		}
	}
	if (!is_write) {
		mov_ir(code, size == SZ_B ? 0xFF : 0xFFFF, opts->scratch1, size);
	}
	retn(code);
	return start;
}
