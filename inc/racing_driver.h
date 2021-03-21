#ifndef H_RACING_DRIVER_INCLUDED
#define H_RACING_DRIVER_INCLUDED

#include "racing_types.h"

int gas_consumption(struct car_t *player_car, int inSand);
void consum_gas(struct car_t *player_car, int inSand);

#endif