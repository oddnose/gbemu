#include "load_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>


struct InstructionResult load_u16_to_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_16bit(state, reg, read_short(state, read_reg_16bit(state, ProgramCounter) + 1));
	result.updates[1] = increase_pc(state, 3);

	return result;
}

struct InstructionResult op_ld_de_u16(struct State* state) { return load_u16_to_reg(state, RegDE); }
struct InstructionResult op_ld_hl_u16(struct State* state) { return load_u16_to_reg(state, RegHL); }
struct InstructionResult op_ld_sp_u16(struct State* state) { return load_u16_to_reg(state, StackPointer); }

struct InstructionResult load_u8_to_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, reg, read_short(state, read_reg_16bit(state, ProgramCounter) + 1));
	result.updates[1] = increase_pc(state, 2);

	return result;
}

struct InstructionResult op_ld_a_u8(struct State* state) { return load_u8_to_reg(state, RegA); }
struct InstructionResult op_ld_b_u8(struct State* state) { return load_u8_to_reg(state, RegB); }
struct InstructionResult op_ld_c_u8(struct State* state) { return load_u8_to_reg(state, RegC); }

struct InstructionResult op_ld_hld_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 3;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), read_reg_8bit(state, RegA));
	result.updates[1] = write_reg_16bit(state, RegHL, read_reg_16bit(state, RegHL) - 1);
	result.updates[2] = increase_pc(state, 1);

	return result;
}


struct InstructionResult op_ld_ff00_plus_c_a(struct State* state) 
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, 0xFF00 + read_reg_8bit(state, RegC), read_reg_8bit(state, RegA));
	result.updates[1] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_ld_hl_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), read_reg_8bit(state, RegA));
	result.updates[1] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_ld_ff00_plus_u8_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, 0xFF00 + read_addr(state, read_reg_16bit(state, ProgramCounter) + 1), read_reg_8bit(state, RegA));
	result.updates[1] = increase_pc(state, 2);

	return result;
}

struct InstructionResult load_reg_to_reg(struct State* state, enum MemoryLocation dest, enum MemoryLocation src)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, dest, read_reg_8bit(state, src));
	result.updates[1] = increase_pc(state, 1);
	return result;
}

struct InstructionResult op_ld_b_a(struct State* state) { return load_reg_to_reg(state, RegB, RegA); }
struct InstructionResult op_ld_c_a(struct State* state) { return load_reg_to_reg(state, RegC, RegA); }

struct InstructionResult op_ld_a_de(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegA, read_addr(state, read_reg_16bit(state, RegDE)));
	result.updates[1] = increase_pc(state, 1);
	return result;
}

