#ifndef SORTED_LIST_H
#define SORTTED_LIST_H

typedef struct sorted_list_cell {
    void *x;
    struct sorted_list_cell *next;
    struct sorted_list_cell *prev;
    float score;

} sorted_list_cell;

typedef struct sorted_list {
    sorted_list_cell *head;
    sorted_list_cell *tail;
    int size;

} sorted_list;

sorted_list *create_sorted_list();

int is_sorted_list_empty(sorted_list *s);

void add_sorted_list(sorted_list *s, void *a, float score);

void remove_sorted_list(sorted_list *s, int indice);

void *get_sorted_list(sorted_list *s, int i, float * score);

void print_sorted_list_int(int content, char *buf);

void print_sorted_list_cell(sorted_list_cell *c, void(print_func)(void *, char *), FILE *file);

void print_sorted_list(sorted_list *s, void(print_func)(void *, char *), FILE *file);

sorted_list *copy_sorted_list(sorted_list *s);

void destroy_sorted_list(sorted_list *s);

#endif