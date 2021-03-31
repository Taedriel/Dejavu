#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "utils.h"

int main() {
    int width, height;
    int round = 0;
    int gas = 0;
    char line_buffer[MAX_LINE_LENGTH];
    FILE * logs;

    car_t cars[3];
    map_t map;

    logs = fopen("log.txt", "w+");
    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read gas level at Start */
    sscanf(line_buffer, "%d %d %d", &width, &height, &gas);

    init_car(cars, BOOSTS_AT_START, 1, 0, 0, 0, gas);
    init_car(cars + 1, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 2, BOOSTS_AT_START, 0, 0, 0, 0, gas);

    init_map(&map, height, width);

    RACE_START(stderr)

    while (!feof(stdin)) {
        round++;
        RACE_ROUND(round, stderr)

        /*
        set_acceleration(cars, 1, 0);
        */
        read_positions(cars);

        if (round == 1) {
            int **parsed_map = parse_map(&map, *(cars[0].pos));

            print_weighted_map(parsed_map, map.width, map.height, logs);

            /*print_map_path(&map, opti, stderr); */
        }
        
        /* Gas consumption cannot be accurate here. */
        consum_gas(cars, 0);

        /* Write the acceleration request to the race manager (stdout). */
        post_actions(cars);
    }

    return EXIT_SUCCESS;
}