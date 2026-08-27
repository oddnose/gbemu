#pragma once

#include "op/instruction_result.h"
#include "state.h"

struct InstructionResult op_ld_sp_u16(struct State* state);
struct InstructionResult op_ld_hld_a(struct State* state);
struct InstructionResult op_ld_hl_u16(struct State* state);
struct InstructionResult op_ld_c_u8(struct State* state);
struct InstructionResult op_ld_a_u8(struct State* state);
struct InstructionResult op_ld_ff00_plus_c_a(struct State* state);
struct InstructionResult op_ld_hl_a(struct State* state);
struct InstructionResult op_ld_ff00_plus_u8_a(struct State* state);
struct InstructionResult op_ld_b_a(struct State* state);
struct InstructionResult op_ld_de_u16(struct State* state);
struct InstructionResult op_ld_a_de(struct State* state);
struct InstructionResult op_ld_c_a(struct State* state);
struct InstructionResult op_ld_b_u8(struct State* state);
