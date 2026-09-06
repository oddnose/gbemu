#include "display.h"
#include <SDL_events.h>
#include <SDL_hints.h>
#include <SDL_render.h>
#include <stdlib.h>
#include "SDL.h"

static const unsigned short col_count = 160;
static const unsigned short row_count = 144;
static const unsigned char scale = 6;

struct Display {
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Texture* texture;

	unsigned short x;
	unsigned short y;

	Uint8 palette[4][3];
};

struct Display* create_display()
{
	struct Display* display = malloc(sizeof *display);

	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	SDL_CreateWindowAndRenderer(col_count, row_count, 0, &display->window, &display->renderer);
	SDL_SetWindowSize(display->window, col_count * scale, row_count * scale);
	SDL_SetWindowResizable(display->window, SDL_FALSE);

	SDL_RenderSetLogicalSize(display->renderer, col_count, row_count);

	SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);
	SDL_RenderClear(display->renderer);

	unsigned char palette[4][3] = {
			{255, 255, 255}, // color 0
			{192, 192, 192}, // color 1
			{96,  96,  96 }, // color 2
			{0,   0,   0  }  // color 3
	};
	memcpy(display->palette, palette, sizeof palette);

	return display;
}

void write_pixel(struct Display* display, unsigned char color_index)
{
	Uint8 r = display->palette[color_index][0];
	Uint8 g = display->palette[color_index][1];
	Uint8 b = display->palette[color_index][2];

	SDL_SetRenderDrawColor(display->renderer, r, g, b, 255);
	SDL_RenderDrawPoint(display->renderer, display->x, display->y);

	display->x++;
}

void write_h_blank(struct Display* display)
{
	display->x = 0;
	display->y++;
}

void write_v_blank(struct Display* display)
{
	SDL_RenderPresent(display->renderer);

	display->x = 0;
	display->y = 0;

	//TODO: Find better place
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			exit(0);
		}
	}
}
