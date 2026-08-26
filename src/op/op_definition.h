#pragma once 

#include <stdint.h>
#include "op/instruction_result.h"
#include "state.h"

struct OpDefinition {
	char* format_name;
	uint8_t length;
	struct InstructionResult(*callback)(struct State*);
};

