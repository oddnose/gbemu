#pragma once

#include "op/instruction_result.h"
#include "state.h"

struct InstructionResult op_ld_sp_u16(struct State* state);
struct InstructionResult op_ld_hld_a(struct State* state);
struct InstructionResult op_ld_hl_u16(struct State* state);
struct InstructionResult op_ld_ff00_plus_c_a(struct State* state);
struct InstructionResult op_ld_hl_a(struct State* state);
struct InstructionResult op_ld_ff00_plus_u8_a(struct State* state);
struct InstructionResult op_ld_b_a(struct State* state);
struct InstructionResult op_ld_de_u16(struct State* state);
struct InstructionResult op_ld_a_de(struct State* state);
struct InstructionResult op_ld_a_ff00_plus_u8(struct State* state);

// Load reg to reg
struct InstructionResult op_ld_a_a(struct State* state);
struct InstructionResult op_ld_a_b(struct State* state);
struct InstructionResult op_ld_a_c(struct State* state);
struct InstructionResult op_ld_a_d(struct State* state);
struct InstructionResult op_ld_a_e(struct State* state);
struct InstructionResult op_ld_a_h(struct State* state);
struct InstructionResult op_ld_a_l(struct State* state);
//hl
struct InstructionResult op_ld_b_a(struct State* state);
struct InstructionResult op_ld_b_b(struct State* state);
struct InstructionResult op_ld_b_c(struct State* state);
struct InstructionResult op_ld_b_d(struct State* state);
struct InstructionResult op_ld_b_e(struct State* state);
struct InstructionResult op_ld_b_h(struct State* state);
struct InstructionResult op_ld_b_l(struct State* state);
//hl
struct InstructionResult op_ld_c_a(struct State* state);
struct InstructionResult op_ld_c_b(struct State* state);
struct InstructionResult op_ld_c_c(struct State* state);
struct InstructionResult op_ld_c_d(struct State* state);
struct InstructionResult op_ld_c_e(struct State* state);
struct InstructionResult op_ld_c_h(struct State* state);
struct InstructionResult op_ld_c_l(struct State* state);
//hl
struct InstructionResult op_ld_d_a(struct State* state);
struct InstructionResult op_ld_d_b(struct State* state);
struct InstructionResult op_ld_d_c(struct State* state);
struct InstructionResult op_ld_d_d(struct State* state);
struct InstructionResult op_ld_d_e(struct State* state);
struct InstructionResult op_ld_d_h(struct State* state);
struct InstructionResult op_ld_d_l(struct State* state);
//hl
struct InstructionResult op_ld_e_a(struct State* state);
struct InstructionResult op_ld_e_b(struct State* state);
struct InstructionResult op_ld_e_c(struct State* state);
struct InstructionResult op_ld_e_d(struct State* state);
struct InstructionResult op_ld_e_e(struct State* state);
struct InstructionResult op_ld_e_h(struct State* state);
struct InstructionResult op_ld_e_l(struct State* state);
//hl
struct InstructionResult op_ld_h_a(struct State* state);
struct InstructionResult op_ld_h_b(struct State* state);
struct InstructionResult op_ld_h_c(struct State* state);
struct InstructionResult op_ld_h_d(struct State* state);
struct InstructionResult op_ld_h_e(struct State* state);
struct InstructionResult op_ld_h_h(struct State* state);
struct InstructionResult op_ld_h_l(struct State* state);
//hl
struct InstructionResult op_ld_l_a(struct State* state);
struct InstructionResult op_ld_l_b(struct State* state);
struct InstructionResult op_ld_l_c(struct State* state);
struct InstructionResult op_ld_l_d(struct State* state);
struct InstructionResult op_ld_l_e(struct State* state);
struct InstructionResult op_ld_l_h(struct State* state);
struct InstructionResult op_ld_l_l(struct State* state);
//hl

// Load val to reg
struct InstructionResult op_ld_a_u8(struct State* state);
struct InstructionResult op_ld_b_u8(struct State* state);
struct InstructionResult op_ld_c_u8(struct State* state);
struct InstructionResult op_ld_d_u8(struct State* state);
struct InstructionResult op_ld_e_u8(struct State* state);
struct InstructionResult op_ld_h_u8(struct State* state);
struct InstructionResult op_ld_l_u8(struct State* state);


struct InstructionResult op_ld_hli_a(struct State* state);

struct InstructionResult op_ld_u16_a(struct State* state);

