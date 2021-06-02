#include <sys/resource.h>

#include "racing_a_star.h"
#include "racing_algorithm.h"
#include "racing_checkpoints.h"
#include "racing_driver.h"
#include "racing_io.h"
#include "racing_map.h"
#include "test.h"
#include "utils.h"

tuple_int find_local_path(map_t map, list *path, car_t cars[3], int round, int nb_point_tested, int boost) {
    double normed_speed;
    double max_normed_speed = 0.;
    double normed_speed_y;
    double normed_speed_x;
    int cpt;
    int i;
    int inSand;
    int old_x_value;

    tuple_int maxdir;
    tuple_int *v;
    tuple_int dir;

    maxdir.x = cars[0].spe->x > 0 ? -1 : (cars[0].spe->x < 0);
    maxdir.y = cars[0].spe->y > 0 ? -1 : (cars[0].spe->y < 0);
    cpt = 0;
    for (i = path->size - 2; i >= 0 && cpt < nb_point_tested; i--) {
        v = copy_tuple_int((tuple_int *)get_list(path, i));
        dir = get_acc_to_reach(&cars[0], map, *v, boost);

        tuple_int *futur_speed = create_tuple_int(cars[0].spe->x + dir.x, cars[0].spe->y + dir.y);

        normed_speed = distance(*futur_speed, create_0_0_tuple());
        inSand = is_in_sand(map, cars[0]);

        if (normed_speed >= max_normed_speed && is_move_valid(map, cars, dir) && normed_speed < MAX_SPEED) {
            if ((inSand && normed_speed <= 1.) || !inSand) {
                max_normed_speed = normed_speed;
                maxdir.x = dir.x;
                maxdir.y = dir.y;
            }
            if (inSand && normed_speed > 1.) {
                maxdir.x = 0;
                maxdir.y = 0;

                old_x_value = dir.x;
                dir.x = 0;
                tuple_int *futur_speed_y = create_tuple_int(cars[0].spe->x + dir.x, cars[0].spe->y + dir.y);
                normed_speed_y = distance(*futur_speed_y, create_0_0_tuple());
                free(futur_speed_y);
                if (is_move_valid(map, cars, dir) && normed_speed_y <= 1.) {
                    maxdir.x = dir.x;
                    maxdir.y = dir.y;
                }

                dir.x = old_x_value;
                dir.y = 0;
                tuple_int *futur_speed_x = create_tuple_int(cars[0].spe->x + dir.x, cars[0].spe->y + dir.y);
                normed_speed_x = distance(*futur_speed_x, create_0_0_tuple());
                free(futur_speed_x);
                if (is_move_valid(map, cars, dir) && normed_speed_x <= 1.) {
                    maxdir.x = dir.x;
                    maxdir.y = dir.y;
                }
            }
        }
        cpt++;
        free(futur_speed);
        free(v);
    }

    return maxdir;
}

void get_input(car_t cars[3], tuple_int past_pos[3], weighted_map_t *A_star, map_t map, list *list_endpos) {
    int i;

    for (i = 0; i < 3; i++) {
        past_pos[i].x = cars[i].pos->x;
        past_pos[i].y = cars[i].pos->y;
    }

    read_positions(cars);

    for (i = 0; i < 3; i++) {
        if ((past_pos[i].x == cars[i].pos->x) && (past_pos[i].y == cars[i].pos->y)) {
            cars[i].spe->x = 0;
            cars[i].spe->y = 0;
            pre_weight_map(A_star, &map, list_endpos);
        }
    }
}

int main() {
    int nb_point_tested = TEST_NB_FUTUR_POINT;
    int width, sand_around;
    int height;
    int round = 0, gas = 0;

    float estimate_gas;

    char line_buffer[MAX_LINE_LENGTH];

    list *path = NULL;
    list *list_endpos = NULL;

    weighted_map_t *A_star = NULL;

    car_t cars[3];
    map_t map;

    tuple_int *start_pos;
    tuple_int maxdir;
    tuple_int past_pos[3];

    fgets(line_buffer, MAX_LINE_LENGTH, stdin);
    sscanf(line_buffer, "%d %d %d", &width, &height, &gas);

    init_car(cars, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 1, BOOSTS_AT_START, 0, 0, 0, 0, gas);
    init_car(cars + 2, BOOSTS_AT_START, 0, 0, 0, 0, gas);

    init_map(&map, height, width);


    while (!feof(stdin)) {
        round++;
        // RACE_ROUND(round, stderr)
        get_input(cars, past_pos, A_star, map, list_endpos);
        start_pos = copy_tuple_int(cars[0].pos);
        list_endpos = find_end(map);

        if (round == 1) {
            A_star = init_weighted_map(height, width, *(cars[0].pos));
            pre_weight_map(A_star, &map, list_endpos);
        }

        weight_map(A_star, &map, *start_pos, list_endpos, cars);
        path = find_path(A_star, &map, *start_pos, list_endpos, cars);

        sand_around = nb_sand_around(map, cars, DISTANCE_SAND_AROUND);

        nb_point_tested = TEST_NB_FUTUR_POINT;
        nb_point_tested = min(nb_point_tested, TEST_NB_FUTUR_POINT - (int)(sand_around / NB_SAND_TO_CARE_AROUND));
        estimate_gas = estimate_gas_needed(&map, path, start_pos, &cars[0]);
        
        nb_point_tested = (cars[0].gas_level - estimate_gas) < 0 ? 1 : nb_point_tested;
        nb_point_tested = max(nb_point_tested, 1);
        maxdir = find_local_path(map, path, cars, round, nb_point_tested, 0);

        set_acceleration(cars, maxdir.x, maxdir.y);

        consum_gas(cars, 0);
        post_actions(cars);
    }

    free_weighted_map(A_star);

    free_car(cars);
    free_car(cars + 1);
    free_car(cars + 2);

    destroy_list(list_endpos);

    free(start_pos);

    return EXIT_SUCCESS;
}
