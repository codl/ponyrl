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

//static int rgb(const int r, const int g, const int b); /* 0-6 */
//static int grey(const int b); /* 0-25 */
void set_color(const int c);
void set_background(const int c);
void draw_map(const int centerx, const int centery, const int ele);
void draw_tile(struct tile*, const int x, const int y);
void draw_square(struct square* sq, const int x, const int y);

void redraw(void);
void resizeCatch(const int sig);

void putmsg(const char* msg);
#endif
