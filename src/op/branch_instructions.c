#include "branch_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdint.h>
#include <stdlib.h>

struct InstructionResult op_jr_i8(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 1;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_16bit(state, ProgramCounter, read_reg_16bit(state, ProgramCounter) + (char) read_char(state, read_reg_16bit(state, ProgramCounter) + 1) + 2); // 2 = length of instruction

	return result;
}

struct InstructionResult op_jr_nz_i8(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 1;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	if (!read_flag(state, ZFlag)) {
		result.updates[0] = write_reg_16bit(state, ProgramCounter, read_reg_16bit(state, ProgramCounter) + (char) read_char(state, read_reg_16bit(state, ProgramCounter) + 1) + 2); // 2 = length of instruction
	} else {
		result.updates[0] = increase_pc(state, 2);
	}

	return result;
}

struct InstructionResult op_jr_z_i8(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 1;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	if (read_flag(state, ZFlag)) {
		result.updates[0] = write_reg_16bit(state, ProgramCounter, read_reg_16bit(state, ProgramCounter) + (char) read_char(state, read_reg_16bit(state, ProgramCounter) + 1) + 2); // 2 = length of instruction
	} else {
		result.updates[0] = increase_pc(state, 2);
	}

	return result;
}

struct InstructionResult op_call_u16(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 5;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_16bit(state, StackPointer, read_reg_16bit(state, StackPointer) - 1);
	unsigned short pc = read_reg_16bit(state, ProgramCounter) + 3;
	result.updates[1] = write_addr(state, read_reg_16bit(state, StackPointer), 0x00FF & pc);
	result.updates[2] = write_reg_16bit(state, StackPointer, read_reg_16bit(state, StackPointer) - 1);
	result.updates[3] = write_addr(state, read_reg_16bit(state, StackPointer), (0xFF00 & pc) >> 8);
	unsigned short dest = read_addr(state, read_reg_16bit(state, ProgramCounter) + 2) << 8;
	dest |= read_addr(state, read_reg_16bit(state, ProgramCounter) + 1);
	result.updates[4] = write_reg_16bit(state, ProgramCounter, dest);

	return result;
}

struct InstructionResult op_push_bc(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 5;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_16bit(state, StackPointer, read_reg_16bit(state, StackPointer) - 1);
	result.updates[1] = write_addr(state, read_reg_16bit(state, StackPointer), read_reg_8bit(state, RegC));
	result.updates[2] = write_reg_16bit(state, StackPointer, read_reg_16bit(state, StackPointer) - 1);
	result.updates[3] = write_addr(state, read_reg_16bit(state, StackPointer), read_reg_8bit(state, RegB));
	result.updates[4] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_pop_bc(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 5;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegB, read_addr(state, read_reg_16bit(state, StackPointer)));
	result.updates[1] = write_reg_16bit(state, StackPointer, read_reg_16bit(state, StackPointer) + 1);
	result.updates[2] = write_reg_8bit(state, RegC, read_addr(state, read_reg_16bit(state, StackPointer)));
	result.updates[3] = write_reg_16bit(state, StackPointer, read_reg_16bit(state, StackPointer) + 1);
	result.updates[4] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_ret(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);

	unsigned short new_pc = (read_addr(state, read_reg_16bit(state, StackPointer)) << 8) | (read_addr(state, read_reg_16bit(state, StackPointer) + 1));

	result.updates[0] = write_reg_16bit(state, StackPointer, read_reg_16bit(state, StackPointer) + 2);
	result.updates[1] = write_reg_16bit(state, ProgramCounter, new_pc);

	return result;
}
