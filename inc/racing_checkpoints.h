#ifndef H_RACING_CHECKPOINTS_INCLUDED
#define H_RACING_CHECKPOINTS_INCLUDED

#include "utils.h"

/**
 * @brief Supress all points that are aligned with the begin and the end of a line.
 * 
 * @param traj 
 * @return stack* 
 */
stack *remove_useless_points(stack *traj);

/**
 * @brief Return the length of a segment between two checkpoints
 * 
 * @param checkpoint 
 * @param checkpoint_size 
 * @param index 
 * @return double 
 */
double segment_len(list * list_checkpoint, int index);

/**
 * @brief Get the weight of a checkpoint
 * 
 * @param checkpoint 
 * @param checkpoint_size 
 * @param index 
 * @param weighted_map 
 * @return int 
 */
int get_weight_checkpoint(tuple_int **checkpoint, int checkpoint_size, int index, weighted_map_t *weighted_map);

/**
 * @brief Get the segment index by coord 
 * 
 * @param checkpoint 
 * @param checkpoint_size 
 * @param weighted_map 
 * @param coord 
 * @return int 
 */
int get_segment_by_coord(tuple_int **checkpoint, int checkpoint_size, weighted_map_t *weighted_map, tuple_int *coord);

/**
 * @brief Get the segment index on which the car is
 * 
 * @param checkpoint 
 * @param checkpoint_size 
 * @param weighted_map 
 * @param car 
 * @return int 
 */
int get_segment(tuple_int **checkpoint, int checkpoint_size, weighted_map_t *weighted_map, car_t *car);

#endif