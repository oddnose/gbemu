#include "load_instructions.h"
#include "state.h"
#include <stdio.h>

void op_ld_sp_u16(struct State* state)
{
	char* result_sp = write_sp(state, ((unsigned short) state->memory[state->program_counter + 2] << 8) | state->memory[state->program_counter + 1]);
	char* result_pc = write_pc(state, state->program_counter + 3);
	printf("%s\n", result_sp);
	printf("%s\n", result_pc);
}

void op_ld_hl_minus_a(struct State* state)
{
	state->program_counter++;
}


void op_ld_hl_u16(struct State* state)
{
	state->program_counter += 3;
}

void op_ld_c_u8(struct State* state)
{
	state->program_counter++;
}

void op_ld_a_u8(struct State* state)
{
	state->program_counter++;
}

void op_ld_ff00_plus_c_a(struct State* state) 
{
	state->program_counter++;
}
