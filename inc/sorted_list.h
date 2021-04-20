#ifndef SORTED_LIST_H
#define SORTTED_LIST_H

typedef struct sorted_list_cell {
    void* x;
    struct sorted_list_cell * next;
    struct sorted_list_cell * prev;
    float score;

} sorted_list_cell;

typedef struct sorted_list {
    sorted_list_cell* head;
    sorted_list_cell* tail;
    int size;

} sorted_list;

#endif