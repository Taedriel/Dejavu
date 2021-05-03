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

list *find_path(weighted_map_t *weighted_map, map_t *map, tuple_int start, tuple_int ** endpos, int size){

    int i, deltaX, deltaY;

    list * ret = create_list();
    tuple_int * current_pos;

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

        deltaX = weighted_map->came_from[current_pos->y][current_pos->x] >> 4;
        deltaY = weighted_map->came_from[current_pos->y][current_pos->x] - (deltaX << 4);
        current_pos->x += -(deltaX == 2 ? -1 : deltaX);   
        current_pos->y += -(deltaY == 2 ? -1 : deltaY);   
    }
    add_list(ret, copy_tuple_int(*current_pos));

    return ret;
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