#ifndef RACING_WEIGHTED_MAP_H
#define RACING_WEIGHTED_MAP_H

weighted_map_t *init_weighted_map(int height, int width, tuple_int start);

void pre_weight_map(weighted_map_t * weighted_map, map_t *map, tuple_int **endpos, int size_list_endpos);

void fill_speed_map(map_t map, weighted_map_t * weighted_map, tuple_int start_pos, float current_acc);

void weight_map(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int **endpos, int size_list_endpos, car_t cars[3]);

float **init_accel_map(int height, int width);

#endif