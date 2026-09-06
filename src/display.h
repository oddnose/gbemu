#pragma once

struct Display;

struct Display* create_display();
void write_pixel(struct Display* display, unsigned char color_index);
void write_h_blank(struct Display* display);
void write_v_blank(struct Display* display);
