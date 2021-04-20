#include <assert.h>

#include "racing_map.h"
#include "racing_types.h"
#include "utils.h"

/**
 * @brief return the 4 (or less) neighnoor that are crossable of a case of the map
 * 
 * @param map 
 * @param startpos 
 */
void get_valid_neighbor(int width, int height, tuple_int startpos, tuple_int *neighboor) {
    if ((startpos.x + 1) < width) {
        if (startpos.y >= 0 && startpos.y < height) {
            neighboor[0].x = startpos.x + 1;
            neighboor[0].y = startpos.y;
        }
    }
    if ((startpos.x - 1) >= 0) {
        if (startpos.y >= 0 && startpos.y < height) {
            neighboor[1].x = startpos.x - 1;
            neighboor[1].y = startpos.y;
        }
    }
    if ((startpos.y + 1) < height) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[2].x = startpos.x;
            neighboor[2].y = startpos.y + 1;
        }
    }
    if ((startpos.y - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[3].x = startpos.x;
            neighboor[3].y = startpos.y - 1;
        }
    }
    if ((startpos.y - 1) >= 0 && (startpos.x - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[4].x = startpos.x - 1;
            neighboor[4].y = startpos.y - 1;
        }
    }
    if ((startpos.y - 1) >= 0 && (startpos.x + 1) < width) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[5].x = startpos.x + 1;
            neighboor[5].y = startpos.y - 1;
        }
    }
    if ((startpos.y + 1) < height && (startpos.x + 1) < width) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[6].x = startpos.x + 1;
            neighboor[6].y = startpos.y + 1;
        }
    }
    if ((startpos.y + 1) < height && (startpos.x - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[7].x = startpos.x - 1;
            neighboor[7].y = startpos.y + 1;
        }
    }
}

float heuristique(weighted_map_t weighted_map, tuple_int current_pos) {
    return weighted_map.heuristique[current_pos.y][current_pos.x];
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
list *find_path(weighted_map_t *weighted_map, map_t *map, int *path_size, tuple_int start, tuple_int end) {
    int i;
    int exist_in_open_wlc = 0, exist_in_closed = 0;
    float current_weight = 0., weight = 0., score = 0.;

    sorted_list *openList = create_sorted_list();
    sorted_list_cell *temp_sorted;
    list_cell *temp;
    list *closedList = create_list();

    tuple_int *u = copy_tuple_int(end);
    tuple_int *v = malloc(sizeof(tuple_int));
    tuple_int *temptuple = malloc(sizeof(tuple_int));
    tuple_int neighboor[8];

    add_sorted_list(openList, (void *)(&start), 0);

    while (!is_sorted_list_empty(openList)) {
        *u = *((tuple_int *)get_sorted_list(openList, 0, &current_weight));
        if (u->x == end.x && u->y == end.y) {
            return closedList;
        }

        get_valid_neighbor(map->width, map->height, *u, neighboor);
        for (i = 0; i < 8; i++) {
            v->x = neighboor[i].x;
            v->y = neighboor[i].y;

            if (map->array[v->y][v->x] != -1) {
                //not a wall
                temp_sorted = openList->head;
                while (temp_sorted->next != NULL) {
                    *temptuple = *((tuple_int *)temp_sorted->x);
                    if (temptuple->x == neighboor[i].x && temptuple->y == neighboor[i].y) {
                        if (weighted_map->cout[temptuple->y][temptuple->x] != -1 && weighted_map->cout[temptuple->y][temptuple->x] < current_weight) {
                            exist_in_open_wlc = 1;
                            break;
                        }
                    }
                    temp_sorted = temp_sorted->next;
                }

                temp = closedList->head;
                while (temp->next != NULL) {
                    *temptuple = *((tuple_int *)temp->x);
                    if (temptuple->x == neighboor[i].x && temptuple->y == neighboor[i].y) {
                        exist_in_closed = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (!(exist_in_open_wlc || exist_in_closed)) {
                    switch (map->array[neighboor[i].y][neighboor[i].x]) {
                        case SAND_CHAR:
                            weight = current_weight + 4;
                            break;

                        case END_CHAR:
                            weight = 0;
                            break;

                        case ROAD_CHAR:
                            __attribute__((fallthrough));
                        default:
                            weight = current_weight + 1;
                            break;
                    }

                    weighted_map->cout[v->y][v->x] = weight;
                    score = weighted_map->cout[v->y][v->x] + heuristique(*weighted_map, *v);
                    add_sorted_list(openList, (void *)v, score);
                }
            }

            add_list(closedList, (void *)v);
        }
    }

    free(temptuple);
    free(u);
    free(v);

    return closedList;
}

tuple_int **find_end(map_t map, int *size) {
    tuple_int **retour = malloc(sizeof(tuple_int *) * 20);
    int i, j, cpt;

    *size = 0;

    for (i = 0; i < map.height; i++) {
        for (j = 0; j < map.width; j++) {
            if (map.array[i][j] == END_CHAR) {
                cpt = (*size);
                retour[cpt] = malloc(sizeof(tuple_int));
                retour[cpt]->y = i;
                retour[cpt]->x = j;
                (*size)++;
            }
        }
    }

    return retour;
}