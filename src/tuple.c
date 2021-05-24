#include "tuple.h"

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

tuple_int create_0_0_tuple() {
    tuple_int tuple = {0, 0};
    return tuple;
}

void print_tuple(void *t, char *rep) {
    sprintf(rep, "%d %d", ((tuple_int *)t)->x, ((tuple_int *)t)->y);
}

int _in(tuple_int **liste, int size, tuple_int elem) {
    int i;

    for (i = 0; i < size; i++) {
        if (liste[i]->x == elem.x && liste[i]->y == elem.y) {
            return 1;
        }
    }

    return 0;
}

tuple_int *int_to_tuple(int entier) {
    tuple_int *ret = create_tuple_int(0, 0);
    int diff;
    ret->x = (entier >> 4) == 2 ? -1 : (entier >> 4);
    diff = entier - ((int)(entier >> 4) << 4);
    ret->y = diff == 2 ? -1 : diff;

    return ret;
}

int tuple_to_int(tuple_int origine, tuple_int dest) {
    int deltaX = origine.x - dest.x;
    int deltaY = origine.y - dest.y;
    return ((deltaX < 0 ? 2 : deltaX == 0 ? 0
                                          : 1)
            << 4) |
           (deltaY < 0 ? 2 : deltaY == 0 ? 0
                                         : 1);
}

int tuple_normed_to_int(tuple_int a) {
    return ((a.x < 0 ? 2 : a.x == 0 ? 0
                                    : 1)
                << 4 |
            (a.y < 0 ? 2 : a.y == 0 ? 0
                                    : 1));
}