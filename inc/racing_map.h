#ifndef H_RACING_MAP_INCLUDED
#define H_RACING_MAP_INCLUDED

#include "racing_types.h"

void init_map(struct map_t *map, int height, int width);

void print_map(struct map_t *map, FILE *file);

void print_map_path(map_t *map, tuple_int ** path, int path_size, FILE *file);

void print_weighted_map(int ** map, int width, int height, FILE * file);

void get_valid_neighnoor(int width, int height, tuple_int startpos, tuple_int *neighboor);

int ** parse_map(map_t * map, tuple_int startpos);

tuple_int ** find_path(int ** weighted_map, map_t * map, int * path_size, tuple_int start, tuple_int end);

tuple_int ** find_end(map_t map, int * size);

#endif