#include "racing_io.h"


int post_actions(struct car_t *player_car)
{
    char action[ACTION_LENGTH];

    memset(action, '\0', ACTION_LENGTH*sizeof(char));
    sprintf(action, "%d %d", player_car->acc_x, player_car->acc_y);
    fprintf(stdout, "%s", action);
    fflush(stdout);

}