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
weighted_map_t *init_weighted_map(int height, int width, tuple_int start) {
    int i;
    weighted_map_t *ret = malloc(sizeof(weighted_map_t));

    float **dist_from_end = malloc(sizeof(float *) * height);
    float **heuristique = malloc(sizeof(float *) * height);
    float **cout = malloc(sizeof(float *) * height);

    for (i = 0; i < height; i++) {
        dist_from_end[i] = malloc(sizeof(float) * width);
        heuristique[i] = malloc(sizeof(float) * width);
        cout[i] = malloc(sizeof(float) * width);
        for (int j = 0; j < width; j++) {
            dist_from_end[i][j] = -1.;
            heuristique[i][j] = -1.;
            cout[i][j] = -1.;
        }
    }

    cout[start.y][start.x] = 0;

    ret->dist_from_end = dist_from_end;
    ret->heuristique = heuristique;
    ret->cout = cout;

    return ret;
}

/**
 * @brief calcul the dist to endpos for each case
 * 
 * @param map 
 * @param startpos 
 * @return weighted_map_t* 
 */
void pre_weight_map(weighted_map_t * weighted_map, map_t *map, tuple_int **endpos, int size_list_endpos) {
    int i, current_value = 0;
    float weight;

    queue *s = create_queue();

    tuple_int *temp;
    tuple_int neighboor[8];
    tuple_int * current_pos = malloc(sizeof(tuple_int));

    for (i = 0; i < size_list_endpos; i++) {
        temp = copy_tuple_int(*(endpos[i]));
        weighted_map->dist_from_end[temp->y][temp->x] = 0.;
        add_queue(s, (void *)temp);
    }

    do {
        *current_pos = *((tuple_int *)(last_queue(s)));
        current_value = weighted_map->dist_from_end[current_pos->y][current_pos->x];

        get_valid_neighbor(map->width, map->height, *current_pos, neighboor);
        for (i = 0; i < 8; i++) {
            if (map->array[neighboor[i].y][neighboor[i].x] != WALL_CHAR) {
                weight = current_value + 1 + (i >= 4 ? 0.5 : 0);
                if (weighted_map->dist_from_end[neighboor[i].y][neighboor[i].x] > weight \
                 || weighted_map->dist_from_end[neighboor[i].y][neighboor[i].x] == -1) {
                    weighted_map->dist_from_end[neighboor[i].y][neighboor[i].x] = weight;
                    temp = copy_tuple_int(neighboor[i]);
                    add_queue(s, (void *)temp);
                }
            }
        }

    } while (!is_queue_empty(s));

    free(current_pos);
    free(temp);
    destroy_queue(s);
    return;
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
void weight_map(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int **endpos, int size_list_endpos) {
    int i, tempx, tempy;
    int exist_in_open_wlc = 0, exist_in_closed = 0;
    float current_weight = 0., heur = 0., cout = 0.;

    sorted_list *openList = create_sorted_list();
    sorted_list_cell *temp_sorted;
    list *closedList = create_list();
    list_cell *temp;

    tuple_int *u = malloc(sizeof(tuple_int));
    tuple_int *v;
    tuple_int neighboor[8];

    add_sorted_list(openList, (void *)(&start), weighted_map->heuristique[start.y][start.y]);

    while (!is_sorted_list_empty(openList)) {
        *u = *((tuple_int *)get_sorted_list(openList, 0, &current_weight));
        remove_sorted_list(openList, 0);
        fprintf(stderr, "===========Current %d %d %d================\n", openList->size, u->x, u->y);
        for (i = 0; i < size_list_endpos; i++) {
            if (u->x == endpos[i]->x && u->y == endpos[i]->y) {
                return;
            }
        }

        get_valid_neighbor(map->width, map->height, *u, neighboor);
        for (i = 0; i < 8; i++) {
            v = copy_tuple_int(neighboor[i]);
            fprintf(stderr, "Neighbor: %d %d = %c\n", v->x, v->y, map->array[v->y][v->x]);

            if (map->array[v->y][v->x] != WALL_CHAR) {
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
                                fprintf(stderr, "\tFound tuple in openList: %d (%d %d)\n", openList->size, tempx, tempy);
                                exist_in_open_wlc = 1;
                                break;
                            }
                        }
                        temp_sorted = temp_sorted->next;
                    }
                }

                if (!is_list_empty(closedList)) {
                    // print_list(closedList, print_tuple, stderr);
                    temp = closedList->head;
                    while (temp != NULL) {
                        tempx = ((tuple_int *)(temp->x))->x;
                        tempy = ((tuple_int *)(temp->x))->y;
                        if (tempx == v->x && tempy == v->y) {
                            fprintf(stderr, "\tFound tuple in closedList: %d (%d %d)\n", closedList->size, tempx, tempy);
                            exist_in_closed = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                }

                if (!(exist_in_open_wlc || exist_in_closed)) {
                    cout = weighted_map->cout[u->y][u->x];
                    cout += (i >= 4 ? 0.5 : 0);
                    switch (map->array[neighboor[i].y][neighboor[i].x]) {
                        case SAND_CHAR:
                            cout += 2;
                            break;

                        case END_CHAR:
                            cout += 0;
                            break;

                        case ROAD_CHAR:
                            __attribute__((fallthrough));
                        default:
                            cout += 1;
                            break;
                    }

                    weighted_map->cout[v->y][v->x] = cout;
                    heur = cout + weighted_map->dist_from_end[v->y][v->x];
                    weighted_map->heuristique[v->y][v->x] = heur;
                    add_sorted_list(openList, (void *)v, heur);
                    fprintf(stderr, "Ajout de nouvelle case de poid: %f %f\n", cout, heur);
                }
            }
        }

        add_list(closedList, (void *)copy_tuple_int(*u));
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