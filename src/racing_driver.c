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

int asservire_x(struct car_t car, int pos_x) {
    if (car.spe->x + car.pos->x > pos_x) {
        //accel negative sur x
        return -1;
    }
    //accel positive sur x
    if (abs(pos_x - (car.spe->x + car.pos->x)) > 1) {
        return 1;
    }
    return 0;
}

int asservire_y(struct car_t car, int pos_y) {
    if (car.spe->y + car.pos->y > pos_y) {
        //accel negative sur x
        return -1;
    }
    //accel positive sur x
    if (abs(pos_y - (car.spe->y + car.pos->y)) > 1) {
        return 1;
    }
    return 0;
}

tuple_int get_acc_to_reach_v2(struct car_t car, struct map_t map, tuple_int cible) {

    tuple_int acc, new_pos;
    int dx, dy, new_speed_norm;

    dx = asservire_x(car, cible.x);
    dy = asservire_y(car, cible.y);

    
    new_pos.x = car.pos->x + (car.spe->x + dx);
    new_pos.y = car.pos->y + (car.spe->y + dy);

    if (map.array[new_pos.y][new_pos.x] == WALL_CHAR){
        dx = 0;
        dy = 0;
    }
    if (map.array[car.pos->y][new_pos.x] == WALL_CHAR){
        dy = 0;
    }
    if (map.array[new_pos.y][car.pos->x] == WALL_CHAR){
        dx = 0;
    }

    acc.x = dx;
    acc.y = dy;
    //si norme supérieur à 5
    new_speed_norm = sqrt((acc.x + car.spe->x) * (acc.x + car.spe->x) + (acc.y + car.spe->y) * (acc.y + car.spe->y));
    if (new_speed_norm > 5) {
        acc.x = 0;
        acc.y = 0;
    }

    return acc;
}

tuple_int get_acc_to_reach(struct car_t *car, tuple_int B) {
    tuple_int acc;
    double new_speed_norm;

    acc.x = 2 * (B.x - car->pos->x - car->spe->x) - car->acc->x;
    acc.y = 2 * (B.y - car->pos->y - car->spe->y) - car->acc->y;
    acc.x = (acc.x == 0) ? 0 : acc.x / abs(acc.x);
    acc.y = (acc.y == 0) ? 0 : acc.y / abs(acc.y);
    new_speed_norm = sqrt((acc.x + car->spe->x) * (acc.x + car->spe->x) + (acc.y + car->spe->y) * (acc.y + car->spe->y));
    if (new_speed_norm > 5) {
        acc.x = 0;
        acc.y = 0;
    }
    return acc;
}

void set_acceleration_on_tuple(struct car_t *player_car, tuple_int acc) {
    set_acceleration(player_car, acc.x, acc.y);
}