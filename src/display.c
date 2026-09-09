#include "display.h"
#include <SDL_events.h>
#include <SDL_hints.h>
#include <SDL_pixels.h>
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

	uint32_t frame_buffer[160 * 144];

	uint32_t palette[4];
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

	display->texture = SDL_CreateTexture(display->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, col_count, row_count);

	display->palette[0] = 0xFFFFFFFF; // white 
	display->palette[1] = 0xFFC0C0C0; // light gray 
	display->palette[2] = 0xFF606060; // dark gray 
	display->palette[3] = 0xFF000000; // black

	display->x = 0;
	display->y = 0;

	return display;
}

void write_pixel(struct Display* display, unsigned char color_index)
{
	if (display->x >= col_count || display->y >= row_count) {
		fprintf(stderr, "Pixel OOB: x=%u y=%u\n",
						display->x, display->y);
		abort();
	}
	display->frame_buffer[display->y * col_count + display->x] = display->palette[color_index];
	display->x++;
}

void write_h_blank(struct Display* display)
{
	display->x = 0;
	display->y++;
}

void write_v_blank(struct Display* display)
{
	SDL_UpdateTexture(display->texture, NULL, display->frame_buffer, col_count * sizeof(uint32_t));
	SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
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
