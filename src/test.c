#include "test.h"

void do_all_tests() {
    test_remove_useless_points();
}

void test_remove_useless_points() {
    tuple_int a1 = {1,1};
    tuple_int a2 = {2,2};
    tuple_int a3 = {3,3};
    tuple_int a4 = {1,3};
    tuple_int a5 = {1,4};
    tuple_int a6 = {1,5};

    stack * Stack = create_stack();
    stack * Stack1 = create_stack();

    push_stack(Stack, &a1);
    push_stack(Stack, &a2);
    push_stack(Stack, &a3);
    push_stack(Stack, &a4);
    push_stack(Stack, &a5);
    push_stack(Stack, &a6);

    Stack1 = remove_useless_points(Stack);

    fprintf(stderr, "Beginning test : %d\n", is_stack_empty(Stack1));

    while(!is_stack_empty(Stack1)) {
        tuple_int * a =  pop_stack(Stack1);
        fprintf(stderr, "%d %d\n", a->x, a->y);
    }
    
    fprintf(stderr, "Ending test\n");
}