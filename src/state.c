#include "state.h"
#include <stdio.h>
#include <stdlib.h>

//char* write_reg_a(unsigned char value);
//char* write_reg_b(unsigned char value);
//char* write_reg_c(unsigned char value);
//char* write_reg_d(unsigned char value);
//char* write_reg_e(unsigned char value);
//char* write_reg_h(unsigned char value);
//char* write_reg_l(unsigned char value);
//char* write_reg_af(unsigned short value);
//char* write_reg_bc(unsigned short value);
//char* write_reg_de(unsigned short value);
//char* write_reg_hl(unsigned short value);
char* write_sp(struct State* state, unsigned short value)
{
	unsigned short old_val = state->stack_pointer;
	state->stack_pointer = value;
	char* buffer = malloc(19);
	snprintf(buffer, 19, "SP: $%04x -> $%04x", old_val, state->stack_pointer);;
	return buffer;
}

char* write_pc(struct State* state, unsigned short value) 
{
	unsigned short old_val = state->program_counter;
	state->program_counter = value;
	char* buffer = malloc(19);
	snprintf(buffer, 19, "PC: $%04x -> $%04x", old_val, state->program_counter);;
	return buffer;
}
