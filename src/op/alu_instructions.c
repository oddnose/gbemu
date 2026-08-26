#include "alu_instructions.h"
#include "state.h"
#include <stdio.h>

void op_xor_a_a(struct State* state)
{
	char* result_rega = write_reg_a(state, 0); // xor with itself will always be 0	
	char* result_z = write_z_flag(state, 1);
	char* result_pc = write_pc(state, state->program_counter + 1);

	printf("%s\n", result_rega);
	printf("%s\n", result_z);
	printf("%s\n", result_pc);

	//TODO: also reset other flags
}
