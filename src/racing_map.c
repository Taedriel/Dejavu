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
void print_map_path(map_t *map, tuple_int * path, FILE *file) {
    int row, col, p = 0;

    fprintf(file, "=== >Map< ===\n");
    fprintf(file, "Size %d x %d\n", map->width, map->height);
    for (row = 0; row < map->height; row++) {
        for (col = 0; col < map->width; col++) {
            if (path[p].x == col && path[p].y == row) {
                fputc('o', file);
                p++;
            }else {
                fputc(map->array[row][col], file);
            }
        }
    }
}

void print_weighted_map(int ** map, int width, int height, FILE * file) {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fprintf(file, "(%d) ", map[i][j]);
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
void get_valid_neighnoor(map_t map, tuple_int startpos, tuple_int *neighboor) {

    for (int i = 0; i < 4 ; i++) {
        neighboor[i].x = -1;
        neighboor[i].y = -1;
    }

    if ((startpos.x + 1) < map.width) {
        if (startpos.y >= 0 && startpos.y < map.height) {
            if (map.array[startpos.y][startpos.x+1] != '.'){
                neighboor[0].x = startpos.x+1;
                neighboor[0].y = startpos.y;
            }
        }
    } 
    if ((startpos.x - 1) >= 0) {
        if (startpos.y >= 0 && startpos.y < map.height) {
            if (map.array[startpos.y][startpos.x-1] != '.'){
                neighboor[1].x = startpos.x-1;
                neighboor[1].y = startpos.y;
            }
        }
    } 
    if ((startpos.y + 1) < map.height) {
        if (startpos.x >= 0 && startpos.x < map.width) {
            if (map.array[startpos.y+1][startpos.x] != '.'){
                neighboor[2].x = startpos.x;
                neighboor[2].y = startpos.y+1;
            }
        }
    } 
    if ((startpos.y - 1) >= 0) {
        if (startpos.x >= 0 && startpos.x < map.width) {
            if (map.array[startpos.y-1][startpos.x] != '.'){
                neighboor[3].x = startpos.x;
                neighboor[3].y = startpos.y-1;
            }
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
    get_valid_neighnoor(*map, current_pos, neighboor);
    for (i = 0; i < 4; i++) {
        if (neighboor[i].x != -1) {
            djikstra[neighboor[i].y][neighboor[i].x] = 1;
            temp = malloc(sizeof(tuple_int));
            memcpy(temp, &(neighboor[i]), sizeof(tuple_int));
            push(s, (void *) temp);
        }
    }

    while (!is_stack_empty(s)) {
        fprintf(stderr, "Empty %d\n", is_stack_empty(s));
        print_stack(*s, &print_tuple, stderr);
        current_pos = *((tuple_int *)(pop(s)));
        cpt = djikstra[current_pos.y][current_pos.x];
        fprintf(stderr, "cpt: %d\n", cpt);

        get_valid_neighnoor(*map, current_pos, neighboor);
        for (i = 0; i < 4; i++) {
            if (neighboor[i].x != -1) {
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