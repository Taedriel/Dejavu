#ifndef H_RACING_DRIVER_INCLUDED
#define H_RACING_DRIVER_INCLUDED

#include "racing_types.h"

/**
 * @brief initialize a car with all the given value
 *
 * @param player_car
 * @param boosts
 * @param acc_x
 * @param acc_y
 * @param spe_x
 * @param spe_y
 * @param gas
 */
void init_car(struct car_t *player_car, int boosts, int acc_x, int acc_y, int spe_x, int spe_y, int gas);

/**
 * @brief return the amount of gas used by the car
 *
 * @param player_car
 * @param inSand whether the car is in sand or not (1 for yes or 0 for no)
 * @return int the amount of gas used
 */
int gas_consumption(struct car_t *player_car, int inSand);

/**
 * @brief update the pos of the car and the gas level
 *
 * @param player_car
 * @param inSand
 */
void consum_gas(struct car_t *player_car, int inSand);

tuple_int estimation_gas(map_t *map, tuple_int begin, tuple_int end, car_t *car);

    /**
 * @brief Set the acceleration of a car
 *
 * @param player_car
 * @param acc_x
 * @param acc_y
 */
    void set_acceleration(struct car_t *player_car, int acc_x, int acc_y);

/**
 * @brief Set the acceleration on tuple object
 * 
 * @param player_car 
 * @param acc 
 */
void set_acceleration_on_tuple(struct car_t *player_car, tuple_int acc);

/**
 * @brief Return the theorical position
 * 
 * @param new_coord 
 * @param prev_coord 
 * @param prev_spe 
 * @return int 
 */
tuple_int * dist_to_futur_pos(tuple_int futur_pos, car_t car);

/**
 * @brief Return the logical acceleration
 * 
 * @param coord 
 * @return int 
 */
int normed_acc(int acc_require, int boost_allowed);

/**
 * @brief Get the acceleration to reach point
 * 
 * @param car your car 
 * @param map the map
 * @param B The point you want to reach
 * @return tuple_int 
 */
tuple_int get_acc_to_reach(struct car_t * car, struct map_t map, tuple_int to_reach, int boost_allowed);

/**
 * @brief Return which composant of the acceleration is valid 
 * 
 * @param car 
 * @param acc 
 * @param map 
 * @return int 
 */
int is_valid_acceleration(struct car_t * car, tuple_int acc, struct map_t map);

/**
 * @brief return whether the move of car0 is a valide move, i.e. it does not goes through wall or opposent
 * 
 */
int is_move_valid(map_t map, car_t cars[3], tuple_int dir);

/**
 * @brief return the normed speed of a car
 * 
 * @param car 
 * @return double 
 */
double get_normed_speed(car_t car);

/**
 * @brief return the number of cars at distance d of the car n°0 
 * 
 * @param map 
 * @param cars 
 * @param distance 
 * @return int 
 */
int nb_cars_around(map_t map, car_t cars[3], int distance);

/**
 * @brief return the number of sand case at distance d of the car n°0
 * 
 * @param map 
 * @param cars 
 * @param distance 
 * @return int 
 */
int nb_sand_around(map_t map, car_t cars[3], int distance);

#endif