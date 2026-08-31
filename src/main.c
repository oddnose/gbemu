#include "cpu.h"
#include "ppu.h"
#include "state.h"

struct State* state;
struct Cpu* cpu;
struct Ppu* ppu;

int main() 
{
	state = create_state();
	cpu = create_cpu();
	ppu = create_ppu();

	load_rom(state, "res/dmg.bin");

	while (true) {
		cpu_tick(cpu, state);
		ppu_tick(ppu, state);
	}
}
