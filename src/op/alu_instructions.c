#include "alu_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

struct InstructionResult op_inc_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char inc_result;
	if (reg == RegHL) {
		inc_result = read_char(state, read_reg_16bit(state, RegHL)) + 1;
		result.cycles = 12;
	} else {
		inc_result = read_reg_8bit(state, reg) + 1;
		result.cycles = 4;
	}

	if (reg == RegHL) {
		result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), inc_result); 
	} else {
		result.updates[0] = write_reg_8bit(state, reg, inc_result); 
	}

	result.updates[1] = write_flag(state, ZFlag, (inc_result == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, (inc_result & 0x0F) == 0x00); 
	result.updates[4] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_inc_a(struct State* state) { return op_inc_reg(state, RegA); }
struct InstructionResult op_inc_b(struct State* state) { return op_inc_reg(state, RegB); }
struct InstructionResult op_inc_c(struct State* state) { return op_inc_reg(state, RegC); }
struct InstructionResult op_inc_d(struct State* state) { return op_inc_reg(state, RegD); }
struct InstructionResult op_inc_e(struct State* state) { return op_inc_reg(state, RegE); }
struct InstructionResult op_inc_h(struct State* state) { return op_inc_reg(state, RegH); }
struct InstructionResult op_inc_l(struct State* state) { return op_inc_reg(state, RegL); }
struct InstructionResult op_inc_hl_addr(struct State* state) { return op_inc_reg(state, RegHL); }

struct InstructionResult op_inc_reg_16bit(struct State* state, enum MemoryLocation reg)
{
	unsigned char num_updates = 2;
	unsigned short inc_result = read_reg_16bit(state, reg) + 1;

	if (inc_result == 0) {
		inc_result++;
	}

	struct InstructionResult result;
	unsigned char update_count = 0;
	result.updates[update_count++] = write_reg_16bit(state, reg, inc_result); 

	if (inc_result == 0) {
		result.updates[update_count++] = write_flag(state, ZFlag, 1);
	}

	result.updates[update_count++] = increase_pc(state, 1);
	result.cycles = 8;

	//TODO: set h if carry from bit 3, reset n 
	return result;
}

struct InstructionResult op_inc_bc(struct State* state) { return op_inc_reg_16bit(state, RegBC); }
struct InstructionResult op_inc_de(struct State* state) { return op_inc_reg_16bit(state, RegDE); }
struct InstructionResult op_inc_hl(struct State* state) { return op_inc_reg_16bit(state, RegHL); }
struct InstructionResult op_inc_sp(struct State* state) { return op_inc_reg_16bit(state, StackPointer); }

struct InstructionResult dec_reg_8bit(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char new_val;
	if (reg == RegHL) {
		new_val = read_addr(state, read_reg_16bit(state, RegHL)) - 1;
		result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), new_val); 
		result.cycles = 12;
	} else {
		new_val = read_reg_8bit(state, reg) - 1;
		result.updates[0] = write_reg_8bit(state, reg, new_val); 
		result.cycles = 4;
	}

	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 1);
	result.updates[3] = write_flag(state, HFlag, (new_val & 0x0F) == 0x0F);
	result.updates[4] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_dec_a(struct State* state) { return dec_reg_8bit(state, RegA); }
struct InstructionResult op_dec_b(struct State* state) { return dec_reg_8bit(state, RegB); }
struct InstructionResult op_dec_c(struct State* state) { return dec_reg_8bit(state, RegC); }
struct InstructionResult op_dec_d(struct State* state) { return dec_reg_8bit(state, RegD); }
struct InstructionResult op_dec_e(struct State* state) { return dec_reg_8bit(state, RegE); }
struct InstructionResult op_dec_h(struct State* state) { return dec_reg_8bit(state, RegH); }
struct InstructionResult op_dec_l(struct State* state) { return dec_reg_8bit(state, RegL); }
struct InstructionResult op_dec_hl_addr(struct State* state) { return dec_reg_8bit(state, RegHL); }


struct InstructionResult sub_a_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char reg_val;
	if (reg == RegHL) {
		reg_val = read_addr(state, read_reg_16bit(state, RegHL));
		result.cycles = 8;
	} else {
		reg_val = read_addr(state, read_reg_8bit(state, reg));
		result.cycles = 4;
	}
	unsigned char new_val = a_val - reg_val;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 1);
	result.updates[3] = write_flag(state, CFlag, a_val < reg_val);
	result.updates[4] = write_flag(state, HFlag, (a_val & 0x0F) < (reg_val & 0x0F));
	result.updates[5] = increase_pc(state, 1);

	return result;

}

struct InstructionResult op_sub_a_a(struct State* state) { return sub_a_reg(state, RegA); }
struct InstructionResult op_sub_a_b(struct State* state) { return sub_a_reg(state, RegB); }
struct InstructionResult op_sub_a_c(struct State* state) { return sub_a_reg(state, RegC); }
struct InstructionResult op_sub_a_d(struct State* state) { return sub_a_reg(state, RegD); }
struct InstructionResult op_sub_a_e(struct State* state) { return sub_a_reg(state, RegE); }
struct InstructionResult op_sub_a_h(struct State* state) { return sub_a_reg(state, RegH); }
struct InstructionResult op_sub_a_l(struct State* state) { return sub_a_reg(state, RegL); }
struct InstructionResult op_sub_a_hl_addr(struct State* state) { return sub_a_reg(state, RegHL); }

struct InstructionResult op_sub_a_u8(struct State* state)
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char u8_val = read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);
	unsigned char new_val = a_val - u8_val;
	result.cycles = 8;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 1);
	result.updates[3] = write_flag(state, CFlag, a_val < u8_val);
	result.updates[4] = write_flag(state, HFlag, (a_val & 0x0F) < (u8_val & 0x0F));
	result.updates[5] = increase_pc(state, 2);

	return result;
}

struct InstructionResult op_cp_a_uint8(struct State* state)
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char u8_val = read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);
	unsigned char cp = a_val - u8_val;

	result.updates[0] = write_flag(state, ZFlag, (cp == 0));
	result.updates[1] = write_flag(state, NFlag, 1);
	result.updates[2] = write_flag(state, CFlag, a_val < u8_val);
	result.updates[3] = write_flag(state, HFlag, (a_val & 0x0F) < (u8_val & 0x0F));
	result.updates[4] = increase_pc(state, 2);
	result.cycles = 8;

	return result;
}

struct InstructionResult cp_a_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char reg_val;
	if (reg == RegHL) {
		reg_val = read_addr(state, read_reg_16bit(state, RegHL));
		result.cycles = 8;
	} else {
		reg_val = read_reg_8bit(state, reg);
		result.cycles = 4;
	}
	unsigned char cp = a_val - reg_val;

	result.updates[0] = write_flag(state, ZFlag, (cp == 0));
	result.updates[1] = write_flag(state, NFlag, 1);
	result.updates[2] = write_flag(state, CFlag, a_val < reg_val);
	result.updates[3] = write_flag(state, HFlag, (a_val & 0x0F) < (reg_val & 0x0F));
	result.updates[4] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_cp_a_a(struct State* state) { return cp_a_reg(state, RegA); }
struct InstructionResult op_cp_a_b(struct State* state) { return cp_a_reg(state, RegB); }
struct InstructionResult op_cp_a_c(struct State* state) { return cp_a_reg(state, RegC); }
struct InstructionResult op_cp_a_d(struct State* state) { return cp_a_reg(state, RegD); }
struct InstructionResult op_cp_a_e(struct State* state) { return cp_a_reg(state, RegE); }
struct InstructionResult op_cp_a_h(struct State* state) { return cp_a_reg(state, RegH); }
struct InstructionResult op_cp_a_l(struct State* state) { return cp_a_reg(state, RegL); }
struct InstructionResult op_cp_a_hl_addr(struct State* state) { return cp_a_reg(state, RegHL); }

struct InstructionResult add_a_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char reg_val;
	if (reg == RegHL) {
		reg_val = read_addr(state, read_reg_16bit(state, RegHL));
		result.cycles = 8;
	} else {
		reg_val = read_reg_8bit(state, reg);
		result.cycles = 4;
	}
	unsigned char new_val = a_val + reg_val;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, CFlag, ((unsigned short) a_val + reg_val) > 0xFF);
	result.updates[4] = write_flag(state, HFlag, ((a_val & 0x0F) + (reg_val & 0x0F)) > 0x0F);
	result.updates[5] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_add_a_a(struct State* state) { return add_a_reg(state, RegA); }
struct InstructionResult op_add_a_b(struct State* state) { return add_a_reg(state, RegB); }
struct InstructionResult op_add_a_c(struct State* state) { return add_a_reg(state, RegC); }
struct InstructionResult op_add_a_d(struct State* state) { return add_a_reg(state, RegD); }
struct InstructionResult op_add_a_e(struct State* state) { return add_a_reg(state, RegE); }
struct InstructionResult op_add_a_h(struct State* state) { return add_a_reg(state, RegH); }
struct InstructionResult op_add_a_l(struct State* state) { return add_a_reg(state, RegL); }
struct InstructionResult op_add_a_hl_addr(struct State* state) { return add_a_reg(state, RegHL); }

struct InstructionResult op_add_a_u8(struct State* state)
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char u8_val = read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);
	unsigned char new_val = a_val + u8_val;
	result.cycles = 8;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, CFlag, ((unsigned short) a_val + u8_val) > 0xFF);
	result.updates[4] = write_flag(state, HFlag, ((a_val & 0x0F) + (u8_val & 0x0F)) > 0x0F);
	result.updates[5] = increase_pc(state, 2);

	return result;
}

struct InstructionResult add_hl_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned short hl_val = read_reg_16bit(state, RegHL);
	unsigned short reg_val = read_reg_16bit(state, reg);
	result.cycles = 8;
	unsigned short new_val = hl_val + reg_val;

	result.updates[0] = write_reg_16bit(state, RegHL, new_val);
	result.updates[1] = write_flag(state, NFlag, 0);
	result.updates[2] = write_flag(state, CFlag, ((unsigned long) hl_val + reg_val) > 0xFFFF);
	result.updates[3] = write_flag(state, HFlag, ((hl_val & 0x0FFF) + (reg_val & 0x0FFF)) > 0x0FFF);
	result.updates[4] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_add_hl_bc(struct State* state) { return add_hl_reg(state, RegBC); }
struct InstructionResult op_add_hl_de(struct State* state) { return add_hl_reg(state, RegDE); }
struct InstructionResult op_add_hl_hl(struct State* state) { return add_hl_reg(state, RegHL); }
struct InstructionResult op_add_hl_sp(struct State* state) { return add_hl_reg(state, StackPointer); }

struct InstructionResult adc_a_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	bool c_flag = read_flag(state, CFlag);
	unsigned char reg_val;
	if (reg == RegHL) {
		reg_val = read_addr(state, read_reg_16bit(state, RegHL));
		result.cycles = 8;
	} else {
		reg_val = read_reg_8bit(state, reg);
		result.cycles = 4;
	}

	unsigned char new_val = a_val + reg_val + c_flag;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, CFlag, ((unsigned short) a_val + reg_val + c_flag) > 0xFF);
	result.updates[4] = write_flag(state, HFlag, (c_flag + (a_val & 0x0F) + (reg_val & 0x0F)) > 0x0F);
	result.updates[5] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_adc_a_a(struct State* state) { return adc_a_reg(state, RegA); }
struct InstructionResult op_adc_a_b(struct State* state) { return adc_a_reg(state, RegB); }
struct InstructionResult op_adc_a_c(struct State* state) { return adc_a_reg(state, RegC); }
struct InstructionResult op_adc_a_d(struct State* state) { return adc_a_reg(state, RegD); }
struct InstructionResult op_adc_a_e(struct State* state) { return adc_a_reg(state, RegE); }
struct InstructionResult op_adc_a_h(struct State* state) { return adc_a_reg(state, RegH); }
struct InstructionResult op_adc_a_l(struct State* state) { return adc_a_reg(state, RegL); }
struct InstructionResult op_adc_a_hl_addr(struct State* state) { return adc_a_reg(state, RegHL); }

struct InstructionResult op_adc_a_u8(struct State* state) 
{
	struct InstructionResult result;

	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char u8_val = read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);
	bool c_flag = read_flag(state, CFlag);
	unsigned char new_val = a_val + u8_val + c_flag;
	result.cycles = 8;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, CFlag, ((unsigned short) a_val + u8_val + c_flag) > 0xFF);
	result.updates[4] = write_flag(state, HFlag, (c_flag + (a_val & 0x0F) + (u8_val & 0x0F)) > 0x0F);
	result.updates[5] = increase_pc(state, 2);

	return result;
}

struct InstructionResult or_a_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char new_val;
	if (reg == RegHL) {
		new_val = read_reg_8bit(state, RegA) | read_addr(state, read_reg_16bit(state, RegHL));
		result.cycles = 8;
	} else {
		new_val = read_reg_8bit(state, RegA) | read_reg_8bit(state, reg);
		result.cycles = 4;
	}

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, 0);
	result.updates[4] = write_flag(state, CFlag, 0);
	result.updates[5] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_or_a_a(struct State* state) { return or_a_reg(state, RegA); }
struct InstructionResult op_or_a_b(struct State* state) { return or_a_reg(state, RegB); }
struct InstructionResult op_or_a_c(struct State* state) { return or_a_reg(state, RegC); }
struct InstructionResult op_or_a_d(struct State* state) { return or_a_reg(state, RegD); }
struct InstructionResult op_or_a_e(struct State* state) { return or_a_reg(state, RegE); }
struct InstructionResult op_or_a_h(struct State* state) { return or_a_reg(state, RegH); }
struct InstructionResult op_or_a_l(struct State* state) { return or_a_reg(state, RegL); }
struct InstructionResult op_or_a_hl_addr(struct State* state) { return or_a_reg(state, RegHL); }

struct InstructionResult xor_a_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	unsigned char new_val;
	if (reg == RegHL) {
		new_val = read_reg_8bit(state, RegA) ^ read_addr(state, read_reg_16bit(state, RegHL));
		result.cycles = 8;
	} else {
		new_val = read_reg_8bit(state, RegA) ^ read_reg_8bit(state, reg);
		result.cycles = 4;
	}

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, 0);
	result.updates[4] = write_flag(state, CFlag, 0);
	result.updates[5] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_xor_a_a(struct State* state) { return xor_a_reg(state, RegA); }
struct InstructionResult op_xor_a_b(struct State* state) { return xor_a_reg(state, RegB); }
struct InstructionResult op_xor_a_c(struct State* state) { return xor_a_reg(state, RegC); }
struct InstructionResult op_xor_a_d(struct State* state) { return xor_a_reg(state, RegD); }
struct InstructionResult op_xor_a_e(struct State* state) { return xor_a_reg(state, RegE); }
struct InstructionResult op_xor_a_h(struct State* state) { return xor_a_reg(state, RegH); }
struct InstructionResult op_xor_a_l(struct State* state) { return xor_a_reg(state, RegL); }
struct InstructionResult op_xor_a_hl_addr(struct State* state) { return xor_a_reg(state, RegHL); }

struct InstructionResult op_xor_a_u8(struct State* state)
{
	struct InstructionResult result;

	unsigned char new_val = read_reg_8bit(state, RegA) ^ read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);
	result.cycles = 8;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, 0);
	result.updates[4] = write_flag(state, CFlag, 0);
	result.updates[5] = increase_pc(state, 2);

	return result;


}

struct InstructionResult op_and_a_u8(struct State* state)
{
	struct InstructionResult result;

	unsigned char new_val;
	new_val = read_reg_8bit(state, RegA) & read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);
	result.cycles = 4;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, 1);
	result.updates[4] = write_flag(state, CFlag, 0);
	result.updates[5] = increase_pc(state, 2);

	return result;
}

// To understand this better, see: https://blog.ollien.com/posts/gb-daa/
struct InstructionResult op_daa(struct State* state)
{
	struct InstructionResult result;

	bool subtracting = read_flag(state, NFlag);
	bool half_carry = read_flag(state, HFlag);
	bool carry = read_flag(state, CFlag);
	unsigned char a_val = read_reg_8bit(state, RegA);
	unsigned char offset = 0;
	unsigned char new_val = 0;

	if (subtracting) {
		if (half_carry) {
			offset |= 0x06;
		}
		if (carry) {
			offset |= 0x60;
		}
		new_val = a_val - offset;

	} else {

		if ((a_val & 0xF) > 0x09 || half_carry) {
			offset |= 0x06;
		}
		if (a_val > 0x99 || carry) {
			offset |= 0x60;
			carry = true;
		}
		new_val = a_val + offset;
	} 

	result.cycles = 4;

	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, HFlag, 0);
	result.updates[3] = write_flag(state, CFlag, carry);
	result.updates[4] = increase_pc(state, 1);

	return result;

}
