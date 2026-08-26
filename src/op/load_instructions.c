#include "load_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

struct InstructionResult op_ld_sp_u16(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_sp(state, read_short(state, read_pc(state) + 1));
	result.updates[1] = write_pc(state, read_pc(state) + 3);

	return result;
}

struct InstructionResult op_ld_hld_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 3;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, read_reg_hl(state), read_reg_a(state));
	result.updates[1] = write_reg_hl(state, read_reg_hl(state) - 1);
	result.updates[2] = write_pc(state, read_pc(state) + 1);

	return result;
}


struct InstructionResult op_ld_hl_u16(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_hl(state, read_short(state, read_pc(state) + 1));
	result.updates[1] = write_pc(state, read_pc(state) + 3);

	return result;
}

struct InstructionResult op_ld_c_u8(struct State* state)
{
	struct InstructionResult result;
	return result;
}

struct InstructionResult op_ld_a_u8(struct State* state)
{
	struct InstructionResult result;
	return result;
}

struct InstructionResult op_ld_ff00_plus_c_a(struct State* state) 
{
	struct InstructionResult result;
	return result;
}
