#include "racing_driver.h"
#include "racing_io.h"
#include "racing_checkpoints.h"
#include "follow_line.h"

void init_car(struct car_t* player_car, int boosts, int acc_x, int acc_y,
              int spe_x, int spe_y, int gas) {
    player_car->acc = create_tuple_int(acc_x, acc_y);
    player_car->spe = create_tuple_int(spe_x, spe_y);
    player_car->pos = create_tuple_int(0, 0);
    player_car->boosts = boosts;
    player_car->gas_level = gas;
}

void free_car(car_t *car) {
    free(car->pos);
    free(car->spe);
    free(car->acc);
}

int gas_consumption(struct car_t* player_car, int inSand) {
    int gas = pow_int_2(player_car->acc->x) + pow_int_2(player_car->acc->y);
    gas += (int)(get_normed_speed(*player_car) * 3. / 2.);
    if (inSand) {
        gas += 1;
    }
    return gas;
}

void consum_gas(struct car_t* player_car, int inSand) {
    player_car->gas_level -= gas_consumption(player_car, inSand);
    player_car->spe->x = (inSand) ? player_car->spe->x > 0 : player_car->spe->x + player_car->acc->x;
    player_car->spe->y = (inSand) ? player_car->spe->y > 0 : player_car->spe->y + player_car->acc->y;
}

double estimate_gas_needed(map_t *map, list * path, tuple_int * start_pos, car_t * car) {

    int i;
    double ret = 0.;
    tuple_int gas;
    
    if (path->size - 1 > 0){

        ret += distance(*start_pos, *((tuple_int *) get_list(path, 0))) * 2;

        for (i = 1; i < path->size - 1; i++) {

            ret += distance(*((tuple_int *) get_list(path, i)), *((tuple_int *) get_list(path, i+1)));
        }
    }

    return ret;
}

tuple_int estimation_gas(map_t *map, tuple_int begin, tuple_int end, car_t *car) {
    int worst_consum;
    int best_consum; 
    car_t tempory_car;

    tuple_int new_acc;
    tuple_int estimation;
    int len_seg;
    int ponctual_consumtion;

    init_car(&tempory_car, 0, 2, 2, 2, 2, 0);
    ponctual_consumtion = gas_consumption(&tempory_car, 0);
    free_car(&tempory_car);

    len_seg = distance(begin, end);
    worst_consum = len_seg * ponctual_consumtion;
    
    init_car(&tempory_car, car->boosts, car->acc->x, car->acc->y, car->spe->x, car->spe->y, car->gas_level);
    tempory_car.pos->x = car->pos->x;
    tempory_car.pos->y = car->pos->y;

    best_consum = 0;
    while (distance(*(tempory_car.pos), end) > 1.) {

        new_acc = get_acc_to_reach(&tempory_car, *map, end, 0);
        new_acc.x = (abs(tempory_car.spe->x + new_acc.x) > 1) ? 0 : new_acc.x;
        new_acc.y = (abs(tempory_car.spe->y + new_acc.y) > 1) ? 0 : new_acc.y;

        set_acceleration_on_tuple(&tempory_car, new_acc);
        tempory_car.spe->x += new_acc.x;
        tempory_car.spe->y += new_acc.y;
        
        best_consum += gas_consumption(&tempory_car, is_in_sand(*map, tempory_car));
        
        tempory_car.pos->x += tempory_car.spe->x;
        tempory_car.pos->y += tempory_car.spe->y;

        tempory_car.pos->x = (tempory_car.pos->x > 0) ? tempory_car.pos->x : 0;
        tempory_car.pos->y = (tempory_car.pos->y > 0) ? tempory_car.pos->y : 0;
    }
    free_car(&tempory_car);
    estimation.x = best_consum;
    estimation.y = worst_consum;
    return estimation;
}

void set_acceleration(struct car_t* player_car, int acc_x, int acc_y) {
    player_car->acc->x = acc_x;
    player_car->acc->y = acc_y;
}

void set_acceleration_on_tuple(struct car_t* player_car, tuple_int acc) {
    set_acceleration(player_car, acc.x, acc.y);
}

tuple_int * dist_to_futur_pos(tuple_int futur_pos, car_t car) {
    tuple_int * ret = create_tuple_int(0,0);

    ret->x = futur_pos.x - (car.pos->x + car.spe->x);
    ret->y = futur_pos.y - (car.pos->y + car.spe->y);
    return ret;
}

/**
 * @todo ici on doit recup le segment en question 
 * puis on calcule la distance. Enfin, un if 
 * arbitraire avec une valeur choisi de longeur limite
 * avant le boost. 
 */
int normed_acc(int acc_require, int boost_allowed) {
    if (acc_require < 0 && !boost_allowed)
        return -1;
    if (acc_require > 0 && !boost_allowed)
        return 1;
    if (acc_require > 1 && boost_allowed)
        return 2;
    if (acc_require < -1 && boost_allowed)
        return -2;
    return 0;
}

tuple_int get_acc_to_reach(struct car_t* car, struct map_t map, tuple_int to_reach, int boost_allowed) {
    tuple_int acc;
    tuple_int * deltaToReach;

    deltaToReach = dist_to_futur_pos(to_reach, *car);
    acc.x = normed_acc(deltaToReach->x, boost_allowed);
    acc.y = normed_acc(deltaToReach->y, boost_allowed); 

    if (is_in_sand(map, *car) && (abs(acc.x) == abs(acc.y)) && (abs(acc.y) == 1)){
        if (rand()%2 == 0) {
            acc.x = 0;
        } else {
            acc.y = 0;
        }
    }
    // fprintf(stderr, "To Reach: %d %d\nDelta: \t%d %d\nAcc: \t%d %d\n", to_reach.x, to_reach.y, deltaToReach->x, deltaToReach->y, acc.x, acc.y);
    free(deltaToReach);
    return acc;
}

int is_valid_acceleration(struct car_t* car, tuple_int acc, struct map_t map) {
    int x = car->pos->x + car->spe->x + acc.x;
    int y = car->pos->y + car->spe->y + acc.y;

    int is_xy_valide = map.array[y][x] == ROAD_CHAR;
    int is_x_valide = map.array[car->pos->y][x] == ROAD_CHAR;
    int is_y_valide = map.array[y][car->pos->x] == ROAD_CHAR;

    if (is_xy_valide) {
        return ERROR_ACC_NO;
    }
    if (is_x_valide) {
        return ERROR_ACC_Y;
    }
    if (is_y_valide) {
        return ERROR_ACC_X;
    }
    return ERROR_ACC_ALL;
}

int is_move_valid(map_t map, car_t cars[3], tuple_int acc_asked){
    //using follow_line.c, 
    InfoLine * line = malloc(sizeof(InfoLine));
    Pos2Dint * pos = malloc(sizeof(Pos2Dint));
    tuple_int * futur_pos = create_tuple_int(cars[0].spe->x + cars[0].pos->x + acc_asked.x, cars[0].spe->y + cars[0].pos->y + acc_asked.y);

    initLine(cars[0].pos->x, cars[0].pos->y, futur_pos->x, futur_pos->y, line);

    while (nextPoint(line, pos, 1) != -1){
        if (map.array[pos->y][pos->x] == WALL_CHAR){
            free(line);
            free(pos);
            return 0;
        }
    }

    free(line);
    free(pos);
    free(futur_pos);
    return 1;
}

double get_normed_speed(car_t car) {
    return sqrt(pow_int_2(car.spe->x) + pow_int_2(car.spe->y));
}

int nb_cars_around(map_t map, car_t cars[3], int distance) {

    int i, x, y, cpt = 0;
    int delta = sqrt((distance * distance)/2);

    fprintf(stderr, "DELTA: %d - (%d %d) -> (%d %d)\n", delta, max(0, cars[0].pos->x - delta), max(0, cars[0].pos->y - delta), min(map.width - 1, cars[0].pos->x + delta + 1), min(map.height - 1, cars[0].pos->y + delta + 1));

    for (y = max(0, cars[0].pos->y - delta); y < min(map.height-1, cars[0].pos->y + delta + 1); y++){
        for (x = max(0, cars[0].pos->x - delta); x < min(map.width-1, cars[0].pos->x + delta + 1); x++){
            for(i = 1; i < 3; i++){
                if (cars[i].pos->x == x && cars[i].pos->y == y){
                    cpt += 1;
                }
            }
        }
    }

    return cpt;
}

int nb_sand_around(map_t map, car_t cars[3], int distance) {

    int x, y, cpt = 0;
    int delta = sqrt((distance * distance) / 2);

    fprintf(stderr, "DELTA: %d - (%d %d) -> (%d %d)\n", delta, max(0, cars[0].pos->x - delta), max(0, cars[0].pos->y - delta), min(map.width - 1, cars[0].pos->x + delta + 1), min(map.height - 1, cars[0].pos->y + delta + 1));

    for (y = max(0, cars[0].pos->y - delta); y < min(map.height - 1, cars[0].pos->y + delta + 1); y++) {
        for (x = max(0, cars[0].pos->x - delta); x < min(map.width - 1, cars[0].pos->x + delta + 1); x++) {
            if (map.array[y][x] == SAND_CHAR) {
                cpt += 1;
            }
        }
    }

    return cpt;
}