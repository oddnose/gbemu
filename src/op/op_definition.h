#pragma once 

#include <stdint.h>
#include "state.h"

struct OpDefinition {
	uint8_t length;
	void(*callback)(struct State*);
};

