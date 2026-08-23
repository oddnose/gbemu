#ifndef OP_LOAD_INSTRUCTIONS_H
#define OP_LOAD_INSTRUCTIONS_H

#include "state.h"

void op_ld_sp_u16(struct State* state);
void op_ld_hl_minus_a(struct State* state);
void op_ld_hl_u16(struct State* state);

#endif
