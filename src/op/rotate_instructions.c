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
	bool val = read_reg_h(state) >> 7;
	result.updates[0] = write_z_flag(state, !val);
	result.updates[1] = write_pc(state, read_pc(state) + 2);

	// TODO: sets flag H and resets N
	return result;
}
