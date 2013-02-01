#ifndef SCREEN_H
#define SCREEN_H
#include "map.h"

int screen_width, screen_height;
int color, background;

void screenInit();
void screenFree();
void getScreenSize(int* width, int* height);
void set_cursor(int x, int y);

int rgb(int r, int g, int b);
int gret(int b);
void set_color(int c);
void set_background(int c);
void draw_tile(struct tile*, int x, int y);
#endif
