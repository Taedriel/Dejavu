#include <assert.h>

#include "racing_algorithm.h"
#include "racing_map.h"
#include "racing_types.h"

/**
 * @brief init a weigthed_map structure that contain two float tab. One representing
 * the distance from the start, the other the distance from the end. That will
 * allow us to perform an A* later
 * 
 * @param height 
 * @param width 
 * @return weighted_map_t* 
 */
weighted_map_t *init_weighted_map(int height, int width) {
    int i;
    weighted_map_t *ret = malloc(sizeof(weighted_map_t));

    float **heuristique = malloc(sizeof(float *) * height);
    float **cout = malloc(sizeof(float *) * height);

    for (i = 0; i < height; i++) {
        heuristique[i] = malloc(sizeof(float) * width);
        cout[i] = malloc(sizeof(float) * width);
        for (int j = 0; j < width; j++) {
            heuristique[i][j] = -1.;
            cout[i][j] = -1.;
        }
    }

    ret->heuristique = heuristique;
    ret->cout = cout;

    return ret;
}

/**
 * @brief weigth the map given the startpos and a list of the endpos
 * 
 * @param map 
 * @param startpos 
 * @return weighted_map_t* 
 */
weighted_map_t *weight_map(map_t *map, tuple_int startpos, tuple_int **endpos, int size_list_endpos) {
    int i, current_value = 0;
    float weight;

    weighted_map_t *ret = init_weighted_map(map->height, map->width);
    queue *s = create_queue();

    tuple_int *temp;
    tuple_int neighboor[8];
    tuple_int * current_pos = malloc(sizeof(tuple_int));

    for (i = 0; i < size_list_endpos; i++) {
        temp = malloc(sizeof(tuple_int));
        temp->x = endpos[i]->x;
        temp->y = endpos[i]->y;
        ret->heuristique[temp->y][temp->x] = 0.;
        add_queue(s, (void *)temp);
    }

    do {
        *current_pos = *((tuple_int *)(last_queue(s)));
        current_value = ret->heuristique[current_pos->y][current_pos->x];

        get_valid_neighbor(map->width, map->height, *current_pos, neighboor);
        for (i = 0; i < 8; i++) {
            if (map->array[neighboor[i].y][neighboor[i].x] != WALL_CHAR) {
                weight = current_value + 1 + (i >= 4 ? 0.5 : 0);
                if (ret->heuristique[neighboor[i].y][neighboor[i].x] > weight || ret->heuristique[neighboor[i].y][neighboor[i].x] == -1) {
                    ret->heuristique[neighboor[i].y][neighboor[i].x] = weight;
                    temp = malloc(sizeof(tuple_int));
                    temp->x = neighboor[i].x;
                    temp->y = neighboor[i].y;
                    add_queue(s, (void *)temp);
                }
            }
        }

        free(current_pos);
    } while (!is_queue_empty(s));

    free(temp);
    destroy_queue(s);
    return ret;
}