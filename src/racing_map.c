#include "racing_map.h"
#include "file.h"
#include "utils.h"

#include <assert.h>

/**
 * @brief init the map struct given the first input of a race
 *        ! Must be used ! => else buffer pb  
 * 
 * @param map 
 * @param height 
 * @param width 
 */
void init_map(map_t *map, int height, int width) {
    int row;

    map->height = height;
    map->width = width;
    map->array = malloc(height * sizeof(char *));

    /* Read map data, line per line */
    for (row = 0; row < height; row++) {
        map->array[row] = malloc(sizeof(char) * MAX_LINE_LENGTH);
        fgets(map->array[row], MAX_LINE_LENGTH, stdin);
        fputs(map->array[row], stderr);
    }
}

/**
 * @brief print the map
 * 
 * @param map 
 * @param file 
 */
void print_map(map_t *map, FILE *file) {
    int row;

    fprintf(file, "=== >Map< ===\n");
    fprintf(file, "Size %d x %d\n", map->width, map->height);
    for (row = 0; row < map->height; ++row) {
        fputs(map->array[row], file);
    }
}
/**
 * @brief print the map but with a path
 * 
 * @param map 
 * @param file 
 */
void print_map_path(map_t *map, tuple_int ** path, int path_size, FILE *file) {
    int row, col, p = 0, printed;

    for (row = 0; row < map->height; row++) {
        for (col = 0; col < map->width; col++) {
            printed = 0;
            for (p = 0; p < path_size; p++){
                if (path[p]->x == col && path[p]->y == row) {
                    fprintf(file, "o");
                    printed = 1;
                }
            }
            if (!printed) {
                fprintf(file, "%c", map->array[row][col]);
            }
        }
        fprintf(file, "\n");
    }
}

void print_weighted_map(int ** map, int width, int height, FILE * file) {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fprintf(file, "%d ", map[i][j]);
        }
        fprintf(file, "\n");
    }
}

/**
 * @brief return the 4 (or less) neighnoor that are crossable of a case of the map
 * 
 * @param map 
 * @param startpos 
 */
void get_valid_neighnoor(int width, int height, tuple_int startpos, tuple_int *neighboor) {

    if ((startpos.x + 1) < width) {
        if (startpos.y >= 0 && startpos.y < height) {
            neighboor[0].x = startpos.x+1;
            neighboor[0].y = startpos.y;
        }
    } 
    if ((startpos.x - 1) >= 0) {
        if (startpos.y >= 0 && startpos.y < height) {
            neighboor[1].x = startpos.x-1;
            neighboor[1].y = startpos.y;
        }
    } 
    if ((startpos.y + 1) < height) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[2].x = startpos.x;
            neighboor[2].y = startpos.y+1;
        }
    } 
    if ((startpos.y - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < width) {
            neighboor[3].x = startpos.x;
            neighboor[3].y = startpos.y-1;
        }
    } 
}

int **parse_map(map_t * map, tuple_int startpos) {

    int **djikstra = malloc(sizeof(int *) * map->height);

    stack *s = create_stack();
    int i, cpt = 0;

    tuple_int * temp;
    tuple_int neighboor[4];

    for (i = 0; i < map->height; i++) {
        djikstra[i] = malloc(sizeof(int) * map->width);
        for (int j = 0; j < map->width; j++) {
            djikstra[i][j] = -1;
        }
    }

    tuple_int current_pos; 
    current_pos.x = startpos.x;
    current_pos.y = startpos.y;

    djikstra[current_pos.y][current_pos.x] = 0;
    get_valid_neighnoor(map->width, map->height, current_pos, neighboor);
    for (i = 0; i < 4; i++) {
        if (map->array[neighboor[i].y][neighboor[i].x] != '.') {
            djikstra[neighboor[i].y][neighboor[i].x] = 1;
            temp = malloc(sizeof(tuple_int));
            memcpy(temp, &(neighboor[i]), sizeof(tuple_int));
            push(s, (void *) temp);
        }
    }

    while (!is_stack_empty(s)) {
        current_pos = *((tuple_int *)(pop(s)));
        cpt = djikstra[current_pos.y][current_pos.x];

        get_valid_neighnoor(map->width, map->height, current_pos, neighboor);
        for (i = 0; i < 4; i++) {
            if (map->array[neighboor[i].y][neighboor[i].x] != WALL_CHAR) {
                if (djikstra[neighboor[i].y][neighboor[i].x] > cpt + 1 || djikstra[neighboor[i].y][neighboor[i].x] == -1) {
                    djikstra[neighboor[i].y][neighboor[i].x] = cpt + 1;
                    temp = malloc(sizeof(tuple_int));
                    memcpy(temp, &(neighboor[i]), sizeof(tuple_int));
                    push(s, (void *)temp);
                }
            }
        }
    }

    destroy_stack(s);
    return djikstra;
}

tuple_int ** find_path(int ** weighted_map, map_t * map, int * path_size, tuple_int start, tuple_int end) {
    
    int i, min;
    int hasFinished = 0;
    tuple_int ** retour;
    stack * path = create_stack();
    
    tuple_int mint;
    tuple_int neighboor[4];
    tuple_int current_pos;

    push(path, (void *) (&end));
    while (!is_stack_empty(path)) {

        current_pos = *((tuple_int *)(pop(path)));
        min = -1;

        get_valid_neighnoor(map->width, map->height, current_pos, neighboor);
        for (i = 0; i < 4; i++) {
            if (weighted_map[neighboor[i].y][neighboor[i].x] == 0){
                memcpy(&mint, &(neighboor[i]), sizeof(tuple_int));
                hasFinished = 1;
                break;
            }
            else if (weighted_map[neighboor[i].y][neighboor[i].x] != -1) {
                if (min == -1 || min > weighted_map[neighboor[i].y][neighboor[i].x]){
                    min = weighted_map[neighboor[i].y][neighboor[i].x];
                    memcpy(&mint, &(neighboor[i]), sizeof(tuple_int));
                }     
            }
        }
        
        push(path, (void *) (&mint));
        if (hasFinished) {
            break;
        }
    }       

    fprintf(stderr, "SIZE file: %d\n", path->size);
    retour = malloc(sizeof(tuple_int *) * path->size);
    *path_size = path->size;
    for (int i = path->size-1; i >= 0; i--) {
        retour[i] = malloc(sizeof(tuple_int));
        memcpy(retour[i], pop(path), sizeof(tuple_int));
    }

    destroy_stack(path);
    return retour;
}

tuple_int ** find_end(map_t map, int * size) {

    tuple_int ** retour = malloc(sizeof(tuple_int *) * 20);
    int i, j, cpt;

    *size = 0;

    for (i = 0; i < map.height; i++) {
        for (j = 0; j < map.width; j++) {
            if (map.array[i][j] == END_CHAR){
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