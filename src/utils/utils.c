#include "utils.h"

inline int max(int a, int b) {
    return a >= b ? a : b;
}

inline int min(int a, int b) {
    return a <= b ? a : b;
}

inline int dot_product(tuple_int *a, tuple_int *b, tuple_int *c) {
    return (b->x - a->x) * (c->y - b->y) - (b->y - a->y) * (c->x - b->x);
}

inline int pow_int_2(int a) {
    return a*a;
}

inline double distance(tuple_int a, tuple_int b) {
    return sqrt(pow_int_2(b.x - a.x) + pow_int_2(b.y - a.y));
}

inline int is_in_sand(map_t *map, car_t *car) {
    return (map->array[car->pos->y][car->pos->x] == SAND_CHAR);
}

inline int hamming_weight(int x) {
    int ret = 0;
    while (x > 0) {
        ret += x & 1;
        x = x >> 1;
    }
    return ret;
}

inline int is_in_diagonal_from(tuple_int start, tuple_int dest) {
    return abs(start.x - dest.x) > 0 && abs(start.y - dest.y) > 0;
}
