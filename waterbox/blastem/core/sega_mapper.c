#include "genesis.h"
#include "util.h"

uint16_t read_sram_w(uint32_t address, m68k_context * context)
{
	genesis_context * gen = context->system;
	address &= gen->save_ram_mask;
	switch(gen->save_type)
	{
	case RAM_FLAG_BOTH:
		return gen->save_storage[address] << 8 | gen->save_storage[address+1];
	case RAM_FLAG_EVEN:
		return gen->save_storage[address >> 1] << 8 | 0xFF;
	case RAM_FLAG_ODD:
		return gen->save_storage[address >> 1] | 0xFF00;
	}
	return 0xFFFF;//We should never get here
}

uint8_t read_sram_b(uint32_t address, m68k_context * context)
{
	genesis_context * gen = context->system;
	address &= gen->save_ram_mask;
	switch(gen->save_type)
	{
	case RAM_FLAG_BOTH:
		return gen->save_storage[address];
	case RAM_FLAG_EVEN:
		if (address & 1) {
			return 0xFF;
		} else {
			return gen->save_storage[address >> 1];
		}
	case RAM_FLAG_ODD:
		if (address & 1) {
			return gen->save_storage[address >> 1];
		} else {
			return 0xFF;
		}
	}
	return 0xFF;//We should never get here
}

m68k_context * write_sram_area_w(uint32_t address, m68k_context * context, uint16_t value)
{
	genesis_context * gen = context->system;
	if (gen->mapper_type == MAPPER_SEGA_MED_V2) {
		if (gen->bank_regs[8] & 0x20) {
			uint32_t bank = address >> 19;
			address &= 0x7FFFF;
			context->mem_pointers[gen->mapper_start_index + bank][address >> 1] = value;
		}
		return context;
	}
	if ((gen->bank_regs[0] & 0x3) == 1) {
		address &= gen->save_ram_mask;
		switch(gen->save_type)
		{
		case RAM_FLAG_BOTH:
			gen->save_storage[address] = value >> 8;
			gen->save_storage[address+1] = value;
			break;
		case RAM_FLAG_EVEN:
			gen->save_storage[address >> 1] = value >> 8;
			break;
		case RAM_FLAG_ODD:
			gen->save_storage[address >> 1] = value;
			break;
		}
	}
	return context;
}

m68k_context * write_sram_area_b(uint32_t address, m68k_context * context, uint8_t value)
{
	genesis_context * gen = context->system;
	if ((gen->bank_regs[0] & 0x3) == 1) {
		address &= gen->save_ram_mask;
		switch(gen->save_type)
		{
		case RAM_FLAG_BOTH:
			gen->save_storage[address] = value;
			break;
		case RAM_FLAG_EVEN:
			if (!(address & 1)) {
				gen->save_storage[address >> 1] = value;
			}
			break;
		case RAM_FLAG_ODD:
			if (address & 1) {
				gen->save_storage[address >> 1] = value;
			}
			break;
		}
	}
	return context;
}

static void* write_med_ram_w(uint32_t address, void *vcontext, uint16_t value, uint16_t bank)
{
	m68k_context *context = vcontext;
	genesis_context * gen = context->system;
	if (gen->bank_regs[8] & 0x20) {
		context->mem_pointers[gen->mapper_start_index + bank][address >> 1] = value;
		address += bank * 0x80000;
		m68k_invalidate_code_range(gen->m68k, address, address + 2);
	}
	return vcontext;
}

void* write_med_ram0_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 0);
}

void* write_med_ram1_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 1);
}

void* write_med_ram2_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 2);
}

void* write_med_ram3_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 3);
}

void* write_med_ram4_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 4);
}

void* write_med_ram5_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 5);
}

void* write_med_ram6_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 6);
}

void* write_med_ram7_w(uint32_t address, void *vcontext, uint16_t value)
{
	return write_med_ram_w(address, vcontext, value, 7);
}

static void* write_med_ram_b(uint32_t address, void *vcontext, uint8_t value, uint16_t bank)
{
	m68k_context *context = vcontext;
	genesis_context * gen = context->system;
	if (gen->bank_regs[8] & 0x20) {
		((uint8_t*)context->mem_pointers[gen->mapper_start_index + bank])[address ^ 1] = value;
		address += bank * 0x80000;
		m68k_invalidate_code_range(gen->m68k, address, address + 1);
	}
	return vcontext;
}

void* write_med_ram0_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 0);
}

void* write_med_ram1_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 1);
}

void* write_med_ram2_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 2);
}

void* write_med_ram3_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 3);
}

void* write_med_ram4_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 4);
}

void* write_med_ram5_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 5);
}

void* write_med_ram6_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 6);
}

void* write_med_ram7_b(uint32_t address, void *vcontext, uint8_t value)
{
	return write_med_ram_b(address, vcontext, value, 7);
}

m68k_context * write_bank_reg_w(uint32_t address, m68k_context * context, uint16_t value)
{
	genesis_context * gen = context->system;
	address &= 0xE;
	address >>= 1;
	if (!address) {
		if (gen->mapper_type == MAPPER_SEGA_MED_V2) {
			if (!value & 0x8000) {
				//writes without protection bit set are ignored
				return context;
			}
			gen->bank_regs[8] = value >> 8;
			void *new_ptr = gen->cart + 0x40000*(value & 0x1F);
			if (context->mem_pointers[gen->mapper_start_index] != new_ptr) {
				m68k_invalidate_code_range(gen->m68k, 0, 0x80000);
				context->mem_pointers[gen->mapper_start_index] = new_ptr;
			}
		} else if (value & 1) {
			//Used for games that only use the mapper for SRAM
			if (context->mem_pointers[gen->mapper_start_index]) {
				gen->mapper_temp = context->mem_pointers[gen->mapper_start_index];
			}
			context->mem_pointers[gen->mapper_start_index] = NULL;
			//For games that need more than 4MB
			for (int i = 4; i < 8; i++)
			{
				context->mem_pointers[gen->mapper_start_index + i] = NULL;
			}
		} else {
			//Used for games that only use the mapper for SRAM
			if (!context->mem_pointers[gen->mapper_start_index]) {
				context->mem_pointers[gen->mapper_start_index] = gen->mapper_temp;
			}
			//For games that need more than 4MB
			for (int i = 4; i < 8; i++)
			{
				context->mem_pointers[gen->mapper_start_index + i] = gen->cart + 0x40000*gen->bank_regs[i];
			}
		}
	} else if (gen->mapper_type != MAPPER_SEGA_SRAM) {
		uint32_t mask = ((gen->mapper_type == MAPPER_SEGA_MED_V2 ? (16 *1024 * 1024) : nearest_pow2(gen->header.info.rom_size)) >> 1) - 1;
		void *new_ptr = gen->cart + ((0x40000*value) & mask);
		if (context->mem_pointers[gen->mapper_start_index + address] != new_ptr) {
			m68k_invalidate_code_range(gen->m68k, address * 0x80000, (address + 1) * 0x80000);
			context->mem_pointers[gen->mapper_start_index + address] = new_ptr;
		}
	}
	gen->bank_regs[address] = value;
	return context;
}

m68k_context * write_bank_reg_b(uint32_t address, m68k_context * context, uint8_t value)
{
	genesis_context * gen = context->system;
	if (gen->mapper_type == MAPPER_SEGA_MED_V2) {
		address &= 0xF;
		if (!address) {
			//not sure if this is correct, possible byte sized writes are always rejected to $A130F0
			write_bank_reg_w(address, context, value << 8 | value);
		} else if (address > 2 && (address & 1)) {
			write_bank_reg_w(address, context, value);
		}
	} else if (address & 1) {
		write_bank_reg_w(address, context, value);
	}
	return context;
}

void sega_mapper_serialize(genesis_context *gen, serialize_buffer *buf)
{
	save_buffer8(buf, gen->bank_regs, gen->mapper_type == MAPPER_SEGA_MED_V2 ? sizeof(gen->bank_regs) : sizeof(gen->bank_regs) - 1);
}

void sega_mapper_deserialize(deserialize_buffer *buf, genesis_context *gen)
{
	if (gen->mapper_type == MAPPER_SEGA_MED_V2) {
		uint16_t reg0 = load_int8(buf);
		for (int i = 1; i < sizeof(gen->bank_regs) - 1; i++)
		{
			write_bank_reg_w(i * 2, gen->m68k, load_int8(buf));
		}
		reg0 |= load_int8(buf) << 8;
		write_bank_reg_w(0, gen->m68k, reg0);
	} else {
		for (int i = 0; i < sizeof(gen->bank_regs) - 1; i++)
		{
			write_bank_reg_w(i * 2, gen->m68k, load_int8(buf));
		}
	}
}
