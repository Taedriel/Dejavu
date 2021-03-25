#ifndef H_RACING_DRIVER_INCLUDED
#define H_RACING_DRIVER_INCLUDED

#include "racing_types.h"

void init_car(struct car_t *player_car, int boosts, int acc_x,
              int acc_y, int spe_x, int spe_y, int gas);
              
int gas_consumption(struct car_t *player_car, int inSand);

void consum_gas(struct car_t *player_car, int inSand);

void set_acceleration(struct car_t *player_car, int acc_x, int acc_y);

#endif