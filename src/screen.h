#ifndef SCREEN_H
#define SCREEN_H
#include "map.h"

int screen_width, screen_height;
int color, background;

void screen_init(void);
void get_screen_size(int* w, int* h);
void set_term_opts(int buffer, int echo, int visible);
void screen_free(void);

void clear_screen(void);
void set_cursor(const int x, const int y);

int rgb(const int r, const int g, const int b);
int grey(const int b);
void set_color(const int c);
void set_background(const int c);
void draw_tile(struct tile*, const int x, const int y);

void redraw(void);
void resizeCatch(const int sig);
#endif
