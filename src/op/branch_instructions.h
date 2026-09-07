#pragma once

#include "op/instruction_result.h"
#include "state.h"

struct InstructionResult op_nop(struct State* state);

struct InstructionResult op_jr_i8(struct State* state);
struct InstructionResult op_jr_nz_i8(struct State* state);
struct InstructionResult op_jr_z_i8(struct State* state);
struct InstructionResult op_jr_nc_i8(struct State* state);
struct InstructionResult op_jr_c_i8(struct State* state);

struct InstructionResult op_call_u16(struct State* state);
struct InstructionResult op_call_nz_u16(struct State* state);

struct InstructionResult op_ret(struct State* state);
struct InstructionResult op_ret_nz(struct State* state);
struct InstructionResult op_ret_z(struct State* state);
struct InstructionResult op_ret_nc(struct State* state);
struct InstructionResult op_ret_c(struct State* state);

struct InstructionResult op_jp_u16(struct State* state);

struct InstructionResult op_di(struct State* state);


