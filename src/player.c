#include "player.h"
#include "screen.h"
#include "math.h"

void move_player(enum direction direction){
    int x, y, ele;
    int xx, yy;
    struct square /**from,*/ *to;
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
    //from = tilefrom->type == Array? SQUARE(tilefrom->tile.sq, x % TILESIZE, y % TILESIZE) : tilefrom->tile.fill;
    to = tileto->type == Array? SQUARE(tileto->tile.sq, pos_mod(xx, TILESIZE), pos_mod(yy, TILESIZE)) : tileto->tile.fill;
    // TODO handle elevation / going to adjacent layers
    // also TODO put the player in the square
    switch(to->terrain){
        case(TERRAIN_ROCK_WALL):
            //log("You bump into a wall.")
            break;
        default:
            player.x = xx;
            player.y = yy;
            draw_map(xx, yy, ele);
    }
}
