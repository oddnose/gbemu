#include "branch_instructions.h"
#include <stdint.h>
#include <stdio.h>

void op_jr_nz_i8(struct State* state)
{
	printf("JR NZ, %d\n", (int8_t) state->memory[++state->program_counter]);
}
