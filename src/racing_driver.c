#include "racing_driver.h"
#include "racing_io.h"
#include "racing_checkpoints.h"

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

void consum_gas(struct car_t* player_car, int inSand) {
    player_car->gas_level -= gas_consumption(player_car, inSand);
    player_car->spe->x = (inSand) ? player_car->spe->x > 0 : player_car->spe->x + player_car->acc->x;
    player_car->spe->y = (inSand) ? player_car->spe->y > 0 : player_car->spe->y + player_car->acc->y;
}

void set_acceleration(struct car_t* player_car, int acc_x, int acc_y) {
    player_car->acc->x = acc_x;
    player_car->acc->y = acc_y;
}

void set_acceleration_on_tuple(struct car_t* player_car, tuple_int acc) {
    set_acceleration(player_car, acc.x, acc.y);
}

tuple_int * dist_to_futur_pos(tuple_int futur_pos, car_t car) {
    tuple_int * ret = create_tuple_int(0,0);
    ret->x = futur_pos.x - (car.pos->x + car.spe->x);
    ret->y = futur_pos.y - (car.pos->y + car.spe->y);
    return ret;
}
/**
 * @todo ici on doit recup le segment en question 
 * puis on calcule la distance. Enfin, un if 
 * arbitraire avec une valeur choisi de longeur limite
 * avant le boost. 
 */
int normed_acc(int acc_require, int boost_allowed) {
    if (acc_require < 0 && !boost_allowed)
        return -1;
    if (acc_require > 0 && !boost_allowed)
        return 1;
    if (acc_require > 1 && boost_allowed)
        return 2;
    if (acc_require < -1 && boost_allowed)
        return -2;
    return 0;
}

tuple_int get_acc_to_reach(struct car_t* car, struct map_t map, tuple_int to_reach, int boost_allowed) {
    tuple_int acc;
    tuple_int * deltaToReach;
    //double new_speed_norm;
    deltaToReach = dist_to_futur_pos(to_reach, *car);
    acc.x = normed_acc(deltaToReach->x, boost_allowed);
    acc.y = normed_acc(deltaToReach->y, boost_allowed); 
    fprintf(stderr, "To Reach: %d %d\nDelta: \t%d %d\nAcc: \t%d %d\n", to_reach.x, to_reach.y, deltaToReach->x, deltaToReach->y, acc.x, acc.y);

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