#include "racing_driver.h"

int gas_consumption(struct car_t *player_car, int inSand)
{
    int gas = player_car->acc_x * player_car->acc_x + player_car->acc_y * player_car->acc_y;
    gas += (int)(sqrt(player_car->spe_x * player_car->spe_x + player_car->spe_y * player_car->spe_y) * 3.0 / 2.0);
    if (inSand)
    {
        gas += 1;
    }
    return -gas;
}

void consum_gas(struct car_t *player_car, int inSand)
{
    player_car->gas_level += gas_consumption(player_car, inSand);
}