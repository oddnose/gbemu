#pragma once

#include "state.h"

struct Ppu;

struct Ppu* create_ppu();

void ppu_tick(struct Ppu* ppu, struct State* state);
