#pragma once

#include "op/instruction_result.h"
#include "state.h"

struct InstructionResult op_bit_7_h(struct State* state);
struct InstructionResult op_rl_c(struct State* state);
struct InstructionResult op_rla(struct State* state);

struct InstructionResult op_srl_a(struct State* state);
struct InstructionResult op_srl_b(struct State* state);
struct InstructionResult op_srl_c(struct State* state);
struct InstructionResult op_srl_d(struct State* state);
struct InstructionResult op_srl_e(struct State* state);
struct InstructionResult op_srl_h(struct State* state);
struct InstructionResult op_srl_l(struct State* state);
struct InstructionResult op_srl_hl_addr(struct State* state);

