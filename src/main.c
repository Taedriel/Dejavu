#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "utils.h"

int main() {
    int width, height, size, opti_size, i;
    int round = 0;
    int gas = 0;
    char line_buffer[MAX_LINE_LENGTH];
    FILE * logs;

    tuple_int ** endpos;
    tuple_int ** opti;
    car_t cars[3];
    map_t map;

    logs = fopen("log.txt", "w+");
    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read gas level at Start */
    sscanf(line_buffer, "%d %d %d", &width, &height, &gas);

    init_car(cars, BOOSTS_AT_START, 1, 0, 0, 0, gas);
    init_car(cars + 1, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 2, BOOSTS_AT_START, 0, 0, 0, 0, gas);

    init_map(&map, height, width);
    fprintf(stderr, "%d %d\n", height, width);

    RACE_START(stderr)

    while (!feof(stdin)) {
        round++;
        RACE_ROUND(round, stderr)

        /*
        set_acceleration(cars, 1, 0);
        */
        read_positions(cars);

        tuple_int point = {30,30};
        tuple_int TEST_AHHHH = get_acc_to_reach(cars, point);
        fprintf(stderr, "%d %d\n",TEST_AHHHH.x, TEST_AHHHH.y );

        if (round == 1) {
            int **parsed_map = parse_map(&map, *(cars[0].pos));

            print_weighted_map(parsed_map, map.width, map.height, logs);
            fflush(logs);
            fclose(logs);

            endpos = find_end(map, &size);
            opti = find_path(parsed_map, &map, &opti_size, *(cars[0].pos), *(endpos[0]));

            for (i = 0; i < opti_size; i++){
                fprintf(stderr, "%d %d\n", opti[i]->x, opti[i]->y);
            }

            print_map_path(&map, opti, opti_size, stderr);
        }
        
        /* Gas consumption cannot be accurate here. */
        consum_gas(cars, 0);

        /* Write the acceleration request to the race manager (stdout). */
        post_actions(cars);
    }


    //TODO free plein de truc 
    return EXIT_SUCCESS;
}