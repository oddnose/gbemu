#include <stdio.h>
#include "op/cb_lookup.h"
#include "op/op_definition.h"
#include "state.h"
#include "op/op_lookup.h"

struct State state;
const unsigned int rom_memory_end = 0x3FFF;

void load_rom()
{
	FILE *ptr;
	ptr = fopen("res/dmg.bin", "rb");
	fread(state.memory, rom_memory_end, 1, ptr);
}

void print_instruction(struct OpDefinition def, uint8_t pos)
{
	printf("%04x\t", pos);
	for (uint8_t i = 0; i < def.length; i++) {
		printf("%02x ", state.memory[pos + i]);
	}

	if (def.length == 3) {
		printf("\t");
	} else {
		printf("\t\t");
	}

	switch (def.length - 1) {
		case 0: {
			printf("%s", def.format_name);
			break;
		}
		case 1: {
			printf(def.format_name, state.memory[pos + 1]);
			break;
		}
		case 2: {
			printf(def.format_name, ((unsigned short) state.memory[pos + 2] << 8) | state.memory[pos + 1]);
			break;
		}
	}
	printf("\n");
}

int main()
{
	load_rom();
	uint8_t pos = 0;
	while (state.program_counter < rom_memory_end) {
		struct OpDefinition def;
		def = decode(&state, state.program_counter);
		print_instruction(def, state.program_counter);
		if (!def.callback) {
			printf("Instruction not implemented!");
		}
		def.callback(&state);
	}
}
