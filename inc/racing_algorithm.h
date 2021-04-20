#ifndef RACING_ALGORITHM_H
#define RACING_ALGORITHM_H

#include "racing_types.h"

void get_valid_neighnoor(int width, int height, tuple_int startpos, tuple_int *neighboor);

int ** parse_map(map_t * map, tuple_int startpos);

tuple_int ** find_path(int ** weighted_map, map_t * map, int * path_size, tuple_int start, tuple_int end);

tuple_int ** find_end(map_t map, int * size);


#endif