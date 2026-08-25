#pragma once

struct State {
	unsigned char memory[8000];
	unsigned short program_counter;
	unsigned short stack_pointer;
	unsigned char reg_a;
	unsigned char reg_b;
	unsigned char reg_c;
	unsigned char reg_d;
	unsigned char reg_e;
	unsigned char reg_h;
	unsigned char reg_l;
};

char* write_reg_a(struct State* state, unsigned char value);
char* write_reg_b(struct State* state, unsigned char value);
char* write_reg_c(struct State* state, unsigned char value);
char* write_reg_d(struct State* state, unsigned char value);
char* write_reg_e(struct State* state, unsigned char value);
char* write_reg_h(struct State* state, unsigned char value);
char* write_reg_l(struct State* state, unsigned char value);
char* write_reg_af(struct State* state, unsigned short value);
char* write_reg_bc(struct State* state, unsigned short value);
char* write_reg_de(struct State* state, unsigned short value);
char* write_reg_hl(struct State* state, unsigned short value);
char* write_sp(struct State* state, unsigned short value);
char* write_pc(struct State* state, unsigned short value);
