#include <assert.h>

#include "racing_types.h"
#include "racing_map.h"

/**
 * @brief return the 4 (or less) neighnoor that are crossable of a case of the map
 * 
 * @param map 
 * @param startpos 
 */
void get_valid_neighnoor(int width, int height, tuple_int startpos, tuple_int *neighboor) {
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
queue * find_path(weighted_map_t weighted_map, map_t *map, int *path_size, tuple_int start, tuple_int end) {
    int i, min, cpt = 0;

    sorted_list * openList = create_sorted_list();
    queue * closedList = create_queue();
    
    tuple_int *current_pos = copy_tuple_int(end);
    tuple_int neighboor[8];

    add_sorted_list(openList, (void *) (&start), 0);

    while (!is_sorted_list_empty(openList)) {

        *current_pos = *((tuple_int *) get_sorted_list(openList, 0));
        if (current_pos->x == end.x && current_pos->y == end.y){
            return closedList;
        }

        get_valid_neighnoor(map->width, map->height, *current_pos, neighboor);
        for (i = 0; i < 8; i++) {
            if (weighted_map[neighboor[i].y][neighboor[i].x] != -1) {
                //not a wall
                if (min == -1 || min > weighted_map[neighboor[i].y][neighboor[i].x]) {
                    min = weighted_map[neighboor[i].y][neighboor[i].x];
                    memcpy(retour[cpt - 1], copy_tuple_int(neighboor[i]), sizeof(tuple_int));
                    memcpy(current_pos, &(neighboor[i]), sizeof(tuple_int));
                }
            }
        }
    }

    free(current_pos);
    *path_size = cpt;
    retour = realloc(retour, sizeof(tuple_int) * cpt);
    return retour;
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