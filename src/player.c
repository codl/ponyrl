#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "screen.h"
#include "math.h"
#include "damage.h"

void move_player(enum direction direction){
    int x, y, ele;
    int xx, yy;
    struct square *from, *to;
    struct tile *tilefrom, *tileto;

    x = xx = player.x;
    y = yy = player.y;
    ele = player.ele;
    switch(direction){
        case(NW):
            xx = x - 1;
        case(N):
            yy = y - 1;
            break;
        case(SW):
            yy = y + 1;
        case(W):
            xx = x - 1;
            break;
        case(SE):
            xx = x + 1;
        case(S):
            yy = y + 1;
            break;
        case(NE):
            yy = y - 1;
        case(E):
            xx = x + 1;
            break;
    }
    tilefrom = get_tile(pos_div(x, TILESIZE), pos_div(y, TILESIZE), 0);
    if(pos_div(x, TILESIZE) == pos_div(xx, TILESIZE) && pos_div(y, TILESIZE) == pos_div(yy, TILESIZE))
        tileto = tilefrom;
    else
        tileto = get_tile(pos_div(xx, TILESIZE), pos_div(yy, TILESIZE), 0);
    from = tilefrom->type == Array? SQUARE(tilefrom->tile.sq, pos_mod(x, TILESIZE), pos_mod(y, TILESIZE)) : tilefrom->tile.fill;
    to = tileto->type == Array? SQUARE(tileto->tile.sq, pos_mod(xx, TILESIZE), pos_mod(yy, TILESIZE)) : tileto->tile.fill;
    // TODO handle elevation / going to adjacent layers
    if(to->c){
        // TODO FIGHT or do other things I guess
        hit(to->c,&player);
        putmsg("Pawnch!");
    }
    else {
        // try moving
        switch(to->terrain){
            case(TERRAIN_ROCK_WALL):
                putmsg("You bump into a wall.");
                break;
            default:
                from->c = 0;
                player.x = xx;
                player.y = yy;
                to->c = &player;
                draw_map(xx, yy, ele);
        }
    }
}

void pick_up(void){
    struct itemlist* i = get_square(player.x, player.y, player.ele)->i;
    if(!i){
        putmsg("There is nothing to pick up here.");
    }
    else {
        // TODO what would you like to pick up? blabla
    }
}
