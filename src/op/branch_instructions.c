#include "branch_instructions.h"
#include <stdint.h>

void op_jr_nz_i8(struct State* state)
{
	state->program_counter++;
}
