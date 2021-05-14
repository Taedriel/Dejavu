#ifndef RACING_ALGORITHM_H
#define RACING_ALGORITHM_H

#include "racing_types.h"

list * get_valid_neighbor(int width, int height, tuple_int startpos);

float heuristique(weighted_map_t weighted_map, tuple_int current_pos);

list *find_path(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int ** endpos, int size);

tuple_int ** find_end(map_t map, int * size);

int tuple_to_int(tuple_int origine, tuple_int dest);

int tuple_normed_to_int(tuple_int a);

int hamming_weight(int x);

tuple_int *int_to_tuple(int entier);

#endif