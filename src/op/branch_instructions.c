#include "branch_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdint.h>
#include <stdlib.h>

struct InstructionResult op_jr_nz_i8(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 1;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	if (!read_z_flag(state)) {
		result.updates[0] = write_pc(state, read_pc(state) + (char) read_char(state, read_pc(state) + 1) + 2); // 2 = length of instruction
	} else {
		result.updates[0] = write_pc(state, read_pc(state) + 2);
	}

	return result;
}
