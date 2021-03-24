#include "racing_map.h"

void init_map(struct map_t *map, int height, int width)
{
    int row;

    map->height = height;
    map->width = width;
    map->array = malloc(height*sizeof(void*));

    for (row = 0; row < height; ++row)
    { /* Read map data, line per line */
        fgets(map->array[row], MAX_LINE_LENGTH, stdin);
        fputs(map->array[row], stderr);
    }
}