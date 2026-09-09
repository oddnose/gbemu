#pragma once

#include "state.h"

struct InstructionResult {
	unsigned char cycles;
	struct MemoryUpdate updates[6]; // No instruction has more than 6 updates
};
