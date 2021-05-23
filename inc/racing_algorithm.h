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

/**
 * @brief Compute the heuristic of a point
 * 
 * @param weighted_map 
 * @param current_pos 
 * @param liste_map_accel 
 * @param cout 
 * @return float 
 */
float heuristique(weighted_map_t weighted_map, tuple_int current_pos, float *** liste_map_accel, float cout);

/**
 * @brief Convert an int into a tuple
 * 
 * @param entier 
 * @return tuple_int* 
 */
tuple_int *int_to_tuple(int entier);

/**
 * @brief Convert a tuple into an int
 * 
 * @param origine 
 * @param dest 
 * @return int 
 */
int tuple_to_int(tuple_int origine, tuple_int dest);

/**
 * @brief Compute the hamming weight
 * 
 * @param x 
 * @return int 
 */
int hamming_weight(int x);

/**
 * @brief transform a normed tupled into the same format than relative_pos
 * 
 * @param a 
 * @return int 
 */
int tuple_normed_to_int(tuple_int a);

/**
 * @brief Check if the two points aren't paralleles to an axis
 * 
 * @param start 
 * @param dest 
 * @return int 
 */
int is_in_diagonal_from(tuple_int start, tuple_int dest);

/**
 * @brief Find the path
 * 
 * @param weighted_map 
 * @param map 
 * @param start 
 * @param endpos 
 * @return list* 
 */
list *find_path(weighted_map_t *weighted_map, map_t *map, tuple_int start, list * endpos);

/**
 * @brief return a list of coord that are the end of the track
 * 
 * @param map 
 * @param size 
 * @return tuple_int** 
 */
list * find_end(map_t map);


#endif