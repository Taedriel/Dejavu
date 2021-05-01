#include "racing_driver.h"

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
    player_car->spe->x += player_car->acc->x;
    player_car->spe->y += player_car->acc->y;
}

void set_acceleration(struct car_t* player_car, int acc_x, int acc_y) {
    player_car->acc->x = acc_x;
    player_car->acc->y = acc_y;
}

void set_acceleration_on_tuple(struct car_t* player_car, tuple_int acc) {
    set_acceleration(player_car, acc.x, acc.y);
}

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