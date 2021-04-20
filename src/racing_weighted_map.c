#include <assert.h>

#include "racing_types.h"
#include "racing_map.h"


/**
 * @brief init a weigthed_map structure that contain two float tab. One representing
 * the distance from the start, the other the distance from the end. That will
 * allow us to perform an A* later
 * 
 * @param height 
 * @param width 
 * @return weighted_map_t* 
 */
weighted_map_t * init_weighted_map(int height, int width) {
    int i, j;
    weighted_map_t * ret = malloc(sizeof(weighted_map_t));

    float ** dist_from_start = malloc(sizeof(float *) * height);
    float ** dist_from_end = malloc(sizeof(float *) * height);

    for (i = 0; i < height; i++) {
        dist_from_start[i] = malloc(sizeof(float) * width);
        dist_from_end[i] = malloc(sizeof(float) * width);
        for (int j = 0; j < width; j++) {
            dist_from_start[i][j] = -1.;
            dist_from_end[i][j] = -1.;
        }
    }

    ret->dist_from_start = dist_from_start;
    ret->dist_from_end = dist_from_end;

    return ret;
}


/**
 * @brief weigth the map given the startpos and a list of the endpos
 * 
 * @param map 
 * @param startpos 
 * @return weighted_map_t* 
 */
weighted_map_t * weight_map(map_t *map, tuple_int startpos, tuple_int * endpos, int size_list_endpos) {

    int i, current_value = 0;
    float weight;

    weighted_map_t * ret = init_weighted_map(map->height, map->width);
    queue *s = create_queue();

    tuple_int *temp;
    tuple_int neighboor[8];
    tuple_int current_pos;

    current_pos.x = startpos.x;
    current_pos.y = startpos.y;

    ret->dist_from_start[current_pos.y][current_pos.x] = 0.;
    temp = malloc(sizeof(tuple_int));
    memcpy(temp, &current_pos, sizeof(tuple_int));
    add(s, (void *) temp);

    do {
        current_pos = *((tuple_int *)(last(s)));
        current_value = ret->dist_from_start[current_pos.y][current_pos.x];

        get_valid_neighnoor(map->width, map->height, current_pos, neighboor);
        for (i = 0; i < 8; i++) {
            if (map->array[neighboor[i].y][neighboor[i].x] != WALL_CHAR) {
                switch (map->array[neighboor[i].y][neighboor[i].x]) {
                    case SAND_CHAR:
                        weight = current_value + 4;
                        break;

                    case END_CHAR:
                        weight = 0;
                        break;

                    case ROAD_CHAR:
                        __attribute__((fallthrough));
                    default:
                        weight = current_value + 1;
                        break;
                }
                if (ret->dist_from_start[neighboor[i].y][neighboor[i].x] > weight \
                 || ret->dist_from_start[neighboor[i].y][neighboor[i].x] == -1) {
                    ret->dist_from_start[neighboor[i].y][neighboor[i].x] = weight;
                    temp = malloc(sizeof(tuple_int));
                    memcpy(temp, &(neighboor[i]), sizeof(tuple_int));
                    add(s, (void *)temp);
                }
            }
        }

        free(&current_pos);
    }while (!is_queue_empty(s));

    free(temp);
    destroy_queue(s);
    return ret;
}