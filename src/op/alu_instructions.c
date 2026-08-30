#include "alu_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

struct InstructionResult op_xor_a_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 3;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegA, 0); // xor with itself will always be 0	
	result.updates[1] = write_flag(state, ZFlag, 1);
	result.updates[2] = increase_pc(state, 1);

	//TODO: also reset other flags
	return result;
}

struct InstructionResult op_inc_reg(struct State* state, enum MemoryLocation reg)
{
	unsigned char num_updates = 2;

	unsigned char inc_result;
	if (reg == RegHL) {
		unsigned char inc_result = read_char(state, read_reg_16bit(state, RegHL)) + 1;
	} else {
		inc_result = read_reg_8bit(state, reg) + 1;
	}

	if (inc_result == 0) {
		inc_result++;
	}

	struct InstructionResult result;
	result.num_memory_updates = num_updates;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	unsigned char update_count = 0;

	if (reg == RegHL) {
		result.updates[update_count++] = write_addr(state, read_reg_16bit(state, RegHL), inc_result); 
	} else {
		result.updates[update_count++] = write_reg_8bit(state, reg, inc_result); 
	}

	if (inc_result == 0) {
		result.updates[update_count++] = write_flag(state, ZFlag, 1);
	}

	result.updates[update_count++] = increase_pc(state, 1);

	//TODO: set h if carry from bit 3, reset n 
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
	result.num_memory_updates = num_updates;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	unsigned char update_count = 0;
	result.updates[update_count++] = write_reg_16bit(state, reg, inc_result); 

	if (inc_result == 0) {
		result.updates[update_count++] = write_flag(state, ZFlag, 1);
	}

	result.updates[update_count++] = increase_pc(state, 1);

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
	result.num_memory_updates = 4;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);

	unsigned char new_val;
	if (reg == RegHL) {
		new_val = read_addr(state, read_reg_16bit(state, RegHL)) - 1;
		result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), new_val); 
	} else {
		new_val = read_reg_8bit(state, reg) - 1;
		result.updates[0] = write_reg_8bit(state, reg, new_val); 
	}

	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 1);
	//TODO: set H if no borrow from bit 4
	result.updates[3] = increase_pc(state, 1);

	printf("dec res: %02x\n", read_reg_8bit(state, reg));

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

struct InstructionResult op_cp_a_uint8(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 3;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);

	unsigned char cp = read_reg_8bit(state, RegA) - read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);

	result.updates[0] = write_flag(state, ZFlag, (cp == 0));
	result.updates[1] = write_flag(state, NFlag, 1);
	//TODO: set H if no borrow from bit 4
	//TODO: set C if no borrow 
	result.updates[2] = increase_pc(state, 2);

	return result;
}
