#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

struct player{
    int x, y, ele; // ele is tile-level precision, not square-level
    //int hp, str…
    //itemlist* inv;
};

struct player player;

void move_player(enum direction);

#endif
