#include "alu_instructions.h"
#include "state.h"
#include <stdio.h>

void op_xor_a_a(struct State* state)
{
	struct MemoryUpdate result_rega = write_reg_a(state, 0); // xor with itself will always be 0	
	struct MemoryUpdate result_z = write_z_flag(state, 1);
	struct MemoryUpdate result_pc = write_pc(state, read_pc(state) + 1);

	//TODO: also reset other flags
}
