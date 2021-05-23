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

double segment_len(tuple_int **checkpoint, int checkpoint_size, int index) {
    if (index + 1 > checkpoint_size) {
        return -1;
    }
    return distance(*(checkpoint[index]), *(checkpoint[index + 1]));
}

int get_weight_checkpoint(tuple_int **checkpoint, int checkpoint_size, int index, weighted_map_t *weighted_map) {
    return weighted_map->dist_from_end[checkpoint[index]->y][checkpoint[index]->x];
}

int get_segment_by_coord(tuple_int **checkpoint, int checkpoint_size, weighted_map_t *weighted_map, tuple_int *coord) {
    int heuristique_car;
    int heuristique_checkpoint;
    int i;

    for (i = 0; i < checkpoint_size - 1; i++) {
        heuristique_checkpoint = get_weight_checkpoint(checkpoint, checkpoint_size, i, weighted_map);
        heuristique_car = weighted_map->dist_from_end[coord->y][coord->x];
        fprintf(stderr, "%d %d\n", heuristique_car, heuristique_checkpoint);
        if (heuristique_car <= heuristique_checkpoint) {
            return i;
        }
    }
    return -1;

}

int get_segment(tuple_int **checkpoint, int checkpoint_size, weighted_map_t *weighted_map, car_t *car) {
    return get_segment_by_coord(checkpoint, checkpoint_size, weighted_map, car->pos);
}