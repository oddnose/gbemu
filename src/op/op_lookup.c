#include "op_lookup.h"

#include <stdio.h>
#include <stdlib.h>

#include "load_instructions.h"
#include "alu_instructions.h"
#include "op/cb_lookup.h"
#include "branch_instructions.h"

void op_invalid(struct State* state)
{
	printf("Instruction is invalid: $%02x\n", state->memory[state->program_counter]);
	exit(1);
}

void op_not_implemented(struct State* state)
{
	printf("Unknown instruction: $%02x\n", state->memory[state->program_counter]);
	exit(1);
}

// Initialize lookup table with function pointers
struct OpDefinition op_lookup[256] = {
	[0x00] = { // NOP
		.length = 1,
		.callback = op_not_implemented,
	},
	[0x01] = { // LD BC, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0x02] = { // LD (BC), A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x03] = { // INC BC
		.length = 1,
		.callback = op_not_implemented
	},
	[0x04] = { // INC B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x05] = { // DEC B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x06] = { // LD B, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x07] = { // RLCA
		.length = 1,
		.callback = op_not_implemented
	},
	[0x08] = { // LD (u16), SP
		.length = 3,
		.callback = op_not_implemented
	},
	[0x09] = { // ADD HL, BC
		.length = 1,
		.callback = op_not_implemented
	},
	[0x0a] = { // LD A, (BC)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x0b] = { // DEC BC
		.length = 1,
		.callback = op_not_implemented
	},
	[0x0c] = { // INC C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x0d] = { // DEC C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x0e] = { // LD C, u8
		.length = 2,
		.callback = op_ld_c_u8
	},
	[0x0f] = { // RRCA
		.length = 1,
		.callback = op_not_implemented
	},
	[0x10] = { // STOP
		.length = 1,
		.callback = op_not_implemented
	},
	[0x11] = { // LD DE, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0x12] = { // LD (DE), A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x13] = { // INC DE
		.length = 1,
		.callback = op_not_implemented
	},
	[0x14] = { // INC D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x15] = { // DEC D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x16] = { // LD D, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x17] = { // RLA
		.length = 1,
		.callback = op_not_implemented
	},
	[0x18] = { // JR i8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x19] = { // ADD HL, DE
		.length = 1,
		.callback = op_not_implemented
	},
	[0x1a] = { // LD A, (DE)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x1b] = { // DEC DE
		.length = 1,
		.callback = op_not_implemented
	},
	[0x1c] = { // INC E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x1d] = { // DEC E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x1e] = { // LD E, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x1f] = { // RRA
		.length = 1,
		.callback = op_not_implemented
	},
	[0x20] = { // JR NZ, i8
		.length = 2,
		.callback = op_jr_nz_i8
	},
	[0x21] = { // LD HL, u16
		.length = 3,
		.callback = op_ld_hl_u16
	},
	[0x22] = { // LD (HL+), A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x23] = { // INC HL
		.length = 1,
		.callback = op_not_implemented
	},
	[0x24] = { // INC H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x25] = { // DEC H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x26] = { // LD H, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x27] = { // DAA 
		.length = 1,
		.callback = op_not_implemented
	},
	[0x28] = { // JR Z, i8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x29] = { // ADD HL, HL
		.length = 1,
		.callback = op_not_implemented
	},
	[0x2a] = { // LD A, (HL+)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x2b] = { // DEC HL
		.length = 1,
		.callback = op_not_implemented
	},
	[0x2c] = { // INC L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x2d] = { // DEC L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x2e] = { // LD L, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x2f] = { // CPL
		.length = 1,
		.callback = op_not_implemented
	},
	[0x30] = { // JR NC, i8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x31] = { // LD SP, u16
		.length = 3,
		.callback = op_ld_sp_u16
	},
	[0x32] = { // LD (HL-), A
		.length = 3,
		.callback = op_ld_hl_minus_a,
	},
	[0x33] = { // INC SP
		.length = 1,
		.callback = op_not_implemented
	},
	[0x34] = { // INC (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x35] = { // DEC (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x36] = { // LD (HL), u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x37] = { // SCF
		.length = 1,
		.callback = op_not_implemented
	},
	[0x38] = { // JR C, i8
		.length = 2,
		.callback = op_not_implemented
	},
	[0x39] = { // ADD HL, SP
		.length = 1,
		.callback = op_not_implemented
	},
	[0x3a] = { // LD A, (HL-)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x3b] = { // DEC SP
		.length = 1,
		.callback = op_not_implemented
	},
	[0x3c] = { // INC A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x3d] = { // DEC A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x3e] = { // LD A, u8
		.length = 2,
		.callback = op_ld_a_u8
	},
	[0x3f] = { // CCF
		.length = 1,
		.callback = op_not_implemented
	},
	[0x40] = { // LD B, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x41] = { // LD B, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x42] = { // LD B, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x43] = { // LD B, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x44] = { // LD B, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x45] = { // LD B, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x46] = { // LD B, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x47] = { // LD B, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x48] = { // LD C, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x49] = { // LD C, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x4a] = { // LD C, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x4b] = { // LD C, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x4c] = { // LD C, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x4d] = { // LD C, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x4e] = { // LD C, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x4f] = { // LD C, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x50] = { // LD D, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x51] = { // LD D, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x52] = { // LD D, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x53] = { // LD D, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x54] = { // LD, D, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x55] = { // LD D, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x56] = { // LD D, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x57] = { // LD D, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x58] = { // LD E, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x59] = { // LD E, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x5a] = { // LD E, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x5b] = { // LD E, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x5c] = { // LD E, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x5d] = { // LD E, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x5e] = { // LD E, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x5f] = { // LD E, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x60] = { // LD H, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x61] = { // LD H, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x62] = { // LD H, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x63] = { // LD H, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x64] = { // LD H, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x65] = { // LD H, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x66] = { // LD H, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x67] = { // LD H, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x68] = { // LD L, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x69] = { // LD L, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x6a] = { // LD L, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x6b] = { // LD L, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x6c] = { // LD L, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x6d] = { // LD L, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x6e] = { // LD LD L, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x6f] = { // LD L, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x70] = { // LD (HL), B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x71] = { // LD (HL), C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x72] = { // LD (HL), D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x73] = { // LD (HL), E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x74] = { // LD (HL), H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x75] = { // LD (HL), L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x76] = { // HALT
		.length = 1,
		.callback = op_not_implemented
	},
	[0x77] = { // LD (HL), A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x78] = { // LD A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x79] = { // LD A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x7a] = { // LD A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x7b] = { // LD A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x7c] = { // LD A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x7d] = { // LD A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x7e] = { // LD A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x7f] = { // LD A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x80] = { // ADD A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x81] = { // ADD A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x82] = { // ADD A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x83] = { // ADD A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x84] = { // ADD A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x85] = { // ADD A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x86] = { // ADD A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x87] = { // ADD A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x88] = { // ADC A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x89] = { // ADC A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x8a] = { // ADC A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x8b] = { // ADC A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x8c] = { // ADC A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x8d] = { // ADC A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x8e] = { // ADC A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x8f] = { // ADC A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x90] = { // SUB A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x91] = { // SUB A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x92] = { // SUB A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x93] = { // SUB A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x94] = { // SUB A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x95] = { // SUB A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x96] = { // SUB A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x97] = { // SUB A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0x98] = { // SBC A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0x99] = { // SBC A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0x9a] = { // SBC A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0x9b] = { // SBC A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0x9c] = { // SBC A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0x9d] = { // SBC A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0x9e] = { // SBC A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0x9f] = { // SBC A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa0] = { // AND A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa1] = { // AND A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa2] = { // AND A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa3] = { // AND A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa4] = { // AND A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa5] = { // AND A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa6] = { // AND A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa7] = { // AND A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa8] = { // XOR A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0xa9] = { // XOR A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0xaa] = { // XOR A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0xab] = { // XOR A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0xac] = { // XOR A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0xad] = { // XOR A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0xae] = { // XOR A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0xaf] = { // XOR A, A
		.length = 1,
		.callback = op_xor_a_a
	},
	[0xb0] = { // OR A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb1] = { // OR A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb2] = { // OR A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb3] = { // OR A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb4] = { // OR A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb5] = { // OR A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb6] = { // OR A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb7] = { // OR A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb8] = { // CP A, B
		.length = 1,
		.callback = op_not_implemented
	},
	[0xb9] = { // CP A, C
		.length = 1,
		.callback = op_not_implemented
	},
	[0xba] = { // CP A, D
		.length = 1,
		.callback = op_not_implemented
	},
	[0xbb] =  { // CP A, E
		.length = 1,
		.callback = op_not_implemented
	},
	[0xbc] = { // CP A, H
		.length = 1,
		.callback = op_not_implemented
	},
	[0xbd] = { // CP A, L
		.length = 1,
		.callback = op_not_implemented
	},
	[0xbe] = { // CP A, (HL)
		.length = 1,
		.callback = op_not_implemented
	},
	[0xbf] = { // CP A, A
		.length = 1,
		.callback = op_not_implemented
	},
	[0xc0] = { // RET NZ
		.length = 1,
		.callback = op_not_implemented
	},
	[0xc1] = { // POP BC
		.length = 1,
		.callback = op_not_implemented
	},
	[0xc2] = { // JP NZ, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xc3] = { // JP u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xc4] = { // CALL NZ, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xc5] = { // PUSH BC
		.length = 1,
		.callback = op_not_implemented
	},
	[0xc6] = { // ADD A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xc7] = { // RST 00h
		.length = 1,
		.callback = op_not_implemented
	},
	[0xc8] = { // RET Z
		.length = 1,
		.callback = op_not_implemented
	},
	[0xc9] = { // RET
		.length = 1,
		.callback = op_not_implemented
	},
	[0xca] = { // JP Z, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xcb] = { // PREFIX CB
		.length = 1,
		.callback = op_not_implemented
	},
	[0xcc] = { // CALL Z, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xcd] = { // CALL u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xce] = { // ADC A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xcf] = { // RST 08h
		.length = 1,
		.callback = op_not_implemented
	},
	[0xd0] = { // RET NC
		.length = 1,
		.callback = op_not_implemented
	},
	[0xd1] = { // POP DE
		.length = 1,
		.callback = op_not_implemented
	},
	[0xd2] = { // JP NC, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xd3] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xd4] = { // CALL NC, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xd5] = { // PUSH DE
		.length = 1,
		.callback = op_not_implemented
	},
	[0xd6] = { // SUB A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xd7] = { // RST 10h
		.length = 1,
		.callback = op_not_implemented
	},
	[0xd8] = { // RET C
		.length = 1,
		.callback = op_not_implemented
	},
	[0xd9] = { // RETI
		.length = 1,
		.callback = op_not_implemented
	},
	[0xda] = { // JP C, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xdb] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xdc] = { // CALL C, u16
		.length = 3,
		.callback = op_not_implemented
	},
	[0xdd] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xde] = { // SBC A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xdf] = { // RST 18h
		.length = 1,
		.callback = op_not_implemented
	},
	[0xe0] = { // LD (FF00+u8), A
		.length = 2,
		.callback = op_not_implemented
	},
	[0xe1] = { // POP HL
		.length = 1,
		.callback = op_not_implemented
	},
	[0xe2] = { // LD (FF00+C), A
		.length = 1,
		.callback = op_ld_ff00_plus_c_a
	},
	[0xe3] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xe4] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xe5] = { // PUSH HL
		.length = 1,
		.callback = op_not_implemented
	},
	[0xe6] = { // AND A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xe7] = { // RST 20h
		.length = 1,
		.callback = op_not_implemented
	},
	[0xe8] = { // ADD SP, i8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xe9] = { // JP HL
		.length = 1,
		.callback = op_not_implemented
	},
	[0xea] = { // LD (u16), A
		.length = 3,
		.callback = op_not_implemented
	},
	[0xeb] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xec] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xed] = {
		.length = 0,
		.callback = op_invalid
	},
	[0xee] = { // XOR A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xef] = { // RST 28h
		.length = 1,
		.callback = op_not_implemented
	},
	[0xf0] = { // LD A, (FF00+u8)
		.length = 2,
		.callback = op_not_implemented
	},
	[0xf1] = { // POP AF
		.length = 1,
		.callback = op_not_implemented
	},
	[0xf2] = { // LD A, (FF00+C)
		.length = 1,
		.callback = op_not_implemented
	},
	[0xf3] = { // DI
		.length = 1,
		.callback = op_not_implemented
	},
	[0xf4] = {
		.length = 0,
		.callback = op_invalid
	},
	[0xf5] = { // PUSH AF
		.length = 1,
		.callback = op_not_implemented
	},
	[0xf6] = { // OR A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xf7] = { // RST 30h
		.length = 1,
		.callback = op_not_implemented
	},
	[0xf8] = { // LD HL, SP+i8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xf9] = { // LD SP, HL
		.length = 1,
		.callback = op_not_implemented
	},
	[0xfa] = { // LD A, (u16)
		.length = 3,
		.callback = op_not_implemented
	},
	[0xfb] = { // EI
		.length = 1,
		.callback = op_not_implemented
	},
	[0xfc] = {
		.length = 0,
		.callback = op_invalid
	},
	[0xfd] = { 
		.length = 0,
		.callback = op_invalid
	},
	[0xfe] = { // CP A, u8
		.length = 2,
		.callback = op_not_implemented
	},
	[0xff] = { // RST 38h
		.length = 1,
		.callback = op_not_implemented
	},
};

struct OpDefinition decode(struct State* state, uint8_t pos)
{
	if (state->memory[pos] == 0xcb) {
		return cb_decode(state, pos + 1);
	}
	return op_lookup[state->memory[pos]];
}

