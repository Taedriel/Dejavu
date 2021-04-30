#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct list_cell {
    void *x;
    struct list_cell *next;
    struct list_cell *prev;
    float score;

} list_cell;

typedef struct list {
    list_cell *head;
    list_cell *tail;
    int size;

} list;

list *create_list();

int is_list_empty(list *s);

void add_list(list *s, void *a);

void remove_list(list *s, int indice);

void *get_list(list *s, int i);

void print_list_int(int content, char *buf);

void print_list_cell(list_cell *c, void(print_func)(void *, char *), FILE *file);

void print_list(list *s, void(print_func)(void *, char *), FILE *file);

list *copy_list(list *s);

void destroy_list(list *s);

void ** list_to_tab (list *s);

#endif