#ifndef RACING_WEIGHTED_MAP_H
#define RACING_WEIGHTED_MAP_H

weighted_map_t * init_weighted_map(int height, int width);

weighted_map_t * weight_map(map_t *map, tuple_int startpos, tuple_int ** endpos, int size_list_endpos);

#endif