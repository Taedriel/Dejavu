#include "racing_io.h"

int post_actions(struct car_t *player_car)
{
    char action[ACTION_LENGTH];

    sprintf(action, "%d %d", player_car->acc_x, player_car->acc_y);
    fprintf(stdout, "%s", action);
    fflush(stdout);

    RACE_BRIEF(action, player_car->gas_level, stderr)

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

void print_car(struct car_t *player_car, FILE *file)
{
    fprintf(file, "%d\n", player_car->acc_x);
    fprintf(file, "%d\n", player_car->acc_y);
    fprintf(file, "%d\n", player_car->boosts);
    fprintf(file, "%d\n", player_car->gas_level);
    fprintf(file, "%d\n", player_car->pos_x);
    fprintf(file, "%d\n", player_car->pos_y);
    fprintf(file, "%d\n", player_car->spe_x);
    fprintf(file, "%d\n", player_car->spe_y);
    fflush(stderr);
}