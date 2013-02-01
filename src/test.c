#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include "screen.h"

void signalCatch(int sig){
    screen_free();
    exit(0);
}

int main(int argc, char* argv){
    char input;
    int x=1, y=1;
    int width, height;
    int turn = 0;
    struct sigaction sa;
    sa.sa_handler = &signalCatch;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    screen_init();

    get_screen_size(&width, &height);

    srand(time(NULL));
    x = rand() % width + 1;
    y = rand() % height + 1;
    set_cursor(x, y);
    putchar('@');


    while((input = getchar()) != EOF){
        get_screen_size(&width, &height);
        set_cursor(x, y);
        //putchar('.');
        if(x < width - 5)
            printf("HI :3");
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
                screen_free();
                return 0;
        }
        if(x > width){ x = width; }
        else if(x < 1){ x = 1; }
        if(y > height){ y = height; }
        else if(y < 1){ y = 1; }
        if(rand() % 10000 == 0){
            set_cursor(1,1);
            set_color(color(5,5,5));
            set_background(color(0,0,0));
            switch(rand() % 3){
                case 0:
                    puts("You hear the voice of Lucky: \"Hello!\"");
                    break;
                case 1:
                    puts("You hear flapping dog wings.");
                    break;
                case 2:
                    puts("You feel the comforting gaze of Lucky upon you.");
                    break;
            }
        }
        set_cursor(x, y);
        set_background(grey((int)sqrt(pow(x/2, 2)+pow(y, 2)) % 26));
        set_color(color(x%6, y%6, (x/6)%6));
        putchar('@');
        turn++;
    }
}
