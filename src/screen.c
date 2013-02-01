#include <stdio.h>
#include <sys/ioctl.h>
#include "screen.h"
#include <termios.h>

void get_screen_size(int* width, int* height){
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);
    *width = ws.ws_col;
    *height = ws.ws_row;
}

void clear_screen(){
    puts("\033[2J");
}

void set_cursor(int x, int y){
    printf("\033[%d;%dH", y, x);
}

void set_term_opts(int buffer, int echo, int visible){
    struct termios t;
    tcgetattr(0, &t);
    if(buffer){
        t.c_lflag |= ICANON;
    } else {
        t.c_lflag &= ~ICANON;
        t.c_cc[VMIN] = 1;
        t.c_cc[VTIME] = 0;
    }
    if(echo){
        t.c_lflag |= ECHO;
    } else {
        t.c_lflag &= ~ECHO;
    }
    if(visible){
        puts("\033[?25h");
    } else {
        puts("\033[?25l");
    }
    tcsetattr(0, TCSANOW, &t);
}

void screen_init(){
    set_term_opts(0, 0, 0);
    clear_screen();
}

void screen_free(){
    int width, height;
    get_screen_size(&width, &height);
    set_term_opts(1, 1, 1);
    set_cursor(1, height);
    puts("\033[0m");
}

int color(int r, int g, int b){
    return 16 + 36*r + 6*g + b;
}

int grey(int b){
    if(b==0) return 16;
    if(b==25) return 231;
    return 232 + b - 1;
}

void set_color(int c){
    printf("\033[38;5;%dm", c);
}

void set_background(int c){
    printf("\033[48;5;%dm", c);
}
