#ifndef H_RACING_TYPES_INCLUDED
#define H_RACING_TYPES_INCLUDED

/* =================== Include ===================*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "file.h"
#include "pile.h"
#include "list.h"
#include "sorted_list.h"

/* =================== Constant ===================*/

#define MAX_LINE_LENGTH             1024
#define BOOSTS_AT_START             5
#define ACTION_LENGTH               100
#define MAX_PATH_SIZE               1024

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
    float ** heuristique;
    float ** dist_from_end;

} weighted_map_t;

#endif