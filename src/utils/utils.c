#include "utils.h"

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

int is_in_sand(map_t *map, car_t *car) {
    return (map->array[car->pos->y][car->pos->x] == SAND_CHAR);
}

int hamming_weight(int x) {
    int ret = 0;
    while (x > 0) {
        ret += x & 1;
        x = x >> 1;
    }
    return ret;
}

int is_in_diagonal_from(tuple_int start, tuple_int dest) {
    return abs(start.x - dest.x) > 0 && abs(start.y - dest.y) > 0;
}
