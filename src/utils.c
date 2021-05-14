#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void print_tuple(void *t, char *rep) {
    sprintf(rep, "%d %d", ((tuple_int *)t)->x, ((tuple_int *)t)->y);
}

tuple_int *copy_tuple_int(tuple_int o) {
    tuple_int *ret = malloc(sizeof(tuple_int));
    ret->x = o.x;
    ret->y = o.y;

    return ret;
}

tuple_int *create_tuple_int(int a, int b) {
    tuple_int *ret = malloc(sizeof(tuple_int));
    ret->x = a;
    ret->y = b;

    return ret;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int min(int a, int b) {
    return a <= b ? a : b;
}

int dot_product(tuple_int *a, tuple_int *b, tuple_int *c) {
    return (b->x - a->x) * (c->y - b->y) - (b->y - a->y) * (c->x - b->x);
}

double distance(tuple_int a, tuple_int b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}