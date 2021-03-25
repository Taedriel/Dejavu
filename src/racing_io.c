#include "racing_io.h"

/**
 * @brief send action to stdout, publishing theme to the GDC
 * 
 * @param player_car 
 * @return int 
 */
int post_actions(struct car_t *player_car) {
    char action[ACTION_LENGTH];

    sprintf(action, "%d %d", player_car->acc_x, player_car->acc_y);
    fprintf(stdout, "%s", action);
    fflush(stdout);

    RACE_BRIEF(action, player_car->gas_level, stderr)

    return EXIT_SUCCESS;
}

/**
 * @brief read positions of all the pilots of the track ans store them in there 
 * respective car struc
 * 
 * @param car_list 
 * @return int 
 */
int read_positions(struct car_t *car_list) {
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

/**
 * @brief print all the car info 
 * 
 * @param player_car 
 * @param file 
 */
void print_car(struct car_t *player_car, FILE *file) {
    fprintf(file, "Acc: %d %d\tSpeed: %d %d\tPos: %d %d\n", player_car->acc_x,
            player_car->acc_y, player_car->spe_x, player_car->spe_y,
            player_car->pos_x, player_car->pos_y);
    fprintf(file, "Gas: %d\tBoost: %d\n", player_car->gas_level,
            player_car->boosts);
    fflush(file);
}