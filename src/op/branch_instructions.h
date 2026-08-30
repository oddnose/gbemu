#pragma once

#include "op/instruction_result.h"
#include "state.h"

struct InstructionResult op_jr_i8(struct State* state);
struct InstructionResult op_jr_nz_i8(struct State* state);
struct InstructionResult op_jr_z_i8(struct State* state);

struct InstructionResult op_call_u16(struct State* state);
struct InstructionResult op_push_bc(struct State* state);
struct InstructionResult op_pop_bc(struct State* state);
struct InstructionResult op_ret(struct State* state);
