#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include "screen.h"

void get_screen_size(int* w, int* h){
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);
    if(w) *w = ws.ws_col;
    if(h) *h = ws.ws_row;
    screen_width = ws.ws_col;
    screen_height = ws.ws_row;
}

void clear_screen(void){
    puts("\033[2J");
}

void set_cursor(const int x, const int y){
    printf("\033[%d;%dH", y, x);
}

void set_term_opts(int buffer, int echo, int visible){
    struct termios t;
    tcgetattr(0, &t);
    if(buffer){
        t.c_lflag |= ICANON;
    } else {
        t.c_lflag &= (unsigned) ~ICANON;
        t.c_cc[VMIN] = 1;
        t.c_cc[VTIME] = 0;
    }
    if(echo){
        t.c_lflag |= ECHO;
    } else {
        t.c_lflag &= (unsigned) ~ECHO;
    }
    if(visible){
        puts("\033[?25h");
    } else {
        puts("\033[?25l");
    }
    tcsetattr(0, TCSANOW, &t);
}

void redraw(void){
    //NOOP
}

void resizeCatch(const int sig){
    if(sig == SIGWINCH){
        get_screen_size(0,0);
        redraw();
    }
}

void screen_init(void){
    set_term_opts(0, 0, 0);
    clear_screen();
    get_screen_size(NULL, NULL);
    color = 0;
    background = 1;
    struct sigaction sa;
    sa.sa_handler = &resizeCatch;
    sa.sa_flags = 0;
    sigaction(SIGWINCH, &sa, NULL);
}

void screen_free(void){
    set_term_opts(1, 1, 1);
    set_cursor(1, screen_height);
    puts("\033[0m");
}

int rgb(const int r, const int g, const int b){
    return 16 + 36*r + 6*g + b;
}

int grey(const int b){
    if(b==0) return 16;
    if(b==25) return 231;
    return 232 + b - 1;
}

void set_color(const int c){
    if(color != c){
        printf("\033[38;5;%dm", c);
        color = c;
    }
}

void set_background(const int c){
    if(background != c){
        printf("\033[48;5;%dm", c);
        background = c;
    }
}

void draw_map(const int centerx, const int centery, const int ele){
    int x, y;
    x = (centerx - screen_width/2)/TILESIZE*TILESIZE;
    if(x <= 0) x -= TILESIZE;
    for(; x < centerx + screen_width/2 + TILESIZE; x+=TILESIZE){
        y = (centery - screen_height/2)/TILESIZE*TILESIZE;
        if(y <= 0) y -= TILESIZE;
        for(; y < centery + screen_height/2 + TILESIZE; y+=TILESIZE){
            draw_tile(get_tile(x/TILESIZE, y/TILESIZE, ele), x - centerx + screen_width/2, y - centery + screen_height/2);
        }
    }
}

void draw_tile(struct tile* t, const int x, const int y){
    if(t->type == Fill)
        return;
        //TODO
    int xx, yy;
    get_screen_size(0, 0);
    for(yy = 0; yy < TILESIZE; yy++){
        set_cursor(x, y+yy);
        for(xx = 0; xx < TILESIZE; xx++){
            if(x + xx < 1 || x + xx > screen_width ||
                    y + yy < 1 || y + yy > screen_height){
                continue;
            }
            draw_square(SQUARE(t->tile.sq, xx, yy), x + xx, y + yy);
        }
    }
}

void draw_square(struct square* sq, const int x, const int y){
    srand((unsigned int) (map.seed + (sq->x ^ (sq->y * TILESIZE))));
    set_cursor(x, y);
    switch(sq->terrain){
        case TERRAIN_WATER:
            set_background(rgb(0,2,5));
            putchar(' ');
            break;
        case TERRAIN_GRASS:
            set_background(grey(0));
            if(rand() % 15 == 0){
                set_color(rgb(0,rand()%5+1,0));
                putchar(",."[rand()%2]);
            }
            else
                putchar(' ');
            break;
        case TERRAIN_ROCK:
            set_background(grey(0));
            if(rand() % 4 == 0){
                set_color(grey(rand()%10 + 5));
                putchar(",."[rand()%2]);
            }
            else
                putchar(' ');
            break;
        case TERRAIN_ROCK_WALL:
            set_background(grey(15));
            putchar(' ');
            break;
    }
}
