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
