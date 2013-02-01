#include <stdlib.h>
#include "map.h"

void fill_tile(struct square* sq, int terrain){
    int x, y;
    for(x = 0; x < TILESIZE; x++){
        for(y = 0; y < TILESIZE; y++){
            square(sq, x, y)->terrain = terrain;
        }
    }
}
