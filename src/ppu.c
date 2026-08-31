#include "ppu.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

enum PpuState {
	OAMSearch,
	PixelTransfer,
	HBlank,
	VBlank
};

struct Ppu {
	enum PpuState ppu_state;

	//TODO: To be able to support double speed mode dots should be counted instead of cycles
	unsigned short cycle_count;
};

struct Ppu* create_ppu()
{
	struct Ppu* ppu = malloc(sizeof *ppu);

	ppu->ppu_state = OAMSearch;
	ppu->cycle_count = 0;

	return ppu;
}

void ppu_tick(struct Ppu* ppu, struct State* state)
{
	ppu->cycle_count++;
	//printf("ppu cycle count: %d\n", ppu->cycle_count);
	switch (ppu->ppu_state) {
		case OAMSearch: {
			//printf("OAMSearch\n");

			if (ppu->cycle_count == 20) {
				ppu->ppu_state = PixelTransfer;
			}
			break;
		}
		case PixelTransfer: {
			//printf("PixelTransfer\n");

			if (ppu->cycle_count == 63) { //TODO: could vary
				ppu->ppu_state = HBlank;
			}
			break;
		}
		case HBlank: {
			//printf("HBlank\n");

			if (ppu->cycle_count == 114) { //line end
				ppu->cycle_count = 0;
				unsigned char ly = read_addr(state, 0xFF44);
				write_addr(state, 0xFF44, ly + 1);
				printf("Update LY: %d\n", ly + 1);

				if (ly + 1 == 144) {
					ppu->ppu_state = VBlank;
				} else {
					ppu->ppu_state = OAMSearch;
				}
			}
			break;
		}
		case VBlank: {
			//printf("VBlank\n");
			if (ppu->cycle_count == 114) { //line end
				ppu->cycle_count = 0;
				unsigned char ly = read_addr(state, 0xFF44);

				if (ly == 153) {
					write_addr(state, 0xFF44, 0);
					printf("Update LY: %d\n", 0);

					ppu->ppu_state = OAMSearch;
				} else {
					write_addr(state, 0xFF44, ly + 1);
					printf("Update LY: %d\n", ly + 1);

				}
			}

			break;
		}
	}
}
