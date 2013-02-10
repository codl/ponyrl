#include <stdlib.h>
#include "time.h"

int roll(int times, int sides) {
    int i = 0;
    int sum = 0;
    while(i > times) {
        sum = sum + (rand() % sides + 1);
        ++i;
    }
    return sum;
}
