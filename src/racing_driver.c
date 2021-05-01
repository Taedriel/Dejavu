#include "racing_driver.h"

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
void init_car(struct car_t* player_car, int boosts, int acc_x, int acc_y,
              int spe_x, int spe_y, int gas) {
    player_car->acc = malloc(sizeof(tuple_int));
    player_car->spe = malloc(sizeof(tuple_int));
    player_car->pos = malloc(sizeof(tuple_int));

    player_car->acc->x = acc_x;
    player_car->acc->y = acc_y;
    player_car->boosts = boosts;
    player_car->gas_level = gas;
    player_car->spe->x = spe_x;
    player_car->spe->y = spe_y;
    player_car->pos->x = 0;
    player_car->pos->y = 0;
}

/**
 * @brief return the amount of gas used by the car
 *
 * @param player_car
 * @param inSand whether the car is in sand or not (1 for yes or 0 for no)
 * @return int the amount of gas used
 */
int gas_consumption(struct car_t* player_car, int inSand) {
    int gas = player_car->acc->x * player_car->acc->x +
              player_car->acc->y * player_car->acc->y;
    gas += (int)(sqrt(player_car->spe->x * player_car->spe->x +
                      player_car->spe->y * player_car->spe->y) *
                 3.0 / 2.0);
    if (inSand) {
        gas += 1;
    }
    return gas;
}

/**
 * @brief update the pos of the car and the gas level
 *
 * @param player_car
 * @param inSand
 */
void consum_gas(struct car_t* player_car, int inSand) {
    player_car->gas_level -= gas_consumption(player_car, inSand);
    player_car->spe->x += player_car->acc->x;
    player_car->spe->y += player_car->acc->y;
}

/**
 * @brief Set the acceleration of a car
 *
 * @param player_car
 * @param acc_x
 * @param acc_y
 */
void set_acceleration(struct car_t* player_car, int acc_x, int acc_y) {
    player_car->acc->x = acc_x;
    player_car->acc->y = acc_y;
}

/**
 * @brief Set the acceleration on tuple object
 * 
 * @param player_car 
 * @param acc 
 */
void set_acceleration_on_tuple(struct car_t* player_car, tuple_int acc) {
    set_acceleration(player_car, acc.x, acc.y);
}

/**
 * @brief Return the theorical position
 * 
 * @param new_coord 
 * @param prev_coord 
 * @param prev_spe 
 * @return int 
 */
inline int theoric_position(int new_coord, int prev_coord, int prev_spe) {
    return new_coord - prev_coord - prev_spe; 
}

inline int normed_acc(int coord) {
    if (coord < 0)
        return -1;
    if (coord > 0)
        return 1;
    return 0;
}

/**
 * @brief Get the acceleration to reach point
 * 
 * @param car your car 
 * @param map the map
 * @param B The point you want to reach
 * @return tuple_int 
 */
tuple_int get_acc_to_reach(struct car_t* car, struct map_t map, tuple_int B) {
    tuple_int acc;
    int x;
    int y;
    //double new_speed_norm;
    x = theoric_position(B.x, car->pos->x, car->spe->x);
    y = theoric_position(B.y, car->pos->y, car->spe->y);
    acc.x = normed_acc(x);
    acc.y = normed_acc(y);

#if 0
    new_speed_norm = sqrt((acc.x + car->spe->x) * (acc.x + car->spe->x) +
                          (acc.y + car->spe->y) * (acc.y + car->spe->y));
    if (new_speed_norm > 5) {
        acc.x = 0;
        acc.y = 0;
    }
#endif
    return acc;
}


int is_valid_acceleration(struct car_t* car, tuple_int acc, struct map_t map) {
    int x = car->pos->x + car->spe->x + acc.x;
    int y = car->pos->y + car->spe->y + acc.y;

    int is_xy_valide = map.array[y][x] == ROAD_CHAR;
    int is_x_valide = map.array[car->pos->y][x] == ROAD_CHAR;
    int is_y_valide = map.array[y][car->pos->x] == ROAD_CHAR;

    if (is_xy_valide) {
        return ERROR_ACC_NO;
    }
    if (is_x_valide) {
        return ERROR_ACC_Y;
    }
    if (is_y_valide) {
        return ERROR_ACC_X;
    }
    return ERROR_ACC_ALL;
}