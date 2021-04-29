#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void print_tuple(void * t, char* rep) {
    sprintf(rep, "%d %d", ((tuple_int *) t)->x, ((tuple_int *)t)->y);
}

tuple_int* copy_tuple_int(tuple_int o) {
    tuple_int* ret = malloc(sizeof(tuple_int));
    ret->x = o.x;
    ret->y = o.y;

    return ret;
}

int max (int a, int b) {
    return a >= b ? a : b;
}

int min (int a, int b) {
    return a <= b ? a : b;
}