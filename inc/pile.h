#ifndef PILE_H
#define PILE_H
#include <stdio.h>
#include <list.h>

typedef struct cell {
    void* x;
    struct cell* next;
} cell;

typedef struct stack {
    cell* head;
    cell* tail;
    int size;
} stack;

/**
 * @brief Create a Stack object
 *
 * @return stack*
 */
stack* create_stack();

/**
 * @brief return whether the stack is empty or not
 *
 * @param s
 * @return int
 */
int is_stack_empty(stack* s);

/**
 * @brief push an element on the stack
 *
 * @param s
 * @param a
 */
void push_stack(stack* s, void* a);

/**
 * @brief pop an element from the stack, if the stack is empty, return a null
 * element
 *
 * @param s
 * @return element
 */
void* pop_stack(stack* s);

void print_cell(cell* c, void(print_func)(void*, char*), FILE* file);

void print_stack(stack s, void(print_func)(void*, char*), FILE* file);

/**
 * @brief concat the second stack at the end of the first,
 * not regarding whether there are empty or not
 *
 * @param s1
 * @param s2
 */
void concat_stack(stack* s1, stack* s2);

/**
 * @brief copy
 *
 * @param s
 * @return stack*
 */
stack* copy_stack(stack* s);

/**
 * @brief free a stack and all the cell inside
 *
 * @param s
 */
void destroy_stack(stack* s);

/**
 * @brief translate a stack into a table
 * 
 * @param s 
 * @return void** 
 */
void** stack_to_tab(stack* s);

/**
 * @brief translate a list into a stack
 * 
 * @param s 
 * @return stack* 
 */
stack *list_to_stack(list* s);

#endif
