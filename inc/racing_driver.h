#ifndef H_RACING_DRIVER_INCLUDED
#define H_RACING_DRIVER_INCLUDED

#include "racing_types.h"

void init_car(struct car_t *player_car, int boosts, int acc_x,
              int acc_y, int spe_x, int spe_y, int gas);

int gas_consumption(struct car_t *player_car, int inSand);

void consum_gas(struct car_t *player_car, int inSand);

void set_acceleration(struct car_t *player_car, int acc_x, int acc_y);

tuple_int get_acc_to_reach(struct car_t *car, struct map_t map, tuple_int B);

void set_acceleration_on_tuple(struct car_t *player_car, tuple_int acc);

tuple_int get_acc_to_reach_v2(struct car_t car, struct map_t map, tuple_int cible);

int asservire_y(struct car_t car, int pos_y);

int asservire_x(struct car_t car, int pos_x);

int is_valid_acceleration(struct car_t *car, tuple_int acc, struct map_t map);

#endif