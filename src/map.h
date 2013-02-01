#ifndef MAP_H
#define MAP_H

#include "terrain.h"

#define TILESIZE 64

#define square(sq,x,y) ((sq) + (y) * TILESIZE + (x))

struct square{
    unsigned int terrain : 2;
    unsigned int elevation : 3;
    // something like itemlist* i; creature* c; entity* e;
};

struct tile{
    enum { Full, Empty } type;
    union{
        int terrain;
        struct square* sq;
    } tile;
};

void fill_tile(struct square* sq, int terrain);

#endif
