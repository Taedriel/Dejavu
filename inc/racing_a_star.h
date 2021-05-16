#ifndef RACING_A_STAR_H
#define RACING_A_STAR_H

#include "racing_types.h"

weighted_map_t *init_weighted_map(int height, int width, tuple_int start);

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
void fill_proba_map(map_t map, weighted_map_t * weighted_map, tuple_int start_pos, car_t * car);

void weight_map(weighted_map_t *weighted_map, map_t *map, tuple_int start, list * endpos, car_t cars[3]);

float **init_accel_map(int height, int width);

#endif