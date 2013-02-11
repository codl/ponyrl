#include <stdlib.h>
#include "map.h"

void fill_tile(struct square* sq, unsigned int terrain){
    int x, y;
    for(x = 0; x < TILESIZE; x++)
        for(y = 0; y < TILESIZE; y++){
            SQUARE(sq, x, y)->terrain = terrain & 3;
            SQUARE(sq, x, y)->elevation = 0;
            SQUARE(sq, x, y)->c = 0;
            SQUARE(sq, x, y)->i = 0;
        }
}

void init_map(void){
    map.seed = rand();
    map.tiles = NULL;
}

struct tile* get_tile(int x, int y, int ele){
    struct tilelist* list = map.tiles;
    struct tile* tile;
    while(list != NULL){
        if(list->tile->x == x &&
                list->tile->y == y &&
                list->tile->ele == ele)
            return list->tile;
        list = list->next;
    }
    tile = gen_tile(x, y, ele);
    return tile;
}
struct tile* gen_tile(int x, int y, int ele){
    int xx, yy;
    //srand(map.seed ^ x ^ y ^ ele);
    struct tile* tile = malloc(sizeof(struct tile));
    struct tilelist* list = malloc(sizeof(struct tilelist));
    tile->x = x;
    tile->y = y;
    tile->ele = ele;
    // v TODO
    tile->type = Array;
    tile->tile.sq = malloc(sizeof(struct square) * TILESIZE * TILESIZE);
    fill_tile(tile->tile.sq, TERRAIN_GRASS);
    for(xx = 0; xx < TILESIZE; xx++)
        for(yy = 0; yy < TILESIZE; yy++){
            SQUARE(tile->tile.sq, xx, yy)->x = x*TILESIZE + xx;
            SQUARE(tile->tile.sq, xx, yy)->y = y*TILESIZE + yy;
        }
    SQUARE(tile->tile.sq, 10, 10)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 11, 10)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 12, 10)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 13, 10)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 14, 10)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 15, 10)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 15, 11)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 15, 12)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 15, 13)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 14, 13)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 13, 13)->terrain = TERRAIN_ROCK_WALL;
    // door lel
    SQUARE(tile->tile.sq, 11, 13)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 10, 13)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 10, 12)->terrain = TERRAIN_ROCK_WALL;
    SQUARE(tile->tile.sq, 10, 11)->terrain = TERRAIN_ROCK_WALL;
    for(xx = 11; xx <= 14; xx++)
        for(yy = 11; yy <= 12; yy++)
            SQUARE(tile->tile.sq, xx, yy)->terrain = TERRAIN_ROCK;
    // ^ TODO
    list->tile = tile;
    list->next = map.tiles;
    map.tiles = list;
    gc_map();
    return tile;
}

void free_tile(struct tile* t){
    if(t->type == Array){
        free(t->tile.sq);
    }
    free(t);
}

void gc_map(void){
    int counter = 0;
    struct tilelist* list = map.tiles;
    struct tilelist* next;
    while(list){
        counter++;
        next = list->next;
        if(counter == 100){
            list->next = NULL;
        }
        else if (counter > 100) {
            free_tile(list->tile);
            free(list);
        }
        list = next;
    }
}
