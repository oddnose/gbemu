#include "rotate_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

struct InstructionResult op_bit_7_h(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	bool val = read_reg_8bit(state, RegH) >> 7;
	result.updates[0] = write_flag(state, ZFlag, !val);
	result.updates[1] = increase_pc(state, 2);
	result.cycles = 8;

	// TODO: sets flag H and resets N
	return result;
}

struct InstructionResult op_rl_c(struct State* state)
{
	struct InstructionResult result;

	unsigned char old_val = read_reg_8bit(state, RegC);
	unsigned char new_val = read_reg_8bit(state, RegC) << 1;

	result.num_memory_updates = 6;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegC, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, 0);
	result.updates[4] = write_flag(state, CFlag, (new_val & 0b10000000) >> 7);
	result.updates[5] = increase_pc(state, 2);
	result.cycles = 8;

	return result;
}

struct InstructionResult op_rla(struct State* state)
{
	struct InstructionResult result;

	unsigned char old_val = read_reg_8bit(state, RegA);
	unsigned char new_val = read_reg_8bit(state, RegA) << 1;

	result.num_memory_updates = 6;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, 0);
	result.updates[4] = write_flag(state, CFlag, (new_val & 0b10000000) >> 7);
	result.updates[5] = increase_pc(state, 1);
	result.cycles = 8;

	return result;
}


struct InstructionResult op_srl(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;

	bool c_flag;
	unsigned char new_val;
	if (reg == RegHL) {
		c_flag = read_addr(state, read_reg_16bit(state, RegHL)) & 0b00000001;
		new_val = read_reg_8bit(state, read_reg_16bit(state, RegHL)) >> 1;
		result.cycles = 16;
	} else {
		c_flag = read_reg_8bit(state, reg) & 0b00000001;
		new_val = read_reg_8bit(state, reg) >> 1;
		result.cycles = 8;
	}

	result.num_memory_updates = 6;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegA, new_val);
	result.updates[1] = write_flag(state, ZFlag, (new_val == 0));
	result.updates[2] = write_flag(state, NFlag, 0);
	result.updates[3] = write_flag(state, HFlag, 0);
	result.updates[4] = write_flag(state, CFlag, c_flag);
	result.updates[5] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_srl_a(struct State* state) { return op_srl(state, RegA); }
struct InstructionResult op_srl_b(struct State* state) { return op_srl(state, RegB); }
struct InstructionResult op_srl_c(struct State* state) { return op_srl(state, RegC); }
struct InstructionResult op_srl_d(struct State* state) { return op_srl(state, RegD); }
struct InstructionResult op_srl_e(struct State* state) { return op_srl(state, RegE); }
struct InstructionResult op_srl_h(struct State* state) { return op_srl(state, RegH); }
struct InstructionResult op_srl_l(struct State* state) { return op_srl(state, RegL); }
struct InstructionResult op_srl_hl_addr(struct State* state) { return op_srl(state, RegHL); }
