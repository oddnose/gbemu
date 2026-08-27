#pragma once

#include <stdbool.h>

struct State;

enum MemoryLocation {
	RegA,
	RegB,
	RegC,
	RegD,
	RegE,
	RegH,
	RegL,
	RegBC,
	RegDE,
	RegHL,
	StackPointer,
	ProgramCounter,
	ZFlag,
	NFlag,
	HFlag,
	CFlag,
	Address
};


struct MemoryUpdate {
	enum MemoryLocation location;
	union {
		unsigned char old_val_8bit;
		unsigned short old_val_16bit;
		bool old_val_1bit;
	};
	union {
		unsigned char new_val_8bit;
		unsigned short new_val_16bit;
		bool new_val_1bit;
	};
	unsigned short address; //TODO: only relevant for Address
};

struct State* create_state();
void load_rom(struct State* state, char* rom_path);


// Write functions
struct MemoryUpdate write_reg_8bit(struct State* state, enum MemoryLocation reg, unsigned char value);
struct MemoryUpdate write_reg_16bit(struct State* state, enum MemoryLocation reg, unsigned short value);
struct MemoryUpdate write_flag(struct State* state, enum MemoryLocation flag, bool value);
struct MemoryUpdate write_addr(struct State* state, unsigned short addr, unsigned char value);

struct MemoryUpdate increase_pc(struct State* state, unsigned short amount);

// Read functions
unsigned short read_short(struct State* state, unsigned short source_memory_location);
unsigned char read_char(struct State* state, unsigned short source_memory_location);

unsigned char read_reg_8bit(struct State* state, enum MemoryLocation reg);
unsigned short read_reg_16bit(struct State* state, enum MemoryLocation reg);
bool read_flag(struct State* state, enum MemoryLocation flag);
unsigned char read_addr(struct State* state, unsigned short addr);
