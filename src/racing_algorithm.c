#include <assert.h>

#include "racing_map.h"
#include "racing_types.h"
#include "utils.h"

list * get_valid_neighbor(int width, int height, tuple_int startpos) {
    list * ret = create_list();
    
    if ((startpos.x + 1) < width) {
        if (startpos.y >= 0 && startpos.y < height) {
            add_list(ret, create_tuple_int(startpos.x +1, startpos.y));
        }
    }
    if ((startpos.x - 1) >= 0) {
        if (startpos.y >= 0 && startpos.y < height) {
            add_list(ret, create_tuple_int(startpos.x -1, startpos.y));
        }
    }
    if ((startpos.y + 1) < height) {
        if (startpos.x >= 0 && startpos.x < width) {
            add_list(ret, create_tuple_int(startpos.x, startpos.y + 1));
        }
    }
    if ((startpos.y - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < width) {
            add_list(ret, create_tuple_int(startpos.x, startpos.y - 1));
        }
    }
    if ((startpos.y - 1) >= 0 && (startpos.x - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < width) {
            add_list(ret, create_tuple_int(startpos.x - 1, startpos.y - 1));
        }
    }
    if ((startpos.y - 1) >= 0 && (startpos.x + 1) < width) {
        if (startpos.x >= 0 && startpos.x < width) {
            add_list(ret, create_tuple_int(startpos.x + 1, startpos.y - 1));
        }
    }
    if ((startpos.y + 1) < height && (startpos.x + 1) < width) {
        if (startpos.x >= 0 && startpos.x < width) {
            add_list(ret, create_tuple_int(startpos.x + 1, startpos.y + 1));
        }
    }
    if ((startpos.y + 1) < height && (startpos.x - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < width) {
            add_list(ret, create_tuple_int(startpos.x - 1, startpos.y + 1));
        }
    }

    return ret;
}

float heuristique(weighted_map_t weighted_map, tuple_int current_pos, float *** liste_accel_map, float cout) {


    float heur = cout + (weighted_map.dist_from_end[current_pos.y][current_pos.x] * DIST_FROM_END_WEIGHT);

    if (liste_accel_map != NULL) {
        // fprintf(stderr, "- %1.2f ", (heur * OWN_SPEED_WEIGHT * liste_accel_map[0][current_pos.y][current_pos.x]));
        heur -= heur * OWN_SPEED_WEIGHT * liste_accel_map[0][current_pos.y][current_pos.x];
        // fprintf(stderr, "+ %1.2f ", (heur * CONCUR_SPEED_WEIGHT * liste_accel_map[1][current_pos.y][current_pos.x]));
        heur += heur * CONCUR_SPEED_WEIGHT * liste_accel_map[1][current_pos.y][current_pos.x];
        // fprintf(stderr, "+ %1.2f ", (heur * CONCUR_SPEED_WEIGHT * liste_accel_map[2][current_pos.y][current_pos.x]));
        heur += heur * CONCUR_SPEED_WEIGHT * liste_accel_map[2][current_pos.y][current_pos.x];
    }

    // fprintf(stderr, "Ajout de (%d %d) de poid: %f (%f + %f * ratio)\n", current_pos.x, current_pos.y, heur,cout);

    return heur;
}


tuple_int * int_to_tuple(int entier) {

    tuple_int * ret = create_tuple_int(0, 0);
    int diff;
    ret->x = (entier >> 4) == 2 ? -1 : (entier >> 4);
    diff = entier - ((int) (entier >> 4) << 4);
    ret->y = diff == 2 ? -1 : diff;

    return ret;
}

int tuple_to_int(tuple_int origine, tuple_int dest) {
    int deltaX = origine.x - dest.x;
    int deltaY = origine.y - dest.y;
    return ((deltaX < 0 ? 2 : deltaX == 0 ? 0
                                          : 1)
            << 4) |
           (deltaY < 0 ? 2 : deltaY == 0 ? 0
                                         : 1);
}

int hamming_weight(int x) {
    int ret = 0;
    while (x > 0) {
        ret += x & 1;
        x = x >> 1;
    }
    return ret;
}

/**
 * @brief transform a normed tupled into the same format than relative_pos
 * 
 * @param a 
 * @return int 
 */
int tuple_normed_to_int(tuple_int a) {
    return ((a.x < 0 ? 2 : a.x == 0 ? 0
                                    : 1)
                << 4 |
            (a.y < 0 ? 2 : a.y == 0 ? 0
                                    : 1));
}

int is_in_diagonal_from(tuple_int start, tuple_int dest) {
    return abs(start.x - dest.x) > 0 && abs(start.y - dest.y) > 0; 
}

list *find_path(weighted_map_t *weighted_map, map_t *map, tuple_int start, list * endpos){

    int x, y, i, min = -1;

    list * ret = create_list();
    tuple_int * current_pos;
    tuple_int * diff;

    fprintf(stderr, "GOAL is (%d %d)\n", start.x, start.y);

    for (i = 0; i < endpos->size; i ++) {
        x = ((tuple_int *)get_list(endpos, i))->x;
        y = ((tuple_int *)get_list(endpos, i))->y;
        if (weighted_map->came_from[y][x] != -1) {
            if (min == -1 || weighted_map->heuristique[y][x] < min){
                // fprintf(stderr, "find min heur value for %d %d: %f\n", x, y, weighted_map->heuristique[y][x]);
                min = weighted_map->heuristique[y][x];
                current_pos = copy_tuple_int(*((tuple_int *)get_list(endpos, i)));
            }
        }
    }
    if (current_pos == NULL){
        //no path found
        return ret;
    }

    while (!(current_pos->x == start.x && current_pos->y == start.y)) {

        add_list(ret, copy_tuple_int(*current_pos));
        // fprintf(stderr, "%d %d\n", current_pos->x, current_pos->y);
        // fprintf(stderr, "%x\n", weighted_map->came_from[current_pos->y][current_pos->x]);

        diff = int_to_tuple(weighted_map->came_from[current_pos->y][current_pos->x]);
        current_pos->x += diff->x;
        current_pos->y += diff->y;

    }
    add_list(ret, copy_tuple_int(*current_pos));

    return ret;
}

list *find_end(map_t map) {
    list * ret = create_list();
    tuple_int * temp;
    int i, j;

    for (i = 0; i < map.height; i++) {
        for (j = 0; j < map.width; j++) {
            if (map.array[i][j] == END_CHAR) {
                temp = malloc(sizeof(tuple_int));
                temp->y = i;
                temp->x = j;
                add_list(ret, temp);
            }
        }
    }

    return ret;
}