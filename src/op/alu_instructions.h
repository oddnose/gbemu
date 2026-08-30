#pragma once

#include "op/instruction_result.h"
#include "state.h"

struct InstructionResult op_xor_a_a(struct State* state);

struct InstructionResult op_inc_a(struct State* state);
struct InstructionResult op_inc_b(struct State* state);
struct InstructionResult op_inc_c(struct State* state);
struct InstructionResult op_inc_d(struct State* state);
struct InstructionResult op_inc_e(struct State* state);
struct InstructionResult op_inc_h(struct State* state);
struct InstructionResult op_inc_l(struct State* state);
struct InstructionResult op_inc_hl_addr(struct State* state);

struct InstructionResult op_inc_bc(struct State* state);
struct InstructionResult op_inc_de(struct State* state);
struct InstructionResult op_inc_hl(struct State* state);
struct InstructionResult op_inc_sp(struct State* state);

struct InstructionResult op_dec_a(struct State* state);
struct InstructionResult op_dec_b(struct State* state);
struct InstructionResult op_dec_c(struct State* state);
struct InstructionResult op_dec_d(struct State* state);
struct InstructionResult op_dec_e(struct State* state);
struct InstructionResult op_dec_h(struct State* state);
struct InstructionResult op_dec_l(struct State* state);
struct InstructionResult op_dec_hl_addr(struct State* state);

struct InstructionResult op_cp_a_uint8(struct State* state);

