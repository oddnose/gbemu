#include "load_instructions.h"
#include "op/instruction_result.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>


struct InstructionResult load_u16_to_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_16bit(state, reg, read_short(state, read_reg_16bit(state, ProgramCounter) + 1));
	result.updates[1] = increase_pc(state, 3);

	return result;
}

struct InstructionResult op_ld_de_u16(struct State* state) { return load_u16_to_reg(state, RegDE); }
struct InstructionResult op_ld_hl_u16(struct State* state) { return load_u16_to_reg(state, RegHL); }
struct InstructionResult op_ld_sp_u16(struct State* state) { return load_u16_to_reg(state, StackPointer); }

struct InstructionResult load_u8_to_reg(struct State* state, enum MemoryLocation reg)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, reg, read_short(state, read_reg_16bit(state, ProgramCounter) + 1));
	result.updates[1] = increase_pc(state, 2);

	return result;
}

struct InstructionResult op_ld_a_u8(struct State* state) { return load_u8_to_reg(state, RegA); }
struct InstructionResult op_ld_b_u8(struct State* state) { return load_u8_to_reg(state, RegB); }
struct InstructionResult op_ld_c_u8(struct State* state) { return load_u8_to_reg(state, RegC); }
struct InstructionResult op_ld_d_u8(struct State* state) { return load_u8_to_reg(state, RegD); }
struct InstructionResult op_ld_e_u8(struct State* state) { return load_u8_to_reg(state, RegE); }
struct InstructionResult op_ld_h_u8(struct State* state) { return load_u8_to_reg(state, RegH); }
struct InstructionResult op_ld_l_u8(struct State* state) { return load_u8_to_reg(state, RegL); }

struct InstructionResult op_ld_hld_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 3;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), read_reg_8bit(state, RegA));
	result.updates[1] = write_reg_16bit(state, RegHL, read_reg_16bit(state, RegHL) - 1);
	result.updates[2] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_ld_hli_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 3;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), read_reg_8bit(state, RegA));
	result.updates[1] = write_reg_16bit(state, RegHL, read_reg_16bit(state, RegHL) + 1);
	result.updates[2] = increase_pc(state, 1);

	return result;

}


struct InstructionResult op_ld_ff00_plus_c_a(struct State* state) 
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, 0xFF00 + read_reg_8bit(state, RegC), read_reg_8bit(state, RegA));
	result.updates[1] = increase_pc(state, 1);

	return result;
}


struct InstructionResult op_ld_hl_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, read_reg_16bit(state, RegHL), read_reg_8bit(state, RegA));
	result.updates[1] = increase_pc(state, 1);

	return result;
}

struct InstructionResult op_ld_ff00_plus_u8_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, 0xFF00 + read_addr(state, read_reg_16bit(state, ProgramCounter) + 1), read_reg_8bit(state, RegA));
	result.updates[1] = increase_pc(state, 2);

	return result;
}

struct InstructionResult op_ld_a_ff00_plus_u8(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegA, read_addr(state, 0xFF00 + read_addr(state, read_reg_16bit(state, ProgramCounter) + 1)));
	result.updates[1] = increase_pc(state, 2);

	return result;
}

struct InstructionResult load_reg_to_reg(struct State* state, enum MemoryLocation dest, enum MemoryLocation src)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, dest, read_reg_8bit(state, src));
	result.updates[1] = increase_pc(state, 1);
	return result;
}

struct InstructionResult op_ld_a_a(struct State* state) { return load_reg_to_reg(state, RegA, RegA); }
struct InstructionResult op_ld_a_b(struct State* state) { return load_reg_to_reg(state, RegA, RegB); }
struct InstructionResult op_ld_a_c(struct State* state) { return load_reg_to_reg(state, RegA, RegC); }
struct InstructionResult op_ld_a_d(struct State* state) { return load_reg_to_reg(state, RegA, RegD); }
struct InstructionResult op_ld_a_e(struct State* state) { return load_reg_to_reg(state, RegA, RegE); }
struct InstructionResult op_ld_a_h(struct State* state) { return load_reg_to_reg(state, RegA, RegH); }
struct InstructionResult op_ld_a_l(struct State* state) { return load_reg_to_reg(state, RegA, RegL); }
struct InstructionResult op_ld_b_a(struct State* state) { return load_reg_to_reg(state, RegB, RegA); }
struct InstructionResult op_ld_b_b(struct State* state) { return load_reg_to_reg(state, RegB, RegB); }
struct InstructionResult op_ld_b_c(struct State* state) { return load_reg_to_reg(state, RegB, RegC); }
struct InstructionResult op_ld_b_d(struct State* state) { return load_reg_to_reg(state, RegB, RegD); }
struct InstructionResult op_ld_b_e(struct State* state) { return load_reg_to_reg(state, RegB, RegE); }
struct InstructionResult op_ld_b_h(struct State* state) { return load_reg_to_reg(state, RegB, RegH); }
struct InstructionResult op_ld_b_l(struct State* state) { return load_reg_to_reg(state, RegB, RegL); }
struct InstructionResult op_ld_c_a(struct State* state) { return load_reg_to_reg(state, RegC, RegA); }
struct InstructionResult op_ld_c_b(struct State* state) { return load_reg_to_reg(state, RegC, RegB); }
struct InstructionResult op_ld_c_c(struct State* state) { return load_reg_to_reg(state, RegC, RegC); }
struct InstructionResult op_ld_c_d(struct State* state) { return load_reg_to_reg(state, RegC, RegD); }
struct InstructionResult op_ld_c_e(struct State* state) { return load_reg_to_reg(state, RegC, RegE); }
struct InstructionResult op_ld_c_h(struct State* state) { return load_reg_to_reg(state, RegC, RegH); }
struct InstructionResult op_ld_c_l(struct State* state) { return load_reg_to_reg(state, RegC, RegL); }
struct InstructionResult op_ld_d_a(struct State* state) { return load_reg_to_reg(state, RegD, RegA); }
struct InstructionResult op_ld_d_b(struct State* state) { return load_reg_to_reg(state, RegD, RegB); }
struct InstructionResult op_ld_d_c(struct State* state) { return load_reg_to_reg(state, RegD, RegC); }
struct InstructionResult op_ld_d_d(struct State* state) { return load_reg_to_reg(state, RegD, RegD); }
struct InstructionResult op_ld_d_e(struct State* state) { return load_reg_to_reg(state, RegD, RegE); }
struct InstructionResult op_ld_d_h(struct State* state) { return load_reg_to_reg(state, RegD, RegH); }
struct InstructionResult op_ld_d_l(struct State* state) { return load_reg_to_reg(state, RegD, RegL); }
struct InstructionResult op_ld_e_a(struct State* state) { return load_reg_to_reg(state, RegE, RegA); }
struct InstructionResult op_ld_e_b(struct State* state) { return load_reg_to_reg(state, RegE, RegB); }
struct InstructionResult op_ld_e_c(struct State* state) { return load_reg_to_reg(state, RegE, RegC); }
struct InstructionResult op_ld_e_d(struct State* state) { return load_reg_to_reg(state, RegE, RegD); }
struct InstructionResult op_ld_e_e(struct State* state) { return load_reg_to_reg(state, RegE, RegE); }
struct InstructionResult op_ld_e_h(struct State* state) { return load_reg_to_reg(state, RegE, RegH); }
struct InstructionResult op_ld_e_l(struct State* state) { return load_reg_to_reg(state, RegE, RegL); }
struct InstructionResult op_ld_h_a(struct State* state) { return load_reg_to_reg(state, RegH, RegA); }
struct InstructionResult op_ld_h_b(struct State* state) { return load_reg_to_reg(state, RegH, RegB); }
struct InstructionResult op_ld_h_c(struct State* state) { return load_reg_to_reg(state, RegH, RegC); }
struct InstructionResult op_ld_h_d(struct State* state) { return load_reg_to_reg(state, RegH, RegD); }
struct InstructionResult op_ld_h_e(struct State* state) { return load_reg_to_reg(state, RegH, RegE); }
struct InstructionResult op_ld_h_h(struct State* state) { return load_reg_to_reg(state, RegH, RegH); }
struct InstructionResult op_ld_h_l(struct State* state) { return load_reg_to_reg(state, RegH, RegL); }
struct InstructionResult op_ld_l_a(struct State* state) { return load_reg_to_reg(state, RegL, RegA); }
struct InstructionResult op_ld_l_b(struct State* state) { return load_reg_to_reg(state, RegL, RegB); }
struct InstructionResult op_ld_l_c(struct State* state) { return load_reg_to_reg(state, RegL, RegC); }
struct InstructionResult op_ld_l_d(struct State* state) { return load_reg_to_reg(state, RegL, RegD); }
struct InstructionResult op_ld_l_e(struct State* state) { return load_reg_to_reg(state, RegL, RegE); }
struct InstructionResult op_ld_l_h(struct State* state) { return load_reg_to_reg(state, RegL, RegH); }
struct InstructionResult op_ld_l_l(struct State* state) { return load_reg_to_reg(state, RegL, RegL); }

struct InstructionResult op_ld_a_de(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_reg_8bit(state, RegA, read_addr(state, read_reg_16bit(state, RegDE)));
	result.updates[1] = increase_pc(state, 1);
	return result;
}

struct InstructionResult op_ld_u16_a(struct State* state)
{
	struct InstructionResult result;
	result.num_memory_updates = 2;
	result.updates = malloc(result.num_memory_updates * sizeof *result.updates);
	result.updates[0] = write_addr(state, read_short(state, read_reg_16bit(state, ProgramCounter) + 1), read_reg_8bit(state, RegA));
	result.updates[1] = increase_pc(state, 3);
	return result;
}

