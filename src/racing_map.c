#include "racing_map.h"

/**
 * @brief init the map struct given the first input of a race
 * 
 * @param map 
 * @param height 
 * @param width 
 */
void init_map(struct map_t *map, int height, int width) {
    int row;

    map->height = height;
    map->width = width;
    map->array = malloc(height * sizeof(void *));

    /* Read map data, line per line */
    for (row = 0; row < height; ++row) { 
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
void print_map(struct map_t *map, FILE *file) {
    int row;

    fprintf(file, "=== >Map< ===\n");
    fprintf(file, "Size %d x %d\n", map->width, map->height);
    for (row = 0; row < map->height; ++row) {
        fputs(map->array[row], file);
    }
}