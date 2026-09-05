#include "display.h"
#include <stdio.h>

void write_pixel(unsigned char color_index)
{
	const char* palette[] = {"█", "▒", "░", " "};
	printf("%s%s", palette[color_index], palette[color_index]); //Print twice to form block
	//printf("%d", color_index);
}

void write_h_blank()
{
	printf("\n");
}

void write_v_blank()
{
	printf("\n ===== VBLANK =====\n");
}
