#ifndef H_TUPLE_INCLUDED
#define H_TUPLE_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct tuple_int {
    int x;
    int y;
} tuple_int;

/**
 * @brief Create a tuple of int (a, b) 
 * 
 * @param a 
 * @param b 
 * @return tuple_int* 
 */
tuple_int *create_tuple_int(int a, int b);

/**
 * @brief Create a 0 0 tuple, i.e. (0, 0)
 * 
 * @return tuple_int 
 */
tuple_int create_0_0_tuple();

/**
 * @brief Return a copy of a tuple
 * 
 * @param o 
 * @return tuple_int* 
 */
tuple_int *copy_tuple_int(tuple_int o);

/**
 * @brief Print a tuple
 * 
 * @param t 
 * @param rep 
 */
void print_tuple(void *t, char *rep);

/**
 * @brief Search if a tuple element is in a list of tuple
 * 
 * @param liste 
 * @param size 
 * @param elem 
 * @return int 
 */
int _in(tuple_int **liste, int size, tuple_int elem);

/**
 * @brief Convert an int into a tuple
 * 
 * @param entier 
 * @return tuple_int* 
 */
tuple_int *int_to_tuple(int entier);

/**
 * @brief Convert a tuple into an int
 * 
 * @param origine 
 * @param dest 
 * @return int 
 */
int tuple_to_int(tuple_int origine, tuple_int dest);

/**
 * @brief transform a normed tupled into the same format than relative_pos
 * 
 * @param a 
 * @return int 
 */
int tuple_normed_to_int(tuple_int a);

#endif