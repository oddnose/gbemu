#include <stdio.h>
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

int main()
{
	load_rom();
	while (state.program_counter <= rom_memory_end) {
		run_op(&state);
	}
}
