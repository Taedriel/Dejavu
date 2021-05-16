#ifndef RACING_ALGORITHM_H
#define RACING_ALGORITHM_H

#include "racing_types.h"

/**
 * @brief return the 4 (or less) neighnoor that are crossable of a case of the map
 * 
 * @param map 
 * @param startpos 
 */
list * get_valid_neighbor(int width, int height, tuple_int startpos);

float heuristique(weighted_map_t weighted_map, tuple_int current_pos, float *** liste_map_accel, float cout);

list *find_path(weighted_map_t *weighted_map, map_t *map, tuple_int start, list * endpos);

/**
 * @brief return a list of coord that are the end of the track
 * 
 * @param map 
 * @param size 
 * @return tuple_int** 
 */
list * find_end(map_t map);

int tuple_to_int(tuple_int origine, tuple_int dest);

int tuple_normed_to_int(tuple_int a);

int hamming_weight(int x);

int is_in_diagonal_from(tuple_int start, tuple_int dest);

tuple_int *int_to_tuple(int entier);

#endif