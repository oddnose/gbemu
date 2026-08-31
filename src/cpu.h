#pragma once

#include "state.h"

struct Cpu;

struct Cpu* create_cpu();

void cpu_tick(struct Cpu* cpu, struct State* state);
