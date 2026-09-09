#include "cpu.h"
#include "ppu.h"
#include "state.h"
#include <stdio.h>

struct State* state;
struct Cpu* cpu;
struct Ppu* ppu;

int main() 
{
	state = create_state();
	cpu = create_cpu();
	ppu = create_ppu();

	load_rom(state, "res/01-special.gb");
	load_rom(state, "res/dmg.bin");

	FILE* ptr = fopen("doctor-output.txt", "w");
	fprintf(ptr, "%s", "");
	fclose(ptr);

	//set_gb_doctor_start(state);
	//print_gb_doctor_debug(state);

	while (true) {
		cpu_tick(cpu, state);
		ppu_tick(ppu, state);
	}
}
