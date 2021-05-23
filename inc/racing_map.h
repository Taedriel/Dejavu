#ifndef H_RACING_MAP_INCLUDED
#define H_RACING_MAP_INCLUDED

#include "racing_types.h"

/**
 * @brief init the map struct given the first input of a race
 *        ! Must be used ! => else buffer pb  
 * 
 * @param map 
 * @param height 
 * @param width 
 */
void init_map(struct map_t *map, int height, int width);

/**
 * @brief print the map
 * 
 * @param map 
 * @param file 
 */
void print_map(struct map_t *map, FILE *file);

/**
 * @brief print the map but with a path
 * 
 * @param map 
 * @param file 
 */
void print_map_path(map_t *map, tuple_int ** path, int path_size, FILE *file);

/**
 * @brief print the map weighted as a float map
 * 
 * @param map 
 * @param width 
 * @param height 
 * @param file 
 */
void print_float_weighted_map(float ** map, int width, int height, FILE * file);

/**
 * @brief print the map weighted as a int map
 * 
 * @param map 
 * @param width 
 * @param height 
 * @param file 
 */
void print_int_weighted_map(int **map, int width, int height, FILE *file);

#endif