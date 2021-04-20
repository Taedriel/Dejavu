#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct queue_cell {
    void* x;
    struct queue_cell* next;
    struct queue_cell* prev;

} queue_cell;

typedef struct queue {
    queue_cell* head;
    queue_cell* tail;
    int size;
} queue;

queue* create_queue();

int is_queue_empty(queue* s);

void add(queue* s, void* a);

void* last(queue* s);

void print_queue_cell(queue_cell* c, void(print_func)(void*, char*), FILE* file);

void print_queue(queue* s, void(print_func)(void*, char*), FILE* file);

void concat_queue(queue* s1, queue* s2);

queue* copy_queue(queue* s);

void destroy_queue(queue* s);

void print_queue_int(int c, char* buf);

#endif
