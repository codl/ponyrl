#include "math.h"

int pos_mod(int a, int b){
    return a%b >= 0? a%b : a%b + b;
}

int pos_div(int a, int b){
    return (a - pos_mod(a, b)) / b;
}
