#ifndef H_RACING_CHECKPOINTS_INCLUDED
#define H_RACING_CHECKPOINTS_INCLUDED

#include "utils.h"

stack *remove_useless_points(stack *traj);

double segment_len(tuple_int **tab, int tab_size, int index);

int get_weight_checkpoint(tuple_int **tab, int tab_size, int index, weighted_map_t *weighted_map);

int get_segment_by_coord(tuple_int **tab, int tab_size, weighted_map_t *weighted_map, tuple_int * coord);

int get_segment(tuple_int **tab, int tab_size, weighted_map_t *weighted_map, car_t *car);

#endif