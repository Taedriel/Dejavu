#ifndef H_RACING_IO_INCLUDED
#define H_RACING_IO_INCLUDED

#include "racing_types.h"

/**
 * @brief send action to stdout, publishing theme to the GDC
 * 
 * @param player_car 
 * @return int 
 */
int read_positions(struct car_t* car_list);

/**
 * @brief read positions of all the pilots of the track ans store them in there 
 * respective car struc
 * 
 * @param car_list 
 * @return int 
 */
int post_actions(struct car_t *player_car);

/**
 * @brief print all the car info 
 * 
 * @param player_car 
 * @param file 
 */
void print_car(struct car_t *player_car, FILE *file);

#endif