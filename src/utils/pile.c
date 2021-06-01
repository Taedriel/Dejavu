#include "pile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

stack *create_stack() {
    stack *s;
    s = malloc(sizeof(stack));
    s->head = 0;
    s->tail = 0;
    s->size = 0;

    return s;
}

int is_stack_empty(stack *s) { return s->size == 0; }

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

void concat_stack(stack *s1, stack *s2) {
    if (is_stack_empty(s1)) {
        s1->head = s2->head;
        s1->tail = s2->tail;
        return;
    }

    if (!is_stack_empty(s2)) {
        s1->tail->next = s2->head;
        s1->tail = s2->tail;
    }
}


stack *copy_stack(stack *s) {
    stack *copy;
    cell *p = s->head;

    copy = malloc(sizeof(stack));

    if (is_stack_empty(s)) {
        return copy;
    }

    while (p != NULL) {
        push_stack(copy, p->x);
        p = (cell *)(p->next);
    }
    return copy;
}

void destroy_stack(stack *s) {
    while (s->head != NULL) {
        pop_stack(s);
    }
    free(s);
}

void **stack_to_tab(stack *s) {
    int i = 0;
    void **ret = malloc(sizeof(void *) * s->size + 1);

    cell *temp = s->head;
    while (temp != NULL) {
        ret[i] = temp->x;
        i++;
        temp = temp->next;
    }

    return ret;
}

stack *list_to_stack(list *s) {
    stack *new_stack = create_stack();
    int i;
    for (i = s->size - 1 ; i >= 0  ; i--) {
        push_stack(new_stack, get_list(s, i));
    }
    return new_stack;
}

list *stack_to_list(stack *stack) {
    int i;
    int maxsize = stack->size;
    list *ret = create_list();

    for (i = 0; i < maxsize; i++) {
        add_list(ret, pop_stack(stack));
    }

    return ret;
}
