#ifndef H_RACING_TYPES_INCLUDED
#define H_RACING_TYPES_INCLUDED

/* =================== Include ===================*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =================== Constant ===================*/

#define MAX_LINE_LENGTH             1024
#define BOOSTS_AT_START             5
#define ACTION_LENGTH               100

#define END_CHAR                    '='
#define WALL_CHAR                   '.'
#define SAND_CHAR                   '~'
#define ROAD_CHAR                   '#'

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



#endif