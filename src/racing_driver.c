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
void init_car(struct car_t *player_car, int boosts, int acc_x,
              int acc_y, int spe_x, int spe_y, int gas) {
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
int gas_consumption(struct car_t *player_car, int inSand) {
    int gas = player_car->acc->x * player_car->acc->x + player_car->acc->y * player_car->acc->y;
    gas += (int)(sqrt(player_car->spe->x * player_car->spe->x + player_car->spe->y * player_car->spe->y) * 3.0 / 2.0);
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
void consum_gas(struct car_t *player_car, int inSand) {
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
void set_acceleration(struct car_t *player_car, int acc_x, int acc_y) {
    player_car->acc->x = acc_x;
    player_car->acc->y = acc_y;
}

tuple_int get_acc_to_reach(struct car_t *car, tuple_int B)
{
    tuple_int acc;

    int t = 1;

    acc.x = 2*(B.x-car->pos->x-car->spe->x*t)/(t*t) - car->acc->x;
    acc.y = 2*(B.y-car->pos->y-car->spe->y*t)/(t*t) - car->acc->y;

    return acc;
}