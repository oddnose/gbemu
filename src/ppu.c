#include "ppu.h"
#include "display.h"
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
	unsigned short map_start_addr;
	unsigned short tile_start_addr;
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
	switch (ppu->ppu_state) {
		case OAMSearch: { // Mode 2
			if (ppu->cycle_count == 20) { // OAM always takes 20 cycles
				// Read the LCD Control register which controls what elements are displayed on the screen
				unsigned char lcdc = read_addr(state, 0xFF40);
				ppu->map_start_addr = (lcdc & 0b01000000) == 0 ? 0x9800 : 0x9C00;
				ppu->tile_start_addr = (lcdc & 0b00010000) == 0 ? 0x8800 : 0x8000;

				ppu->ppu_state = PixelTransfer;
			}
			break;
		}
		//TODO: Doesn't emulate proper FIFO logic. Instead we just print the whole scan-line at once in one cycle
		case PixelTransfer: { // Mode 3
			unsigned char ly = read_addr(state, 0xFF44);

			unsigned char x_pos = 0; //TODO: could be affected by shifting
			unsigned char tile_line = ly % 8; // current line inside tile
			unsigned short tile_index = ppu->cycle_count + (ly / 8) * 32; // the map contains 32 rows of tiles

			while (x_pos < 160) {
				unsigned char tile_id = read_addr(state, tile_index);
				unsigned short tile_addr = ppu->tile_start_addr + tile_id * 16; // each tile is 16 bytes 

				unsigned char low_byte = read_addr(state, tile_addr + tile_line * 2); // 2 bytes per row
				unsigned char high_byte = read_addr(state, tile_addr + tile_line * 2 + 1);

				for (int i = 0; i < 8 && x_pos < 160; i++, x_pos++) {
					unsigned char bit = 7 - i;

					// Each pixel is composed of 2 bits. In both bytes, bit 7 represents the leftmost pixel and so forth.
					// See pandocs 4.1
					unsigned char pixel = ((high_byte >> bit) & 1) << 1 | ((low_byte >> bit) & 1);

					write_pixel(pixel);
				}

				tile_index++;
			}

			ppu->ppu_state = HBlank;

			break;
		}
		case HBlank: { // Mode 0

			if (ppu->cycle_count == 114) { //line end
				ppu->cycle_count = 0;
				unsigned char ly = read_addr(state, 0xFF44);
				write_addr(state, 0xFF44, ly + 1);
				//printf("Update LY: %d\n", ly + 1);

				if (ly + 1 == 144) {
					ppu->ppu_state = VBlank;
				} else {
					ppu->ppu_state = OAMSearch;
				}
				write_h_blank();
			}
			break;
		}
		case VBlank: { // Mode 1
			if (ppu->cycle_count == 114) { //line end
				ppu->cycle_count = 0;
				unsigned char ly = read_addr(state, 0xFF44);

				if (ly == 153) {
					write_addr(state, 0xFF44, 0);
					//printf("Update LY: %d\n", 0);

					ppu->ppu_state = OAMSearch;
					write_v_blank();
				} else {
					write_addr(state, 0xFF44, ly + 1);
					//printf("Update LY: %d\n", ly + 1);

				}
			}

			break;
		}
	}
}
