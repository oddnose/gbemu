#include "state.h"
#include <stdio.h>
#include <stdlib.h>

struct State {
	unsigned char memory[8000];
	unsigned short reg_af; // Accumulator and flags
	unsigned short reg_bc; 
	unsigned short reg_de;
	unsigned short reg_hl;
	unsigned short stack_pointer;
	unsigned short program_counter;
};

struct State* create_state()
{
	struct State* state = malloc(sizeof *state);
	return state;
}

const unsigned int rom_memory_end = 0x3FFF;
void load_rom(struct State* state, char* rom_path)
{
	FILE *ptr;
	ptr = fopen(rom_path, "rb");
	fread(state->memory, rom_memory_end, 1, ptr);
}

unsigned char read_char(struct State* state, unsigned short source_memory_location)
{
	return state->memory[source_memory_location];
}

unsigned short read_short(struct State* state, unsigned short source_memory_location)
{
	// The high byte is stored last
	return (unsigned short) state->memory[source_memory_location + 1] << 8 | state->memory[source_memory_location];
}


struct MemoryUpdate write_reg_a(struct State* state, unsigned char value)
{
  unsigned char old_val = state->reg_af >> 8;
	unsigned short new_val = (unsigned short) value << 8;
  state->reg_af |= new_val;

	struct MemoryUpdate result;
	result.location = RegA;
	result.old_val_8bit = old_val;
	result.new_val_8bit = new_val;
	
  return result;
}
// char* write_reg_b(unsigned char value);
// char* write_reg_c(unsigned char value);
// char* write_reg_d(unsigned char value);
// char* write_reg_e(unsigned char value);

struct MemoryUpdate write_reg_h(struct State* state, unsigned char value)
{
  unsigned char old_val = state->reg_hl >> 8;
	unsigned short new_val = (unsigned short) value << 8;
  state->reg_hl |= new_val;

	struct MemoryUpdate result;
	result.location = RegH;
	result.old_val_8bit = old_val;
	result.new_val_8bit = new_val;
	
  return result;
}

struct MemoryUpdate write_reg_l(struct State* state, unsigned char value)
{
  unsigned char old_val = (unsigned char) state->reg_hl;
	unsigned short new_val = (unsigned short) value;
  state->reg_hl |= new_val;

	struct MemoryUpdate result;
	result.location = RegL;
	result.old_val_8bit = old_val;
	result.new_val_8bit = new_val;
	
  return result;
}

// char* write_reg_af(unsigned short value);
// char* write_reg_bc(unsigned short value);
// char* write_reg_de(unsigned short value);
struct MemoryUpdate write_reg_hl(struct State* state, unsigned short value)
{
  unsigned short old_val = state->reg_hl;
  state->reg_hl = value;
	struct MemoryUpdate result;
	result.location = RegHL;
	result.old_val_16bit = old_val;
	result.new_val_16bit = state->reg_hl;
	
  return result;
}

struct MemoryUpdate write_sp(struct State *state, unsigned short value)
{
  unsigned short old_val = state->stack_pointer;
  state->stack_pointer = value;
	struct MemoryUpdate result;
	result.location = StackPointer;
	result.old_val_16bit = old_val;
	result.new_val_16bit = state->stack_pointer;
	
  return result;
}

struct MemoryUpdate write_pc(struct State *state, unsigned short value) 
{
  unsigned short old_val = state->program_counter;
  state->program_counter = value;
	struct MemoryUpdate result;
	result.location = ProgramCounter;
	result.old_val_16bit = old_val;
	result.new_val_16bit = value;
	
  return result;
}

struct MemoryUpdate write_z_flag(struct State* state, bool value)
{
	bool old_val = state->reg_af & 0b10000000;
  state->reg_af |= ((unsigned short)value << 7);
	struct MemoryUpdate result;
	result.location = ZFlag;
	result.old_val_1bit = old_val;
	result.new_val_1bit = value;
	
  return result;
}

// Read functions

unsigned short read_sp(struct State* state)
{
	return state->stack_pointer;
}

unsigned short read_pc(struct State* state)
{
	return state->program_counter;
}
