#include "racing_algorithm.h"
#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "racing_a_star.h"
#include "racing_checkpoints.h"
#include "utils.h"
#include "test.h"

int main () {

    int width, height, i;
    int round = 0, gas = 0;
    int segment = 0, new_segment = 1;

    char line_buffer[MAX_LINE_LENGTH];
    FILE *logs, *logs_cout;

    list * list_opti_global;
    list * list_opti_local;
    list * list_endpos;

    stack *tmp_stack;

    weighted_map_t *A_star_global, *A_star_local;

    car_t cars[3];
    map_t map;

    tuple_int ** opti_global;
    tuple_int * end_pos;
    tuple_int * start_pos;
    tuple_int dir;

    //do_all_tests();

    fgets(line_buffer, MAX_LINE_LENGTH, stdin);
    sscanf(line_buffer, "%d %d %d", &width, &height, &gas);

    init_car(cars, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 1, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 2, BOOSTS_AT_START, 0, 0, 0, 0, gas);

    init_map(&map, height, width);
    fprintf(stderr, "Height: %d Width: %d Gas: %d\n", height, width, gas);

    // RACE_START(stderr)

    
    while (!feof(stdin)) {
        round++;
        // RACE_ROUND(round, stderr)
        read_positions(cars);
        
        if (round == 1) {
            A_star_global = init_weighted_map(map.height, map.width, *(cars[0].pos));
            list_endpos = find_end(map);
        
            pre_weight_map(A_star_global, &map, list_endpos);

            weight_map(A_star_global, &map, *(cars[0].pos), list_endpos, cars);
            

            list_opti_global = find_path(A_star_global, &map, *(cars[0].pos), list_endpos);
            tmp_stack = remove_useless_points(list_to_stack(list_opti_global));
            opti_global = (tuple_int **)(stack_to_tab(tmp_stack));

            fprintf(stderr, "size: %d\n", list_opti_global->size);
            for (i = 0; i < list_opti_global->size-1; i++) {
                fprintf(stderr, "%d %d\n", ((tuple_int *) get_list(list_opti_global, i))->x, ((tuple_int *) get_list(list_opti_global, i))->y);
            }

            print_map_path(&map, (tuple_int **) list_to_tab(list_opti_global), list_opti_global->size, stderr);
            print_map_path(&map, opti_global, tmp_stack->size, stderr);

        }
            
        start_pos = copy_tuple_int(*(cars[0].pos));
        
        if (new_segment){

            A_star_local = init_weighted_map(map.height, map.width, *(cars[0].pos));
            end_pos = copy_tuple_int(*(opti_global[segment]));
            list_endpos = create_list_from_obj(end_pos);
            pre_weight_map(A_star_local, &map, list_endpos);
        
            new_segment = 0;
        }

        weight_map(A_star_local, &map, *start_pos, list_endpos, cars);

        logs = fopen("log.txt", "w+");
        logs_cout = fopen("log_cout.txt", "w+");
        fprintf(logs, "Round n°%d, Segement n°%d\n", round, segment);
        fprintf(logs_cout, "Round n°%d, Segement n°%d\n", round, segment);
        print_float_weighted_map(A_star_local->cout, map.width, map.height, logs);
        fclose(logs);
        print_float_weighted_map(A_star_local->heuristique, map.width, map.height, logs_cout);
        fclose(logs_cout);

        list_opti_local = find_path(A_star_local, &map, *start_pos, list_endpos);
        dir = get_acc_to_reach(cars, map, *((tuple_int *) get_list(list_opti_local, 0)));
        set_acceleration(cars, dir.x, dir.y);

        //TEST FIN DE SEGMENT ICI
        

        consum_gas(cars, 0);
        post_actions(cars);
    }

    // TODO free plein de truc
    return EXIT_SUCCESS;
}