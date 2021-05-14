#include "racing_algorithm.h"
#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "racing_weighted_map.h"
#include "utils.h"

int main () {

    int width, height, size_end_pos, i;
    int round = 0;
    int gas = 0;
    char line_buffer[MAX_LINE_LENGTH];
    FILE *logs, *logs_cout;

    list * list_opti;
    weighted_map_t *A_star;
    car_t cars[3];
    map_t map;

    tuple_int **opti;
    tuple_int **endpos;
    tuple_int dir;

    logs = fopen("log.txt", "w+");
    logs_cout = fopen("log_cout.txt", "w+");
    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read gas level at Start */
    sscanf(line_buffer, "%d %d %d", &width, &height, &gas);

    init_car(cars, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 1, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 2, BOOSTS_AT_START, 0, 0, 0, 0, gas);

    init_map(&map, height, width);

    // RACE_START(stderr)

    
    while (!feof(stdin)) {
        round++;
        /*
        RACE_ROUND(round, stderr)
        set_acceleration(cars, 1, 0);
        */
        read_positions(cars);

        /*
        tuple_int point = {26,5};
        tuple_int TEST_AHHHH = get_acc_to_reach(cars, point);
        set_acceleration_on_tuple(cars, TEST_AHHHH);
        print_car(cars, stderr);
        */

        if (round == 1) {
            endpos = find_end(map, &size_end_pos);

            A_star = init_weighted_map(map.height, map.width, *(cars[0].pos));
            
            pre_weight_map(A_star, &map, endpos, size_end_pos);
            // min = -1;
            // for (i = 0; i < size_end_pos; i++) {
            //     if (min == -1 || min > A_star->heuristique[endpos[i]->y][endpos[i]->x]) {
            //         min = A_star->heuristique[endpos[i]->y][endpos[i]->x];
            //         min_ind = i;
            //     }
            // }


            weight_map(A_star, &map, *(cars[0].pos), endpos, size_end_pos, cars);
            
            print_float_weighted_map(A_star->dist_from_end, map.width, map.height, logs);
            fclose(logs);
            fflush(logs);
            print_float_weighted_map(A_star->heuristique, map.width, map.height, logs_cout);
            fclose(logs_cout);
            fflush(logs_cout);

            list_opti = find_path(A_star, &map, *(cars[0].pos), endpos, size_end_pos);
            opti = (tuple_int **)(list_to_tab(list_opti)); 

            fprintf(stderr, "size: %d\n", list_opti->size);
            for (i = list_opti->size-1; i > 0; i--) {
                fprintf(stderr, "%d %d\n", opti[i]->x, opti[i]->y);
            }

            print_map_path(&map, opti, list_opti->size, stderr);
        }

        /* Gas consumption cannot be accurate here. */
        consum_gas(cars, 0);

        fprintf(stderr, "%d %d\n", opti[list_opti->size - round - 1]->x,
                opti[list_opti->size - round - 1]->y);
        dir = get_acc_to_reach(cars, map, *(opti[list_opti->size - round - 1]));
        set_acceleration(cars, dir.x, dir.y);

        /* Write the acceleration request to the race manager (stdout). */
        post_actions(cars);
    }

    // TODO free plein de truc
    return EXIT_SUCCESS;
}