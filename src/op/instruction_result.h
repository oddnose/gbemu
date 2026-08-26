#pragma once

#include "state.h"

struct InstructionResult {
	unsigned char cycles;
	unsigned char num_memory_updates;
	struct MemoryUpdate* updates;
};
