#include <stdio.h>
#include <signal.h>
#include "screen.h"
#include <errno.h>

void signalCatch(int sig){
    setTermOpts(1, 1, 1);
    exit(0);
}

int main(int argc, char* argv){
    char input;
    int x=1, y=1;
    int width, height;
    struct sigaction sa;

    clearScreen();

    sa.sa_handler = &signalCatch;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    setTermOpts(0, 0, 0);
    while((input = getchar()) != EOF){
        getScreenSize(&width, &height);
        setCursorPos(x, y);
        putchar(' ');
        switch(input){
            case 'h':
                x--;
                break;
            case 'j':
                y++;
                break;
            case 'k':
                y--;
                break;
            case 'l':
                x++;
                break;
            case 'y':
                x--; y--;
                break;
            case 'u':
                x++; y--;
                break;
            case 'n':
                x++; y++;
                break;
            case 'b':
                x--; y++;
                break;
            case 'q':
                setTermOpts(1, 1, 1);
                return 0;
        }
        if(x > width){ x = width; }
        else if(x < 1){ x = 1; }
        if(y > height){ y = height; }
        else if(y < 1){ y = 1; }
        setCursorPos(x, y);
        putchar('@');
    }
}
