#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include "screen.h"
#include "map.h"
#include "terrain.h"
#include "test.h"

void signalCatch(int s){
    if(s){
        screen_free();
        exit(0);
    }
}

int main(void){
    int input;
    int x, y;
    int xx, yy, xxx, yyy;
    int width, height;
    struct tile my_super_fancy_tile;
    struct sigaction sa;
    sa.sa_handler =  &signalCatch;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    screen_init();

    get_screen_size(&width, &height);

    srand((unsigned int)time(NULL));
    x = rand() % width + 1;
    y = rand() % height + 1;
    set_cursor(x, y);
    putchar('@');

    my_super_fancy_tile.type = Full;
    my_super_fancy_tile.tile.sq = malloc(sizeof(struct square) * TILESIZE * TILESIZE); // this will be done by the map generator / loader
    if(my_super_fancy_tile.tile.sq == NULL){
        perror(NULL);
        screen_free();
        exit(1);
    }
    fill_tile(my_super_fancy_tile.tile.sq, TERRAIN_GRASS);
    xx = rand() % TILESIZE-4 + 2;
    yy = rand() % TILESIZE-4 + 2;
    for(yyy = yy - 2; yyy <= yy + 2; yyy++){
        for(xxx = xx - 2; xxx <= xx + 2; xxx++){
            square(my_super_fancy_tile.tile.sq, xxx, yyy)->terrain = TERRAIN_WATER;
        }
    }

    xx = rand() % TILESIZE-6 + 2;
    yy = rand() % TILESIZE-6 + 2;
    for(yyy = yy - 3; yyy <= yy + 2; yyy++){
        square(my_super_fancy_tile.tile.sq, xx-3, yyy)->terrain = TERRAIN_ROCK_WALL;
        square(my_super_fancy_tile.tile.sq, xx+2, yyy)->terrain = TERRAIN_ROCK_WALL;
    }
    for(xxx = xx - 3; xxx <= xx + 2; xxx++){
        square(my_super_fancy_tile.tile.sq, xxx, yy-3)->terrain = TERRAIN_ROCK_WALL;
        square(my_super_fancy_tile.tile.sq, xxx, yy+2)->terrain = TERRAIN_ROCK_WALL;
    }

    draw_tile(&my_super_fancy_tile, 1, 1);




    while(1){
        input = getchar();
        get_screen_size(&width, &height);
        set_color(grey((int)sqrt(pow(x/2, 2)+pow(y, 2)) % 26));
        set_background(rgb(x%6, y%6, (x/6)%6));
        set_cursor(x, y);
        putchar('%');
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
            set_color(grey(25));
            set_background(grey(0));
            switch(rand() % 3){
                case 0:
                    puts("You hear the voice of Lucky. \"Hello, adventurer!\"");
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
        set_background(grey(0));
        set_color(grey(20));
        putchar('@');
    }
}
