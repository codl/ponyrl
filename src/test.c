#include <stdio.h>
#include "screen.h"

int main(int argc, char* argv){
    char input;
    int x=1, y=1;
    int width, height;
    clearScreen();
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
