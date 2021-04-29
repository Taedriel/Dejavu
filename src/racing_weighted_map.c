#include <assert.h>

#include "racing_algorithm.h"
#include "racing_map.h"
#include "racing_types.h"
#include "utils.h"

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
weighted_map_t *pre_weight_map(map_t *map, tuple_int startpos, tuple_int **endpos, int size_list_endpos) {
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

    } while (!is_queue_empty(s));

    free(current_pos);
    free(temp);
    destroy_queue(s);
    return ret;
}

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
void weight_map(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int end) {
    int i, tempx, tempy;
    int exist_in_open_wlc = 0, exist_in_closed = 0;
    float current_weight = 0., weight = 0., score = 0.;

    sorted_list *openList = create_sorted_list();
    sorted_list_cell *temp_sorted;
    list *closedList = create_list();
    list_cell *temp;

    tuple_int *u = malloc(sizeof(tuple_int));
    tuple_int *v = malloc(sizeof(tuple_int));
    tuple_int *temptuple;
    tuple_int neighboor[8];

    add_sorted_list(openList, (void *)(&start), 0);

    while (!is_sorted_list_empty(openList)) {
        *u = *((tuple_int *)get_sorted_list(openList, 0, &current_weight));
        remove_sorted_list(openList, 0);
        if (u->x == end.x && u->y == end.y) {
            return;
        }

        get_valid_neighbor(map->width, map->height, *u, neighboor);
        for (i = 0; i < 8; i++) {
            v = malloc(sizeof(tuple_int));
            v->x = neighboor[i].x;
            v->y = neighboor[i].y;
            fprintf(stderr, "Neighbor: %d %d ...\n", v->x, v->y);

            if (map->array[v->y][v->x] != -1) {
                //not a wall
                exist_in_closed = 0;
                exist_in_open_wlc = 0;

                if (!is_sorted_list_empty(openList)) {
                    //print_sorted_list(openList, print_tuple, stderr);
                    temp_sorted = openList->head;
                    while (temp_sorted != NULL) {
                        tempx = ((tuple_int *)(temp_sorted->x))->x;
                        tempy = ((tuple_int *)(temp_sorted->x))->y;
                        if (tempx == v->x && tempy == v->y) {
                            if (weighted_map->cout[tempy][tempx] != -1 && weighted_map->cout[tempy][tempx] < current_weight) {
                                exist_in_open_wlc = 1;
                                break;
                            }
                        }
                        temp_sorted = temp_sorted->next;
                    }
                }

                if (!is_list_empty(closedList)) {
                    //print_list(closedList, print_tuple, stderr);
                    temp = closedList->head;
                    while (temp != NULL) {
                        tempx = ((tuple_int *)(temp->x))->x;
                        tempy = ((tuple_int *)(temp->x))->y;
                        if (tempx == v->x && tempy == v->y) {
                            //fprintf(stderr, "Found tuple in closedList: %d (%d %d)\n", closedList->size, tempx, tempy);
                            exist_in_closed = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                }

                if (!(exist_in_open_wlc || exist_in_closed)) {
                    //fprintf(stderr, "Ajout de nouvelle case\n");
                    switch (map->array[neighboor[i].y][neighboor[i].x]) {
                        case SAND_CHAR:
                            weight = 4;
                            break;

                        case END_CHAR:
                            weight = 0;
                            break;

                        case ROAD_CHAR:
                            __attribute__((fallthrough));
                        default:
                            weight = 1;
                            break;
                    }

                    weighted_map->cout[v->y][v->x] = weight;
                    score = weight * heuristique(*weighted_map, *v);
                    add_sorted_list(openList, (void *)v, score);
                }
            }
        }

        temptuple = malloc(sizeof(tuple_int));
        memcpy(temptuple, u, sizeof(tuple_int));
        add_list(closedList, (void *)temptuple);
    }

    destroy_list(closedList);
    destroy_sorted_list(openList);
    /*
    free(temptuple);
    free(u);
    free(v);
    */

    return;
}