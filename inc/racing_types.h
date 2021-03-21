#ifndef H_RACING_TYPES_INCLUDED
#define H_RACING_TYPES_INCLUDED

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH             1024
#define BOOSTS_AT_START             5
#define ACTION_LENGTH               100

#define RACE_START()                fflush(stderr);\
                                    fprintf(stderr, "\n=== Race start ===\n");

#define RACE_ROUND(round)           fprintf(stderr, "=== ROUND %d\n", round);\
                                    fflush(stderr);

struct car_t
{
    int gas_level;
    int boosts;
    int acc_x;
    int acc_y;
    int spe_x;
    int spe_y;
    int pos_x;
    int pos_y;
};

struct map_t
{
    int width;
    int height;
    int **array;
};


#endif