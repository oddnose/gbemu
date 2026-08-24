#pragma once

#include "state.h"

void op_ld_sp_u16(struct State* state);
void op_ld_hl_minus_a(struct State* state);
void op_ld_hl_u16(struct State* state);
void op_ld_c_u8(struct State* state);
void op_ld_a_u8(struct State* state);
void op_ld_ff00_plus_c_a(struct State* state);
