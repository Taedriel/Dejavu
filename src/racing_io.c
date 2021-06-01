#include "racing_io.h"

int post_actions(car_t *player_car) {
    char action[ACTION_LENGTH];

    sprintf(action, "%d %d", player_car->acc->x, player_car->acc->y);
    fprintf(stdout, "%s", action);
    fflush(stdout);

    // RACE_BRIEF(action, player_car->gas_level, stderr)

    return EXIT_SUCCESS;
}

int read_positions(struct car_t *car_list) {
    char line_buffer[MAX_LINE_LENGTH];

    fgets(line_buffer, MAX_LINE_LENGTH, stdin);

    sscanf(line_buffer, "%d %d %d %d %d %d",
           &(car_list[0].pos->x), &(car_list[0].pos->y),
           &(car_list[1].pos->x), &(car_list[1].pos->y),
           &(car_list[2].pos->x), &(car_list[2].pos->y));

    return EXIT_SUCCESS;
}

void print_car(struct car_t *player_car, FILE *file) {
    fprintf(file, "Acc: %d %d\tSpeed: %d %d\tPos: %d %d", player_car->acc->x,
            player_car->acc->y, player_car->spe->x, player_car->spe->y,
            player_car->pos->x, player_car->pos->y);
    fprintf(file, "\tGas: %d\tBoost: %d\n", player_car->gas_level,
            player_car->boosts);
    fflush(file);
}