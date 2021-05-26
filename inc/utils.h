#ifndef H_UTILS_INCLUDED
#define H_UTILS_INCLUDED

#include "racing_types.h"

/**
 * @brief Find the max
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int max(int a, int b);

/**
 * @brief Find the min
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int min(int a, int b);

/**
 * @brief Compute the dot product of two segments represent by three points
 * 
 * @param a 
 * @param b 
 * @param c 
 * @return int 
 */
int dot_product(tuple_int *a, tuple_int *b, tuple_int *c);

/**
 * @brief Return a*a
 * 
 * @param a 
 * @return int 
 */
int pow_int_2(int a);

/**
 * @brief Compute the distance between two points
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double distance(tuple_int a, tuple_int b);

/**
 * @brief Check if the car is in sand
 * 
 * @param map 
 * @param car 
 * @return int 
 */
int is_in_sand(map_t map, car_t car);

/**
 * @brief Compute the hamming weight
 * 
 * @param x 
 * @return int 
 */
int hamming_weight(int x);

/**
 * @brief Check if the two points aren't paralleles to an axis
 * 
 * @param start 
 * @param dest 
 * @return int 
 */
int is_in_diagonal_from(tuple_int start, tuple_int dest);

#endif