#include "racing_checkpoints.h"

stack *remove_useless_points(stack *traj) {
    stack *new_stack = create_stack();

    tuple_int *begin_seg = (tuple_int *)pop_stack(traj);
    tuple_int *end_seg = (tuple_int *)pop_stack(traj);
    tuple_int *test_cell = NULL;

    push_stack(new_stack, begin_seg);
    while (!is_stack_empty(traj)) {
        test_cell = (tuple_int *)pop_stack(traj);
        if (dot_product(begin_seg, end_seg, test_cell)) {
            push_stack(new_stack, end_seg);
            begin_seg = end_seg;
        }
        end_seg = test_cell;
    }
    if (!test_cell) {
        push_stack(new_stack, end_seg);
    } else if (new_stack->head->x != test_cell) {
        push_stack(new_stack, test_cell);
    }
    return new_stack;
}

double segment_len(tuple_int **tab, int tab_size, int index) {
    if (index + 1 > tab_size) {
        return -1;
    }
    return distance(*(tab[index]), *(tab[index + 1]));
}

int get_weight_checkpoint(tuple_int **tab, int tab_size, int index, weighted_map_t *weighted_map) {
    tuple_int *checkpoint_coord;
    checkpoint_coord = tab[index];
    return weighted_map->heuristique[checkpoint_coord->y][checkpoint_coord->x];
}

int get_segment_by_coord(tuple_int **tab, int tab_size, weighted_map_t *weighted_map, tuple_int *coord) {
    int heuristique_car;
    int heuristique_checkpoint;
    int i;

    for (i = 0; i < tab_size - 1; i++) {
        heuristique_checkpoint = get_weight_checkpoint(tab, tab_size, i, weighted_map);
        heuristique_car = weighted_map->heuristique[coord->y][coord->x];
        fprintf(stderr, "heuristique_checkpoint : %d, heuristique_car : %d \n", heuristique_checkpoint, heuristique_car);
        if (heuristique_car < heuristique_checkpoint) {
            return i-1;
        }
    }
    return -1;

}

int get_segment(tuple_int **tab, int tab_size, weighted_map_t *weighted_map, car_t *car) {
    return get_segment_by_coord(tab, tab_size, weighted_map, car->pos);
}