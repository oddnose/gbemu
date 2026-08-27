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

struct InstructionResult op_inc_c(struct State* state)
{
	unsigned char num_updates = 2;
	unsigned char inc_result = read_reg_8bit(state, RegC) + 1;

	if (inc_result == 0) {
		inc_result++;
	}

	struct InstructionResult result;
	result.num_memory_updates = num_updates;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	unsigned char update_count = 0;
	result.updates[update_count++] = write_reg_8bit(state, RegC, inc_result); 

	if (inc_result == 0) {
		result.updates[update_count++] = write_flag(state, ZFlag, 1);
	}

	result.updates[update_count++] = increase_pc(state, 1);

	//TODO: set h if carry from bit 3, reset n 
	return result;
}
