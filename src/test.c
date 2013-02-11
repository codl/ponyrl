#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include "screen.h"
#include "map.h"
#include "terrain.h"
#include "test.h"
#include "player.h"

void signalCatch(int s){
    if(s){
        screen_free();
        exit(0);
    }
}

int main(void){
    int input;
    int width, height;
    struct sigaction sa;
    sa.sa_handler =  &signalCatch;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    screen_init();

    get_screen_size(&width, &height);

    srand((unsigned int)time(NULL));
    init_map();

    player.x = 1;
    player.y = 1;
    player.ele = 0;
    player.type = CREA_EARTH_PONY;
    player.inv = 0;
    player.health = 1;

    SQUARE(get_tile(0,0,0)->tile.sq, 1,1)->c = &player;

    draw_map(1,1,0);

    while(1){
        input = getchar();
        switch(input){
            case 'h':
                move_player(W);
                break;
            case 'j':
                move_player(S);
                break;
            case 'k':
                move_player(N);
                break;
            case 'l':
                move_player(E);
                break;
            case 'y':
                move_player(NW);
                break;
            case 'u':
                move_player(NE);
                break;
            case 'n':
                move_player(SE);
                break;
            case 'b':
                move_player(SW);
                break;
            case 'q':
                screen_free();
                return 0;
        }
    }
}
