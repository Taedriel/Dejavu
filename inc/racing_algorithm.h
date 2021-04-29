#ifndef RACING_ALGORITHM_H
#define RACING_ALGORITHM_H

#include "racing_types.h"

void get_valid_neighbor(int width, int height, tuple_int startpos, tuple_int *neighboor);

float heuristique(weighted_map_t weighted_map, tuple_int current_pos);

list *find_path(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int end);

tuple_int ** find_end(map_t map, int * size);


#endif