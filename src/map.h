#ifndef MAP_H
#define MAP_H

#include "terrain.h"
#include "item.h"
#include "creature.h"

#define TILESIZE 64
#define TERRAINSIZE 2 // 0-3
#define ELESIZE 3 // 0-7

#define SQUARE(sq,x,y) ((sq) + (y) * TILESIZE + (x))

enum direction{ N, NE, E, SE, S, SW, W, NW };

struct square{
    unsigned int terrain :TERRAINSIZE;
    unsigned int elevation :ELESIZE;
    long x, y;
    struct itemlist* i;
    struct creature* c;
    /*entity* e;*/
};

struct tile{
    enum { Array, Fill } type;
    int x, y, ele;
    union{
        struct square* fill;
        struct square* sq;
    } tile;
};

struct tilelist{
    struct tile* tile;
    struct tilelist* next;
};

struct map{
    int seed;
    struct tilelist* tiles;
};

struct map map;

void init_map(void);

struct tile* get_tile(int x, int y, int ele);
struct tile* gen_tile(int x, int y, int ele);
void fill_tile(struct square* sq, unsigned int terrain);

void free_tile(struct tile* t);

void gc_map(void);

#endif
