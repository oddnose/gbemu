#include "load_instructions.h"
#include "state.h"
#include <stdio.h>

void op_ld_sp_u16(struct State* state)
{
	struct MemoryUpdate result_sp = write_sp(state, read_short(state, read_pc(state) + 1));
	struct MemoryUpdate result_pc = write_pc(state, read_pc(state) + 3);
}

void op_ld_hld_a(struct State* state)
{
	//struct MemoryUpdate result_hl = write_reg_hl(state, read_short(state, read_pc(state) + 1));
	//struct MemoryUpdate result_pc = write_pc(state, read_pc(state) + 3);
}


void op_ld_hl_u16(struct State* state)
{
	struct MemoryUpdate result_hl = write_reg_hl(state, read_short(state, read_pc(state) + 1));
	struct MemoryUpdate result_pc = write_pc(state, read_pc(state) + 3);
}

void op_ld_c_u8(struct State* state)
{
}

void op_ld_a_u8(struct State* state)
{
}

void op_ld_ff00_plus_c_a(struct State* state) 
{
}
