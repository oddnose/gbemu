#include <stdio.h>
#include "op/cb_lookup.h"
#include "op/op_definition.h"
#include "state.h"
#include "op/op_lookup.h"

struct State* state;


void print_instruction(struct OpDefinition def, uint8_t pos)
{
	printf("%04x\t", pos);
	for (uint8_t i = 0; i < def.length; i++) {
		printf("%02x ", read_char(state, pos + i));
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
			printf(def.format_name, read_char(state, pos + 1));
			break;
		}
		case 2: {
			printf(def.format_name, read_short(state, pos + 1));
			break;
		}
	}
	printf("\n");
}

int main()
{
	state = create_state();
	load_rom(state, "res/dmg.bin");
	uint8_t pos = 0;
	for (int i = 0; i < 10; i++) {
	//while (read_pc(state) < 0x3FFF) {
		struct OpDefinition def;
		def = decode(state, read_pc(state));
		print_instruction(def, read_pc(state));
		if (!def.callback) {
			printf("Instruction not implemented!");
		}
		def.callback(state);
	}
}
