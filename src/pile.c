#include "pile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * @brief Create a Stack object
 *
 * @return stack*
 */
stack *create_stack() {
    stack *s;
    s = malloc(sizeof(stack));
    s->head = 0;
    s->tail = 0;
    s->size = 0;

    return s;
}

/**
 * @brief return whether the stack is empty or not
 *
 * @param s
 * @return int
 */
int is_stack_empty(stack *s) { return s->size == 0; }

/**
 * @brief push an element on the stack
 *
 * @param s
 * @param a
 */
void push_stack(stack *s, void *a) {
    cell *c;
    c = malloc(sizeof(cell));
    c->x = a;
    c->next = 0;

    if (is_stack_empty(s)) {
        s->head = c;
    } else {
        s->tail->next = c;
    }
    s->tail = c;
    s->size++;
}

/**
 * @brief pop an element from the stack, if the stack is empty, return a null
 * element
 *
 * @param s
 * @return element
 */
void *pop_stack(stack *s) {
    if (is_stack_empty(s)) {
        return NULL;
    }

    cell *temp = s->head;
    void *v;

    v = temp->x;
    s->head = (cell *)(s->head->next);
    s->size--;
    free(temp);

    return v;
}

void print_cell(cell *c, void(print_func)(void *, char *), FILE *file) {
    char *rep = malloc(sizeof(char) * 1024);
    print_func(c->x, rep);
    fprintf(file, "| %s |", rep);
    free(rep);
}

void print_stack(stack s, void(print_func)(void *, char *), FILE *file) {
    cell *p = s.head;
    if (p == NULL) {
        fprintf(file, "Stack is Empty");
    }

    fprintf(file, "[");
    while (p != NULL) {
        print_cell(p, print_func, file);
        p = (cell *)(p->next);
    }
    fprintf(file, "]\n");
}

/**
 * @brief concat the second stack at the end of the first,
 * not regarding whether there are empty or not
 *
 * @param s1
 * @param s2
 */
void concat_stack(stack *s1, stack *s2) {
    if (is_stack_empty(s1)) {
        /* swap s1 and s2 */
        s1->head = s2->head;
        s1->tail = s2->tail;
        return;
    }

    if (!is_stack_empty(s2)) {
        s1->tail->next = s2->head;
        s1->tail = s2->tail;
    }
}

/**
 * @brief copy
 *
 * @param s
 * @return stack*
 */
stack *copy_stack(stack *s) {
    stack *copy;
    cell *p = s->head;

    copy = malloc(sizeof(stack));

    if (is_stack_empty(s)) {
        return copy;
    }

    while (p != NULL) {
        push(copy, p->x);
        p = (cell *)(p->next);
    }
    return copy;
}

/**
 * @brief free a stack and all the cell inside
 *
 * @param s
 */
void destroy_stack(stack *s) {
    while (s->head != NULL) {
        pop(s);
    }
    free(s);
}