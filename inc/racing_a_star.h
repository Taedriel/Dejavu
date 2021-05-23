#ifndef RACING_A_STAR_H
#define RACING_A_STAR_H

#include "racing_types.h"

/**
 * @brief Initialize the weighted map
 * 
 * @param height 
 * @param width 
 * @param start 
 * @return weighted_map_t* 
 */
weighted_map_t *init_weighted_map(int height, int width, tuple_int start);

/**
 * @brief calcul the dist to endpos for each case
 * 
 * @param map 
 * @param startpos 
 * @return weighted_map_t* 
 */
void pre_weight_map(weighted_map_t * weighted_map, map_t *map, list * endpos);

/**
 * @brief fill a map with number between 0 and 1 that represent the proba of the 
 * car to be on this case next turn. The more you change your acc, the less it's probable
 * e.g. if your car has a 1 0 accel, and need to change to 0 0 to go on this case, the proba is 
 * 1/5 less time by the hamming weight of the diff between the acc. Here, it would be 1 * 1/5 less.
 * 
 * @param map 
 * @param weighted_map 
 * @param start_pos 
 * @param car 
 */
void fill_proba_map(map_t map, weighted_map_t * weighted_map, car_t * car);

/**
 * @brief perform A*
 * 
 * @param weighted_map 
 * @param map 
 * @param path_size 
 * @param start 
 * @param end 
 * @return tuple_int** 
 */
void weight_map(weighted_map_t *weighted_map, map_t *map, tuple_int start, list * endpos, car_t cars[3]);

/**
 * @brief reset all costs
 * 
 * @param weighted_map 
 * @param map 
 */
void reset_cost(weighted_map_t *weighted_map, map_t map);

/**
 * @brief init a weigthed_map structure that contain two float tab. One representing
 * the distance from the start, the other the distance from the end. That will
 * allow us to perform an A* later
 * 
 * @param height 
 * @param width 
 * @return weighted_map_t* 
 */
float **init_accel_map(int height, int width);

#endif