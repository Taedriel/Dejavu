#ifndef H_RACING_MAP_INCLUDED
#define H_RACING_MAP_INCLUDED

#include "racing_types.h"

void init_map(struct map_t *map, int height, int width);

void print_map(struct map_t *map, FILE *file);

void print_map_path(map_t *map, tuple_int ** path, int path_size, FILE *file);

void print_weighted_map(float ** map, int width, int height, FILE * file);


#endif