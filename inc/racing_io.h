#ifndef H_RACING_IO_INCLUDED
#define H_RACING_IO_INCLUDED

#include "racing_types.h"

int read_positions(struct car_t* car_list);
int post_actions(struct car_t *player_car);
void print_car(struct car_t *player_car, FILE *file);

#endif