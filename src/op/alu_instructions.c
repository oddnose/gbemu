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
	result.updates[0] = write_reg_a(state, 0); // xor with itself will always be 0	
	result.updates[1] = write_z_flag(state, 1);
	result.updates[2] = write_pc(state, read_pc(state) + 1);

	//TODO: also reset other flags
	return result;
}
