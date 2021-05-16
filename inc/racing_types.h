#ifndef H_RACING_TYPES_INCLUDED
#define H_RACING_TYPES_INCLUDED

/* =================== Include ===================*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "file.h"
#include "pile.h"
#include "list.h"
#include "sorted_list.h"


/* =================== Constant ===================*/

#define MAX_LINE_LENGTH             1024
#define BOOSTS_AT_START             5
#define ACTION_LENGTH               100
#define MAX_PATH_SIZE               1024
#define DELTA_SPEED                 0.5

#define DIAG_WEIGHT                 1
#define OWN_SPEED_WEIGHT            1
#define CONCUR_SPEED_WEIGHT         1
#define POURCENT_LOSS_BY_ACC_WEIGHT 1./5.

#define END_CHAR                    '='
#define WALL_CHAR                   '.'
#define SAND_CHAR                   '~'
#define ROAD_CHAR                   '#'

#define ERROR_ACC_ALL               -1
#define ERROR_ACC_NO                0
#define ERROR_ACC_Y                 1
#define ERROR_ACC_X                 2

/* =================== Macro ===================*/

#define RACE_START(file)                fflush(file);\
                                        fprintf(file, "\n=== Race start ===\n");

#define RACE_ROUND(round, file)         fprintf(file, "=== ROUND %d\n", round);\
                                        fflush(file);

#define RACE_BRIEF(action, gas, file)   fprintf(file, "Action: %s   Gas remaining: %d\n", action, gas);\
                                        fflush(file);

#define RACE_END(file)                  fprintf(file, "Good Bye!\n");\
                                        fflush(file);

/* =================== Struct ===================*/

typedef struct tuple_int
{

    int x;
    int y;

} tuple_int;

typedef struct car_t
{
    int gas_level;
    int boosts;
    tuple_int * acc;
    tuple_int * spe;
    tuple_int * pos;
} car_t;

typedef struct map_t
{
    int width;
    int height;
    char **array;
} map_t;

typedef struct weighted_map_t
{
    int ** came_from;
    float ** dist_from_end;
    float ** heuristique;
    float ** cout;

} weighted_map_t;

#endif