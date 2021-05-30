#include "racing_a_star.h"
#include "racing_algorithm.h"
#include "racing_checkpoints.h"
#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "test.h"
#include "utils.h"

#include <sys/resource.h>

int prepare_new_segment(int segment, list * list_checkpoint, weighted_map_t ** A_star_local, map_t map, car_t cars[3], tuple_int *start_pos, list ** list_endpos) {
    tuple_int * end_pos;

    if ((segment + 1) >= list_checkpoint->size) {
        // fprintf(stderr, "\n\nArrivé !!\n\n");
        return 1;
    }

    end_pos = copy_tuple_int((tuple_int *) get_list(list_checkpoint, segment + 1));
    *list_endpos = create_list_from_obj(end_pos);

    if (*A_star_local) {
        free_weighted_map(*A_star_local);
    }

    *A_star_local = init_weighted_map(map.height, map.width, *(cars[0].pos));


    pre_weight_map(*A_star_local, &map, *list_endpos);
    // fprintf(stderr, "New Segment %d Started ! Start: (%d %d) End (%d %d) Lenght: %f\n", segment, start_pos->x, start_pos->y, end_pos->x, end_pos->y, segment_len(list_checkpoint, segment));


    return 0;
}

tuple_int find_local_path(map_t map, weighted_map_t * A_star_local, tuple_int * start_pos, list * list_endpos, car_t cars[3], int segment, list * list_checkpoint, int round, int nb_point_tested) {
    
    double normed_speed;
    double max_normed_speed = 0.;
    double normed_speed_y;
    double normed_speed_x;
    int cpt;
    int i;
    int inSand;
    int old_x_value;

    tuple_int maxdir;
    tuple_int * v;
    tuple_int dir;

    list *list_opti_local;

    weight_map(A_star_local, &map, *start_pos, list_endpos, cars);

    list_opti_local = find_path(A_star_local, &map, *start_pos, list_endpos);

    maxdir.x = cars[0].spe->x > 0 ? -1 : (cars[0].spe->x < 0);
    maxdir.y = cars[0].spe->y > 0 ? -1 : (cars[0].spe->y < 0);
    cpt = 0;
    for (i = list_opti_local->size - 2; i >= 0 && cpt < nb_point_tested; i--) {
        v = copy_tuple_int((tuple_int *)get_list(list_opti_local, i));
        dir = get_acc_to_reach(&cars[0], map, *v, 0);

        tuple_int *futur_speed = create_tuple_int(cars[0].spe->x + dir.x, cars[0].spe->y + dir.y);

        normed_speed = distance(*futur_speed, create_0_0_tuple());
        inSand = is_in_sand(map, cars[0]);
        if (map.array[v->y][v->x] == SAND_CHAR) {
            normed_speed = 1;
        }

        if (normed_speed >= max_normed_speed && is_move_valid(map, cars, dir)) {
            if (normed_speed < MAX_SPEED && normed_speed <= segment_len(list_checkpoint, segment)+1.) {
                if (( inSand && normed_speed <= 1. ) || !inSand){
                    max_normed_speed = normed_speed;
                    maxdir.x = dir.x;
                    maxdir.y = dir.y;
                }
                if (inSand && normed_speed > 1.){
                    maxdir.x = 0;
                    maxdir.y = 0;

                    old_x_value = dir.x;
                    dir.x = 0;
                    tuple_int *futur_speed_y = create_tuple_int(cars[0].spe->x + dir.x, cars[0].spe->y + dir.y);
                    normed_speed_y = distance(*futur_speed_y, create_0_0_tuple());
                    free(futur_speed_y);
                    if (is_move_valid(map, cars, dir) && normed_speed_y <= 1.){
                        maxdir.x = dir.x;
                        maxdir.y = dir.y;
                    }

                    dir.x = old_x_value;
                    dir.y = 0;
                    tuple_int *futur_speed_x = create_tuple_int(cars[0].spe->x + dir.x, cars[0].spe->y + dir.y);
                    normed_speed_x = distance(*futur_speed_x, create_0_0_tuple());
                    free(futur_speed_x);
                    if (is_move_valid(map, cars, dir) && normed_speed_x <= 1.){
                        maxdir.x = dir.x;
                        maxdir.y = dir.y;
                    } 
                }
            }
        }
        cpt++;
        free(futur_speed);
        free(v);
    }

    return maxdir;
}

void find_global_path(weighted_map_t * A_star_global, car_t cars[3], map_t map, list ** list_checkpoint){

    list * list_endpos;
    list *list_opti_global;
    stack *tmp_stack;
    // FILE * logs_heur;
    // FILE * logs_dist;
    // FILE * logs_cout;

    A_star_global = init_weighted_map(map.height, map.width, *(cars[0].pos));
    list_endpos = find_end(map);

    pre_weight_map(A_star_global, &map, list_endpos);   
    weight_map(A_star_global, &map, *(cars[0].pos), list_endpos, cars);

    list_opti_global = find_path(A_star_global, &map, *(cars[0].pos), list_endpos);
    tmp_stack = remove_useless_points(list_to_stack(list_opti_global));

    print_map_path(&map, (tuple_int **) list_to_tab(list_opti_global), list_opti_global->size, stderr);
    print_map_path(&map, (tuple_int **) stack_to_tab(tmp_stack), tmp_stack->size, stderr);
    *list_checkpoint = stack_to_list(tmp_stack);

    // logs_heur = fopen("logs_global_heur.txt", "w+");
    // logs_dist = fopen("logs_global_dist.txt", "w+");
    // logs_cout = fopen("logs_global_cout.txt", "w+");
    // print_float_weighted_map(A_star_global->heuristique, map.width, map.height, logs_heur);
    // print_float_weighted_map(A_star_global->cout, map.width, map.height, logs_cout);
    // print_float_weighted_map(A_star_global->dist_from_end, map.width, map.height, logs_dist);

    // fclose(logs_heur);
    // fclose(logs_dist);
    // fclose(logs_cout);

    destroy_list(list_opti_global);
    destroy_list(list_endpos);
    destroy_stack(tmp_stack);
}


void get_input(car_t cars[3], tuple_int past_pos[3]) {
    int i;

    for (i = 0; i < 3; i++) {
        past_pos[i].x = cars[i].pos->x;
        past_pos[i].y = cars[i].pos->y;
    }

    read_positions(cars);
    // print_car(&cars[0], stderr);

    for (i = 0; i < 3; i++) {
        if ((past_pos[i].x == cars[i].pos->x) && (past_pos[i].y == cars[i].pos->y)) {
            if (i == 0)
                fprintf(stderr, "\n CAR STOPED ! RESET SPEED !\n\n");
            cars[i].spe->x = 0;
            cars[i].spe->y = 0;
        }
    }
}


int main () {

    int nb_point_tested = TEST_NB_FUTUR_POINT;
    int width, sand_around, cars_around;
    int end;
    int height;
    int round = 0, gas = 0;
    int segment = 0;
    int new_segment = 1;

    float estimate_gas;

    char line_buffer[MAX_LINE_LENGTH];

    list * list_opti_local;
    list * list_checkpoint = NULL;
    list * list_endpos = NULL;


    weighted_map_t *A_star_global = NULL;
    weighted_map_t *A_star_local = NULL;

    car_t cars[3];
    map_t map;

    tuple_int * start_pos;
    tuple_int maxdir;
    tuple_int * futur_pos;
    tuple_int * v;
    tuple_int past_pos[3]; 


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
        RACE_ROUND(round, stderr)

        get_input(cars, past_pos);

        if (round == 1) {
            find_global_path(A_star_global, cars, map, &list_checkpoint);
        }
        
        if (round >= 2){
            if (A_star_local->dist_from_end[futur_pos->y][futur_pos->x] <= get_normed_speed(cars[0])) {
                segment++;
                new_segment = 1;
            }
        }

        start_pos = copy_tuple_int(cars[0].pos);
        cars_around = nb_cars_around(map, cars, get_normed_speed(cars[0]) + DISTANCE_CARS_AROUND);
        sand_around = nb_sand_around(map, cars, DISTANCE_SAND_AROUND);
        // fprintf(stderr, "%d cars around - %d sand around\n", cars_around, sand_around);
        nb_point_tested = TEST_NB_FUTUR_POINT;
        nb_point_tested = min(nb_point_tested, (TEST_NB_FUTUR_POINT - cars_around));
        nb_point_tested = min(nb_point_tested, TEST_NB_FUTUR_POINT - (int)(sand_around/ NB_SAND_TO_CARE_AROUND));
        estimate_gas = estimate_gas_needed(&map, list_checkpoint, segment, start_pos, &cars[0]);
        fprintf(stderr, "gas estimated to finish race: %f\n", estimate_gas);
        fprintf(stderr, "gas level: %d (%f)\n", cars[0].gas_level, cars[0].gas_level * 0.90);
        nb_point_tested = cars[0].gas_level - (estimate_gas * 0.90) < 0 ? 1 : nb_point_tested;

        fprintf(stderr, "NB POINT TESTED FOR THIS ROUND: %d\n\n", nb_point_tested);
        nb_point_tested = max(nb_point_tested, 1);


        if (new_segment){
            end = prepare_new_segment(segment, list_checkpoint, &A_star_local, map, cars, start_pos, &list_endpos);
        }

        if (end) {
            list_endpos = find_end(map);
            weight_map(A_star_local, &map, *start_pos, list_endpos, cars);
            list_opti_local = find_path(A_star_local, &map, *start_pos, list_endpos);

            v = copy_tuple_int((tuple_int *)get_list(list_opti_local, list_opti_local->size - 2));
            maxdir = get_acc_to_reach(&cars[0], map, *v, 0);
        }else {
            maxdir = find_local_path(map, A_star_local, start_pos, list_endpos, cars, segment, list_checkpoint, round, nb_point_tested);
        }

        set_acceleration(cars, maxdir.x, maxdir.y);

        futur_pos = create_tuple_int(cars[0].pos->x + cars[0].acc->x + cars[0].spe->x, cars[0].pos->y + cars[0].acc->y + cars[0].spe->y);
        // fprintf(stderr, "futur pos will be: %d %d (dist_from_end = %f)\n", futur_pos->x, futur_pos->y, A_star_local->dist_from_end[futur_pos->y][futur_pos->x]);

        consum_gas(cars, 0);
        post_actions(cars);
    }

    free_weighted_map(A_star_global);
    free_weighted_map(A_star_local);

    free_car(cars);
    free_car(cars + 1);
    free_car(cars + 2);

    destroy_list(list_opti_local);
    destroy_list(list_endpos);

    free(start_pos);
    free(futur_pos);
    free(v);

    return EXIT_SUCCESS;
}
