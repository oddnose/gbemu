#pragma once 

#include <stdint.h>
#include "op/instruction_result.h"
#include "state.h"

struct OpDefinition {
	char* format_name;
	unsigned char length;
	struct InstructionResult(*callback)(struct State*);
	unsigned char cycles;
};

