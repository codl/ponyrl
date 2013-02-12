#include <stdlib.h>
#include "roll.h"
#include "time.h"

int roll(int times, int sides) {
    int i;
    int sum = 0;
    for(i = 0; i < times; i++) {
        sum = sum + (rand() % sides + 1);
    }
    return sum;
}

