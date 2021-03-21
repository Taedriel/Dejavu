#include "racing_io.h"

int post_actions(struct car_t *player_car)
{
    char action[ACTION_LENGTH];

    memset(action, '\0', ACTION_LENGTH * sizeof(char));
    sprintf(action, "%d %d", player_car->acc_x, player_car->acc_y);
    fprintf(stdout, "%s", action);
    fflush(stdout);

    return EXIT_SUCCESS;
}

int read_positions(struct car_t *car_list)
{
    char line_buffer[MAX_LINE_LENGTH];

    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read positions of pilots */

    sscanf(line_buffer, "%d %d %d %d %d %d",
           &(car_list[0].pos_x), &(car_list[0].pos_y),
           &(car_list[1].pos_x), &(car_list[1].pos_y),
           &(car_list[2].pos_x), &(car_list[2].pos_y));

    fprintf(stderr, "    Positions: Me(%d,%d)  A(%d,%d), B(%d,%d)\n",
            car_list[0].pos_x, car_list[0].pos_y,
            car_list[1].pos_x, car_list[1].pos_y,
            car_list[2].pos_x, car_list[2].pos_y);
    fflush(stderr);

    return EXIT_SUCCESS;
}