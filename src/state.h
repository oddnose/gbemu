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
struct MemoryUpdate write_reg_a(struct State* state, unsigned char value);
struct MemoryUpdate write_reg_b(struct State* state, unsigned char value);
struct MemoryUpdate write_reg_c(struct State* state, unsigned char value);
struct MemoryUpdate write_reg_d(struct State* state, unsigned char value);
struct MemoryUpdate write_reg_e(struct State* state, unsigned char value);
struct MemoryUpdate write_reg_h(struct State* state, unsigned char value);
struct MemoryUpdate write_reg_l(struct State* state, unsigned char value);
struct MemoryUpdate write_reg_af(struct State* state, unsigned short value);
struct MemoryUpdate write_reg_bc(struct State* state, unsigned short value);
struct MemoryUpdate write_reg_de(struct State* state, unsigned short value);
struct MemoryUpdate write_reg_hl(struct State* state, unsigned short value);
struct MemoryUpdate write_sp(struct State* state, unsigned short value);
struct MemoryUpdate write_pc(struct State* state, unsigned short value);

struct MemoryUpdate write_z_flag(struct State* state, bool value);
struct MemoryUpdate write_n_flag(struct State* state, bool value);
struct MemoryUpdate write_h_flag(struct State* state, bool value);
struct MemoryUpdate write_c_flag(struct State* state, bool value);

struct MemoryUpdate write_addr(struct State* state, unsigned short addr, unsigned char value);


// Read functions
unsigned short read_short(struct State* state, unsigned short source_memory_location);
unsigned char read_char(struct State* state, unsigned short source_memory_location);

unsigned char read_reg_a(struct State* state);
unsigned char read_reg_b(struct State* state);
unsigned char read_reg_c(struct State* state);
unsigned char read_reg_d(struct State* state);
unsigned char read_reg_e(struct State* state);
unsigned char read_reg_h(struct State* state);
unsigned char read_reg_l(struct State* state);
unsigned short read_reg_af(struct State* state);
unsigned short read_reg_bc(struct State* state);
unsigned short read_reg_de(struct State* state);
unsigned short read_reg_hl(struct State* state);
unsigned short read_sp(struct State* state);
unsigned short read_pc(struct State* state);

bool read_z_flag(struct State* state);
bool read_n_flag(struct State* state);
bool read_h_flag(struct State* state);
bool read_c_flag(struct State* state);
