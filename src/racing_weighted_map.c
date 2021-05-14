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

float ** init_accel_map(int height, int width) {

    int i;
    float **acceleration = malloc(sizeof(float *) * height);
    for (i = 0; i < height; i++) {
        acceleration[i] = malloc(sizeof(int) * width);
        for (int j = 0; j < width; j++) {
            acceleration[i][j] = 0;
        }
    }

    return acceleration;
}

weighted_map_t *init_weighted_map(int height, int width, tuple_int start) {
    int i;
    weighted_map_t *ret = malloc(sizeof(weighted_map_t));

    int **came_from = malloc(sizeof(int *) * height);
    float **dist_from_end = malloc(sizeof(float *) * height);
    float **heuristique = malloc(sizeof(float *) * height);
    float **cout = malloc(sizeof(float *) * height);

    for (i = 0; i < height; i++) {
        came_from[i] = malloc(sizeof(int) * width);
        dist_from_end[i] = malloc(sizeof(float) * width);
        heuristique[i] = malloc(sizeof(float) * width);
        cout[i] = malloc(sizeof(float) * width);
        for (int j = 0; j < width; j++) {
            came_from[i][j] = -1;
            dist_from_end[i][j] = -1.;
            heuristique[i][j] = -1.;
            cout[i][j] = -1.;
        }
    }

    cout[start.y][start.x] = 0;
    heuristique[start.y][start.x] = 0;

    ret->came_from = came_from;
    ret->dist_from_end = dist_from_end;
    ret->heuristique = heuristique;
    ret->cout = cout;

    return ret;
}

void fill_speed_map(map_t map, float ** to_map, tuple_int start_pos, float current_speed) {
    
    if (current_speed == 0) {
        return;
    }
    int i;
    
    to_map[start_pos.y][start_pos.x] = current_speed;

    list * neighboor = get_valid_neighbor(map.width, map.height, start_pos);
    for (i = 0; i < neighboor->size; i++) {
        fill_speed_map(map, to_map, *((tuple_int *) get_list(neighboor, i)), current_speed - DELTA_SPEED);
    }
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
    list * neighboor;

    tuple_int *temp;
    tuple_int * current_pos = malloc(sizeof(tuple_int));

    for (i = 0; i < size_list_endpos; i++) {
        temp = copy_tuple_int(*(endpos[i]));
        weighted_map->dist_from_end[temp->y][temp->x] = 0.;
        add_queue(s, (void *)temp);
    }

    do {
        *current_pos = *((tuple_int *)(last_queue(s)));
        current_value = weighted_map->dist_from_end[current_pos->y][current_pos->x];

        neighboor = get_valid_neighbor(map->width, map->height, *current_pos);
        for (i = 0; i < neighboor->size; i++) {
            temp = copy_tuple_int(*((tuple_int *) get_list(neighboor, i)));
            if (map->array[temp->y][temp->x] != WALL_CHAR) {
                weight = current_value + 1;
                weight += (is_in_diagonal_from(*current_pos, *temp) ? 0.5 : 0);
                if (weighted_map->dist_from_end[temp->y][temp->x] > weight \
                 || weighted_map->dist_from_end[temp->y][temp->x] == -1) {
                    weighted_map->dist_from_end[temp->y][temp->x] = weight;
                    add_queue(s, (void *) temp);
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
void weight_map(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int **endpos, int size_list_endpos, car_t cars[3]) {
    int i, tempx, tempy;
    int exist_in_open = 0, exist_in_closed = 0;
    float current_weight = 0., heur = 0., cout = 0.;
    float *** list_acc_map = malloc(sizeof(float **) * 6);

    for (i = 0; i < 3; i++) {
        list_acc_map[2*i] = init_accel_map(map->height, map->width);
        fill_speed_map(*map, list_acc_map[2*i], *(cars[i].pos), cars[i].spe->x);
        list_acc_map[2*i+1] = init_accel_map(map->height, map->width);
        fill_speed_map(*map, list_acc_map[2*i+1], *(cars[i].pos), cars[i].spe->y);
    }

    sorted_list *openList = create_sorted_list();
    sorted_list_cell *temp_sorted;

    list *closedList = create_list();
    list_cell *temp;

    tuple_int *u = malloc(sizeof(tuple_int));
    tuple_int *v;
    list * neighboor;

    add_sorted_list(openList, (void *)(&start), weighted_map->heuristique[start.y][start.y]);

    while (!is_sorted_list_empty(openList)) {


        *u = *((tuple_int *)get_sorted_list(openList, 0, &current_weight));
        remove_sorted_list(openList, 0);
        // fprintf(stderr, "===========Current %d %d %d================\n", openList->size, u->x, u->y);
        for (i = 0; i < size_list_endpos; i++) {
            if (u->x == endpos[i]->x && u->y == endpos[i]->y) {
                return;
            }
        }

        neighboor = get_valid_neighbor(map->width, map->height, *u);
        for (i = 0; i < neighboor->size; i++) {
            v = copy_tuple_int(*((tuple_int *) get_list(neighboor, i)));
            // fprintf(stderr, "Neighbor: %d %d = %c\n", v->x, v->y, map->array[v->y][v->x]);

            if (map->array[v->y][v->x] != WALL_CHAR) {
                //not a wall
                exist_in_closed = 0;
                exist_in_open = 0;

                if (!is_list_empty(closedList)) {
                    // print_list(closedList, print_tuple, stderr);
                    temp = closedList->head;
                    while (temp != NULL) {
                        tempx = ((tuple_int *)(temp->x))->x;
                        tempy = ((tuple_int *)(temp->x))->y;
                        if (tempx == v->x && tempy == v->y) {
                            // fprintf(stderr, "\tFound tuple in closedList: %d (%d %d)\n", closedList->size, tempx, tempy);
                            exist_in_closed = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                }

                if (!(exist_in_closed)) {

                    cout = weighted_map->cout[u->y][u->x];
                    cout += (is_in_diagonal_from(*u, *v) ? 0.5 : 0);
                    switch (map->array[v->y][v->x]) {
                        case SAND_CHAR:
                            cout += 1.5;
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

                    // acc_diff = tuple_normed_to_int(*(car.acc));
                    // diff = acc_diff ^ tuple_to_int(*u, *v);
                    // float t = (hamming_weight(diff) / 2);
                    // // fprintf(stderr, "Surcout acc: %f\n", t);
                    // cout += t;
                    if (weighted_map->cout[v->y][v->x] == -1 || cout < weighted_map->cout[v->y][v->x]) {

                        weighted_map->came_from[v->y][v->x] = tuple_to_int(*u, *v);
                        weighted_map->cout[v->y][v->x] = cout;
                        weighted_map->heuristique[v->y][v->x] = heuristique(*weighted_map, *v, list_acc_map, cout);

                        if (!is_sorted_list_empty(openList)) {
                            temp_sorted = openList->head;
                            while (temp_sorted != NULL) {
                                tempx = ((tuple_int *)(temp_sorted->x))->x;
                                tempy = ((tuple_int *)(temp_sorted->x))->y;
                                if (tempx == v->x && tempy == v->y) {
                                    exist_in_open = 1;
                                    break;
                                }
                                temp_sorted = temp_sorted->next;
                            }
                        }

                        if (!exist_in_open) {
                            add_sorted_list(openList, (void *)v, heur);
                            // fprintf(stderr, "Ajout de nouvelle case de poid: %f %f\n", cout, heur);
                        }
                    }
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