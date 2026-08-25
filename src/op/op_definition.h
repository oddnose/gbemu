#pragma once 

#include <stdint.h>
#include "state.h"

struct OpDefinition {
	char* format_name;
	uint8_t length;
	void(*callback)(struct State*);
};

