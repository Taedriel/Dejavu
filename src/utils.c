#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void print_tuple(tuple_int* t, char* rep) {
    sprintf(rep, "%d %d", t->x, t->y);
}

tuple_int* copy_tuple_int(tuple_int o) {
    tuple_int* ret = malloc(sizeof(tuple_int));
    ret->x = o.x;
    ret->y = o.y;

    return ret;
}