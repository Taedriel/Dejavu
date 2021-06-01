#include "racing_map.h"

void init_map(map_t *map, int height, int width) {
    int row;

    map->height = height;
    map->width = width;
    map->array = malloc(height * sizeof(char *));

    for (row = 0; row < height; row++) {
        map->array[row] = malloc(sizeof(char) * MAX_LINE_LENGTH);
        fgets(map->array[row], MAX_LINE_LENGTH, stdin);
    }
}

void print_map(map_t *map, FILE *file) {
    int row;

    fprintf(file, "=== >Map< ===\n");
    fprintf(file, "Size %d x %d\n", map->width, map->height);
    for (row = 0; row < map->height; ++row) {
        fputs(map->array[row], file);
    }
}

void print_map_path(map_t *map, tuple_int **path, int path_size, FILE *file) {
    int row, col, p = 0, printed;

    for (row = 0; row < map->height; row++) {
        for (col = 0; col < map->width; col++) {
            printed = 0;
            for (p = 0; p < path_size; p++) {
                if (path[p]->x == col && path[p]->y == row) {
                    fprintf(file, "o");
                    printed = 1;
                    break;
                }
            }
            if (!printed) {
                fprintf(file, "%c", map->array[row][col]);
            }
        }
        fprintf(file, "\n");
    }
}

void print_float_weighted_map(float ** map, int width, int height, FILE *file) {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (map[i][j] == 0. || map[i][j] == -1.){
                fprintf(file, "     ");
            } else {
                fprintf(file, "%2.1f ", map[i][j]);
            }
        }
        fprintf(file, "\n");
    }
}

void print_int_weighted_map(int ** map, int width, int height, FILE *file) {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fprintf(file, "(%x) ", map[i][j]);
        }
        fprintf(file, "\n");
    }
}
