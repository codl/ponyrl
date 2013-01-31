#include <stdio.h>
#include <sys/ioctl.h>
#include "screen.h"
#include <termios.h>

void getScreenSize(int* width, int* height){
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    *width = ws.ws_col;
    *height = ws.ws_row;
}

void clearScreen(){
    puts("\033[2J");
}

void setCursorPos(int x, int y){
    printf("\033[%d;%dH", y, x);
}

void setTermOpts(int buffer, int echo, int visible){
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
