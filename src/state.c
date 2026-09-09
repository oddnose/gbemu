#include "state.h"
#include <stdio.h>
#include <stdlib.h>

struct State {
	unsigned char memory[0x10000];
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

void set_gb_doctor_start(struct State* state) 
{
	state->reg_af = 0x01B0;
	state->reg_bc = 0x0013;
	state->reg_de = 0x00D8;
	state->reg_hl = 0x014D;
	state->stack_pointer = 0xFFFE;
	state->program_counter = 0x0100;
}

void print_gb_doctor_debug(struct State* state)
{
	FILE* ptr = fopen("doctor-output.txt", "a");
	fprintf(ptr, "A:%02x F:%02X B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X SP:%04X PC:%04X PCMEM:%02X,%02X,%02X,%02X\n",
				 state->reg_af >> 8, state->reg_af & 0x00FF, state->reg_bc >> 8, state->reg_bc & 0x00FF, state->reg_de >> 8, state->reg_de & 0x00FF, state->reg_hl >> 8, state->reg_hl & 0x00FF,
				 state->stack_pointer, state->program_counter, 
				 state->memory[state->program_counter], state->memory[state->program_counter + 1], state->memory[state->program_counter + 2], state->memory[state->program_counter + 3]
				 );

	fclose(ptr);
}

const unsigned int rom_memory_end = 0x3FFF;
void load_rom(struct State* state, char* rom_path)
{
	FILE *ptr = fopen(rom_path, "rb");
	if (ptr == NULL) {
		perror("Error opening file");
		return;
	}
	fseek(ptr, 0, SEEK_END);
	size_t size = ftell(ptr);
	fseek(ptr, 0, SEEK_SET);
	fread(state->memory, sizeof(unsigned char), size, ptr);
	fclose(ptr);
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

struct MemoryUpdate write_upper_byte(enum MemoryLocation location, unsigned short* reg, unsigned char value)
{
  unsigned char old_val = *reg >> 8;
  *reg = (*reg & 0x00FF) | ((unsigned short) value << 8);

	struct MemoryUpdate result;
	result.location = location;
	result.old_val_8bit = old_val;
	result.new_val_8bit = value;
	
  return result;
}

struct MemoryUpdate write_lower_byte(enum MemoryLocation location, unsigned short* reg, unsigned char value)
{
  unsigned char old_val = *reg;
  *reg = (*reg & 0xFF00) | value;

	struct MemoryUpdate result;
	result.location = location;
	result.old_val_8bit = old_val;
	result.new_val_8bit = value;
	
  return result;
}

struct MemoryUpdate write_reg(enum MemoryLocation location, unsigned short* reg, unsigned short value) {
  unsigned short old_val = *reg;
  *reg = value;

	// The lower 4 bits of the flags register can never be set
	if (location == RegAF) {
		*reg &= 0xFFF0;
	}
	struct MemoryUpdate result;
	result.location = location;
	result.old_val_16bit = old_val;
	result.new_val_16bit = *reg;
	
  return result;
}

struct MemoryUpdate write_reg_8bit(struct State* state, enum MemoryLocation reg, unsigned char value)
{
	switch (reg) {
		case RegA: return write_upper_byte(RegA, &state->reg_af, value);
		case RegB: return write_upper_byte(RegB, &state->reg_bc, value);
		case RegC: return write_lower_byte(RegC, &state->reg_bc, value);
		case RegD: return write_upper_byte(RegD, &state->reg_de, value); 
		case RegE: return write_lower_byte(RegE, &state->reg_de, value); 
		case RegH: return write_upper_byte(RegH, &state->reg_hl, value); 
		case RegL: return write_lower_byte(RegL, &state->reg_hl, value); 

		case RegAF:
		case RegBC:
		case RegDE:
		case RegHL:
		case StackPointer:
		case ProgramCounter:
		case ZFlag:
		case NFlag:
		case HFlag:
		case CFlag:
		case Address:
			printf("Invalid register provided to write_reg_8bit\n");
			exit(1);
	}
}

struct MemoryUpdate write_reg_16bit(struct State* state, enum MemoryLocation reg, unsigned short value)
{
	switch (reg) {
		case RegAF: return write_reg(RegAF, &state->reg_af, value);
		case RegBC: return write_reg(RegBC, &state->reg_bc, value); 
		case RegDE: return write_reg(RegDE, &state->reg_de, value); 
		case RegHL: return write_reg(RegHL, &state->reg_hl, value); 
		case StackPointer: return write_reg(StackPointer, &state->stack_pointer, value); 
		case ProgramCounter: return write_reg(ProgramCounter, &state->program_counter, value); 

		case RegA: 
		case RegB: 
		case RegC: 
		case RegD:  
		case RegE:  
		case RegH:  
		case RegL:  
		case ZFlag:
		case NFlag:
		case HFlag:
		case CFlag:
		case Address:
			printf("Invalid register provided to write_reg_16bit\n");
			exit(1);
	}

}

struct MemoryUpdate write_n_flag(struct State* state, bool value)
{
	bool old_val = state->reg_af & 0b01000000;
	//TODO: find better way?
	state->reg_af &= 0b10111111;
  state->reg_af |= ((unsigned short)value << 6);
	struct MemoryUpdate result;
	result.location = NFlag;
	result.old_val_1bit = old_val;
	result.new_val_1bit = value;
	
  return result;
}

struct MemoryUpdate write_h_flag(struct State* state, bool value)
{
	bool old_val = state->reg_af & 0b00100000;
	//TODO: find better way?
	state->reg_af &= 0b11011111;
  state->reg_af |= ((unsigned short)value << 5);
	struct MemoryUpdate result;
	result.location = HFlag;
	result.old_val_1bit = old_val;
	result.new_val_1bit = value;
	
  return result;
}

struct MemoryUpdate write_c_flag(struct State* state, bool value)
{
	bool old_val = state->reg_af & 0b00010000;
	//TODO: find better way?
	state->reg_af &= 0b11101111;
  state->reg_af |= ((unsigned short)value << 4);
	struct MemoryUpdate result;
	result.location = CFlag;
	result.old_val_1bit = old_val;
	result.new_val_1bit = value;
	
  return result;
}

struct MemoryUpdate write_flag(struct State* state, enum MemoryLocation flag, bool value)
{
	unsigned char bit_pos;
	switch (flag) {
		case ZFlag: bit_pos = 7; break;
		case NFlag: bit_pos = 6; break;
		case HFlag: bit_pos = 5; break;
		case CFlag: bit_pos = 4; break;

		case RegAF:
		case RegBC: 
		case RegDE: 
		case RegHL: 
		case StackPointer: 
		case ProgramCounter: 
		case RegA: 
		case RegB: 
		case RegC: 
		case RegD:  
		case RegE:  
		case RegH:  
		case RegL:  
		case Address:
			printf("Invalid flag provided to write_flag\n");
			exit(1);
	}
	bool old_val = state->reg_af & (1u << bit_pos);

	if (value) {
		state->reg_af |= (1u << bit_pos);
	} else {
		state->reg_af &= ~(1u << bit_pos);
	}

	struct MemoryUpdate result;
	result.location = flag;
	result.old_val_1bit = old_val;
	result.new_val_1bit = value;
	
  return result;
}


struct MemoryUpdate write_addr(struct State* state, unsigned short addr, unsigned char value)
{
	unsigned char old_val = state->memory[addr];
	state->memory[addr] = value;
	struct MemoryUpdate result;
	result.location = Address;
	result.old_val_8bit = old_val;
	result.new_val_8bit = value;
	result.address = addr;
	
  return result;

}

struct MemoryUpdate increase_pc(struct State* state, unsigned short amount) { return write_reg_16bit(state, ProgramCounter, read_reg_16bit(state, ProgramCounter) + amount); }

// Read functions

unsigned char read_reg_8bit(struct State* state, enum MemoryLocation reg)
{
	switch (reg) {
		case RegA: return state->reg_af >> 8; 
		case RegB: return state->reg_bc >> 8; 
		case RegC: return state->reg_bc & 0x00FF; 
		case RegD: return state->reg_de >> 8; 
		case RegE: return state->reg_de & 0x00FF; 
		case RegH: return state->reg_hl >> 8; 
		case RegL: return state->reg_hl & 0x00FF; 

		case RegAF:
		case RegBC:
		case RegDE:
		case RegHL:
		case StackPointer:
		case ProgramCounter:
		case ZFlag:
		case NFlag:
		case HFlag:
		case CFlag:
		case Address:
			printf("Invalid register provided to read_reg_8bit\n");
			exit(1);
		}
}

unsigned short read_reg_16bit(struct State* state, enum MemoryLocation reg)
{
	switch (reg) {
		case RegAF: return state->reg_af;
		case RegBC: return state->reg_bc; 
		case RegDE: return state->reg_de;
		case RegHL: return state->reg_hl;
		case StackPointer: return state->stack_pointer;
		case ProgramCounter: return state->program_counter;

		case RegA: 
		case RegB: 
		case RegC: 
		case RegD: 
		case RegE: 
		case RegH: 
		case RegL: 
		case ZFlag:
		case NFlag:
		case HFlag:
		case CFlag:
		case Address:
			printf("Invalid register provided to read_reg_16bit\n");
			exit(1);
		}
}

bool read_z_flag(struct State* state) { return (state->reg_af & 0b10000000) != 0; }
bool read_n_flag(struct State* state) { return (state->reg_af & 0b01000000) != 0; }
bool read_h_flag(struct State* state) { return (state->reg_af & 0b00100000) != 0; }
bool read_c_flag(struct State* state) { return (state->reg_af & 0b00010000) != 0; }

bool read_flag(struct State* state, enum MemoryLocation flag)
{
	switch (flag) {
		case ZFlag: return read_z_flag(state);
		case NFlag: return read_n_flag(state);
		case HFlag: return read_h_flag(state);
		case CFlag: return read_c_flag(state);

		case RegAF:
		case RegBC: 
		case RegDE: 
		case RegHL: 
		case StackPointer: 
		case ProgramCounter: 
		case RegA: 
		case RegB: 
		case RegC: 
		case RegD:  
		case RegE:  
		case RegH:  
		case RegL:  
		case Address:
			printf("Invalid flag provided to write_flag\n");
			exit(1);
	}
}


unsigned char read_addr(struct State* state, unsigned short addr)
{ 
	//: Needed for gameboy-doctor
	/*if (addr == 0xFF44) { 
		printf("WARN: Returning hardcoded value for 0xFF44\n");
		return 0x90; 
	}*/
	return state->memory[addr]; 
}

