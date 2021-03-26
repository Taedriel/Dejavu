#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void print_tuple(tuple_int* t, char * rep) {
    sprintf(rep, "%d %d", t->x, t->y);
}