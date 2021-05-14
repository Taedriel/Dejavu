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

float heuristique(weighted_map_t weighted_map, tuple_int current_pos) {
    return weighted_map.heuristique[current_pos.y][current_pos.x];
}

int _in (tuple_int ** liste, int size, tuple_int elem) {
    int i;

    for (i = 0; i < size; i++) {
        if (liste[i]->x == elem.x && liste[i]->y == elem.y) {
            return 1;
        }
    }

    return 0;
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

list *find_path(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int ** endpos, int size){

    int i   ;

    list * ret = create_list();
    tuple_int * current_pos;
    tuple_int * diff;

    for (i = 0; i < size; i ++) {
        if (weighted_map->came_from[endpos[i]->y][endpos[i]->x] != -1) {
            current_pos = copy_tuple_int(*(endpos[i]));
            break;
        }
    }
    if (current_pos == NULL){
        //no path found
        return ret;
    }

    while (!(current_pos->x == start.x && current_pos->y == start.y)) {

        add_list(ret, copy_tuple_int(*current_pos));
        fprintf(stderr, "%d %d\n", current_pos->x, current_pos->y);
        fprintf(stderr, "%x\n", weighted_map->came_from[current_pos->y][current_pos->x]);

        diff = int_to_tuple(weighted_map->came_from[current_pos->y][current_pos->x]);
        current_pos->x += diff->x;
        current_pos->y += diff->y;

    }
    add_list(ret, copy_tuple_int(*current_pos));

    return ret;
}

/**
 * @brief return a list of coord that are the end of the track
 * 
 * @param map 
 * @param size 
 * @return tuple_int** 
 */
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