#include "racing_algorithm.h"
#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "racing_a_star.h"
#include "racing_checkpoints.h"
#include "utils.h"
#include "test.h"

int main () {

    int width;
    int height;
    int i;
    int max_normed_speed;
    int normed_speed;
    int cpt;
    int round = 0, gas = 0;
    int segment = 0;
    int new_segment = 1;
    int indice_end_point;

    char line_buffer[MAX_LINE_LENGTH];
    FILE *logs_cout, *logs_heur, *logs_dist;

    list * list_opti_global;
    list * list_opti_local;
    list * list_endpos;

    stack *tmp_stack;

    weighted_map_t *A_star_global;
    weighted_map_t *A_star_local;

    car_t cars[3];
    map_t map;

    tuple_int ** opti_global;
    tuple_int * end_pos;
    tuple_int * start_pos;
    tuple_int dir, maxdir;
    tuple_int * futur_pos;
    tuple_int * v;
    tuple_int * temp;

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

        for (i=0; i<3;i++){
            past_pos[i].x = cars[i].pos->x; 
            past_pos[i].y = cars[i].pos->y;
        }

        read_positions(cars);

        for(i=0;i<3;i++){
            if ((past_pos[i].x == cars[i].pos->x) && (past_pos[i].y == cars[i].pos->y)){
                cars[i].spe->x = 0;
                cars[i].spe->y = 0;
            }
        }

        if (round >= 2){
            if (A_star_local->dist_from_end[futur_pos->y][futur_pos->x] <= get_normed_speed(cars[0])) {
                segment++;
                new_segment = 1;
            }
        }

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

            logs_heur = fopen("logs_global_heur.txt", "w+");
            print_float_weighted_map(A_star_global->heuristique, map.width, map.height, logs_heur);
            fclose(logs_heur);

        }
            
        start_pos = copy_tuple_int(cars[0].pos);
        
        if (new_segment){

            if ((segment+1) >= tmp_stack->size){
                fprintf(stderr, "\n\nArrivé !!\n\n");
                goto end;
            }

            end_pos = copy_tuple_int(opti_global[segment+1]);
            list_endpos = create_list_from_obj(end_pos);
            A_star_local = init_weighted_map(map.height, map.width, *(cars[0].pos));
            // indice_end_point = 0;
            // for (i = 0; i < list_opti_global->size; i++) {
            //     temp = (tuple_int *) get_list(list_opti_global, i);
            //     if (temp->x == end_pos->x && temp->y == end_pos->y){
            //         indice_end_point = i;
            //         break;
            //     }
            // }
            // for (i = indice_end_point-1; i < max(list_opti_global->size, indice_end_point - NB_CASE_END); i--) {
            //     add_list(list_endpos, get_list(list_opti_global, i));
            // }
            pre_weight_map(A_star_local, &map, list_endpos);
            fprintf(stderr, "New Segment %d Started ! Start: (%d %d) End (%d %d) Lenght: %f\n", segment, start_pos->x, start_pos->y \
            ,end_pos->x, end_pos->y, segment_len(opti_global, tmp_stack->size, segment));
        
            new_segment = 0;
        }

        weight_map(A_star_local, &map, *start_pos, list_endpos, cars);

        logs_heur = fopen("log_heur.txt", "w+");
        logs_dist = fopen("log_dist.txt", "w+");
        logs_cout = fopen("log_cout.txt", "w+");
        fprintf(logs_heur, "Round n°%d, Segement n°%d\n", round, segment);
        fprintf(logs_dist, "Round n°%d, Segement n°%d\n", round, segment);
        fprintf(logs_cout, "Round n°%d, Segement n°%d\n", round, segment);
        print_float_weighted_map(A_star_local->cout, map.width, map.height, logs_cout);
        print_float_weighted_map(A_star_local->heuristique, map.width, map.height, logs_heur);
        print_float_weighted_map(A_star_local->dist_from_end, map.width, map.height, logs_dist);
        fclose(logs_cout);
        fclose(logs_heur);
        fclose(logs_dist);

        list_opti_local = find_path(A_star_local, &map, *start_pos, list_endpos);
        print_list(list_opti_local, print_tuple, stderr);
        // fprintf(stderr, "SIZE PATH: %d\n", list_opti_local->size);
        print_car(&cars[0], stderr);
        max_normed_speed = 0;
        maxdir.x = cars[0].spe->x > 0 ? -1 : (cars[0].spe->x < 0);
        maxdir.y = cars[0].spe->y > 0 ? -1 : (cars[0].spe->y < 0);
        cpt = 0;
        for (i = list_opti_local->size-2; i >= 0 && cpt < TEST_NB_FUTUR_POINT; i--) {
            v = copy_tuple_int((tuple_int *)get_list(list_opti_local, i));
            dir = get_acc_to_reach(cars, map, *v, 0);

            /**
             * @todo j'ai mis ça la en attendant d'avoir une fonction qui fait tout ça.
             * Pour l'ODL pas le droit à cette declaration ici.
             * 
             */
            tuple_int * temp_tuple_1 = create_tuple_int(cars[0].spe->x + dir.x, cars[0].spe->y + dir.y);

            normed_speed = distance(*temp_tuple_1, create_0_0_tuple());
            if (map.array[v->y][v->x] == SAND_CHAR) {
                normed_speed = 1; 
            }


            fprintf(stderr, "normed speed: %d\t", normed_speed);
            fprintf(stderr, "valide move ? %d <= dist_from_end ? %d | %d < %d ? %d\n", is_move_valid(map, cars, dir), normed_speed <= segment_len(opti_global, tmp_stack->size, segment), normed_speed, MAX_SPEED, normed_speed < MAX_SPEED);

            if (normed_speed >= max_normed_speed && is_move_valid(map, cars, dir)) {
                if (normed_speed < MAX_SPEED && max_normed_speed <= normed_speed && normed_speed <= segment_len(opti_global, tmp_stack->size, segment)) {
                    max_normed_speed = normed_speed;
                    maxdir.x = dir.x;
                    maxdir.y = dir.y;   
                }
            }
            cpt++;
            free(temp_tuple_1);
            free(v);
        }
        goto accel;

        end:
        weight_map(A_star_local, &map, *start_pos, list_endpos, cars);
        list_opti_local = find_path(A_star_local, &map, *start_pos, list_endpos);

        v = copy_tuple_int((tuple_int *)get_list(list_opti_local, list_opti_local->size - 2));
        dir = get_acc_to_reach(cars, map, *v, 0);
        maxdir.x = dir.x;
        maxdir.y = dir.y;

        accel:
        set_acceleration(cars, maxdir.x, maxdir.y);

        // new_seg = get_segment_by_coord((tuple_int **)list_to_tab(list_opti_local), list_opti_local->size, A_star_local, cars[0].pos);
        // fprintf(stderr, "Segment at the end: %d\nCurrent Segment: %d\n", new_seg, segment);
        futur_pos = create_tuple_int(cars[0].pos->x + cars[0].acc->x + cars[0].spe->x, cars[0].pos->y + cars[0].acc->y + cars[0].spe->y);
        fprintf(stderr, "futur pos will be: %d %d (dist_from_end = %f)\n", futur_pos->x, futur_pos->y, A_star_local->dist_from_end[futur_pos->y][futur_pos->x]);

        consum_gas(cars, is_in_sand(&map, cars));
        post_actions(cars);
    }

    // TODO free plein de truc

    fclose(logs_cout);
    fclose(logs_heur);
    fclose(logs_dist);

    free_weighted_map(A_star_global);
    free_weighted_map(A_star_local);

    destroy_list(list_opti_global);
    destroy_list(list_opti_local);
    destroy_list(list_endpos);

    destroy_stack(tmp_stack);

    free(end_pos);
    free(start_pos);
    free(futur_pos);
    free(v);

    return EXIT_SUCCESS;
}
