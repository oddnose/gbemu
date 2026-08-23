#include "load_instructions.h"
#include <stdio.h>

unsigned short combine_to_16bit(unsigned char low, unsigned char high)
{
	return ((unsigned short) high << 8) | low;
}

void op_ld_sp_u16(struct State* state)
{
	unsigned short value = combine_to_16bit(state->memory[state->program_counter + 1], state->memory[state->program_counter + 2]);
	state->program_counter += 2;
	printf("LD SP, $%04x\n", value); 
}

void op_ld_hl_minus_a(struct State* state)
{
	printf("LD (HL-), A\n"); 
}


void op_ld_hl_u16(struct State* state)
{
	unsigned short value = combine_to_16bit(state->memory[state->program_counter + 1], state->memory[state->program_counter + 2]);
	state->program_counter += 2;
	printf("LD HL, $%04x\n", value);
}

void op_ld_c_u8(struct State* state)
{
	printf("LD C, $%02x\n", state->memory[++state->program_counter]);
}

void op_ld_a_u8(struct State* state)
{
	printf("LD A, $%02x\n", state->memory[++state->program_counter]);
}

void op_ld_ff00_plus_c_a(struct State* state) 
{
	printf("LD (FF00+C), A\n"); 
}
