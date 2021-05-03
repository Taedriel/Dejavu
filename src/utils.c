#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void print_tuple(void *t, char *rep) {
    sprintf(rep, "%d %d", ((tuple_int *)t)->x, ((tuple_int *)t)->y);
}

tuple_int *copy_tuple_int(tuple_int o) {
    tuple_int *ret = malloc(sizeof(tuple_int));
    ret->x = o.x;
    ret->y = o.y;

    return ret;
}

tuple_int *create_tuple_int(int a, int b) {
    tuple_int *ret = malloc(sizeof(tuple_int));
    ret->x = a;
    ret->y = b;

    return ret;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int min(int a, int b) {
    return a <= b ? a : b;
}

int dot_product(tuple_int *a, tuple_int *b, tuple_int *c) {
    return (b->x - a->x) * (c->y - b->y) - (b->y - a->y) * (c->x - b->x);
}

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
    } else if (new_stack->head != test_cell) {
        push_stack(new_stack, test_cell);
    }

    return new_stack;
}