#ifndef FILE_H
#define FILE_H


typedef struct cell {
    void * x;
    struct cell* next;
}cell;

typedef struct stack {
    cell* head;
    cell* tail;
}stack;

stack* create_stack();

int is_stack_empty(stack *s);

void push(stack *s, void * a);

void * pop(stack *s);

void print_cell(cell* c, void (print_func)(void *, char *), FILE * file);

void print_stack(stack s, void (print_func)(void *, char *), FILE * file);

void concat_stack(stack* s1, stack* s2);

stack* copy_stack(stack * s);

void destroy_stack(stack *s);

#endif
