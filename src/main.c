#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "utils.h"

int main() {
    int width, height, size, opti_size, i, min, min_ind;
    int round = 0;
    int gas = 0;
    char line_buffer[MAX_LINE_LENGTH];
    FILE * logs;

    tuple_int ** endpos;
    tuple_int ** opti;
    tuple_int dir;
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

        tuple_int point = {26,5};
        tuple_int TEST_AHHHH = get_acc_to_reach(cars, point);
        set_acceleration_on_tuple(cars, TEST_AHHHH);
        print_car(cars, stderr);

        if (round == 1) {
            int **djikstra = parse_map(&map, *(cars[0].pos));

            print_weighted_map(djikstra, map.width, map.height, logs);
            fflush(logs);
            fclose(logs);

            endpos = find_end(map, &size);
            min = -1;
            for (i = 0; i < size; i++){
                if (min == -1 || min > djikstra[endpos[i]->y][endpos[i]->x]){
                    min = djikstra[endpos[i]->y][endpos[i]->x];
                    min_ind = i;
                }
            }
            opti = find_path(djikstra, &map, &opti_size, *(cars[0].pos), *(endpos[min_ind]));

            for (i = 0; i < opti_size; i++){
                fprintf(stderr, "%d %d\n", opti[i]->x, opti[i]->y);
            }

            print_map_path(&map, opti, opti_size, stderr);
        }
        
        /* Gas consumption cannot be accurate here. */
        consum_gas(cars, 0);

        dir = get_acc_to_reach(cars, *(opti[round]));
        set_acceleration(cars, dir.x, dir.y);

        /* Write the acceleration request to the race manager (stdout). */
        post_actions(cars);
    }


    //TODO free plein de truc 
    return EXIT_SUCCESS;
}