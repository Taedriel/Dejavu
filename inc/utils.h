#ifndef H_UTILS_INCLUDED
#define H_UTILS_INCLUDED

#include "racing_types.h"

int max(int a, int b);

int min(int a, int b);

int dot_product(tuple_int *a, tuple_int *b, tuple_int *c);

double distance(tuple_int a, tuple_int b);

int is_in_sand(map_t *map, car_t *car);

#endif