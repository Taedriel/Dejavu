#include "racing_driver.h"

void init_car(struct car_t *player_car, int boosts,int acc_x,
              int acc_y, int spe_x, int spe_y, int gas)
{
    player_car->acc_x = acc_x;
    player_car->acc_y = acc_y;
    player_car->boosts = boosts;
    player_car->gas_level = gas;
    player_car->spe_x = spe_x;
    player_car->spe_y = spe_y;
    player_car->pos_x = 0;
    player_car->pos_y = 0;
}

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
    player_car->spe_x += player_car->acc_x;
    player_car->spe_y += player_car->acc_y;
}

void set_acceleration(struct car_t *player_car, int acc_x, int acc_y)
{
    player_car->acc_x = acc_x;
    player_car->acc_y = acc_y;
}