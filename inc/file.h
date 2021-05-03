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

/**
 * @brief Create a Queue object FILO
 * 
 * @return stack* 
 */
queue* create_queue();

/**
 * @brief return whether the queue is empty or not
 * 
 * @param s 
 * @return int 
 */
int is_queue_empty(queue* s);

/**
 * @brief push an element at the beginning of the queue 
 * 
 * @param s 
 * @param a 
 */
void add_queue(queue* s, void* a);

/**
 * @brief pop an element from the end of the queue,
 *  if the queue is empty, return a null element
 * 
 * @param s 
 * @return element 
 */
void* last_queue(queue* s);

/**
 * @brief Print a queue (Use it if the queue is int composed)
 * 
 * @param c 
 * @param buf 
 */
void print_queue_int(int c, char* buf);

void print_queue_cell(queue_cell* c, void(print_func)(void*, char*), FILE* file);

void print_queue(queue* s, void(print_func)(void*, char*), FILE* file);

/**
 * @brief concat the second queue at the end of the first, 
 * not regarding whether there are empty or not
 * 
 * @param s1 
 * @param s2 
 */
void concat_queue(queue* s1, queue* s2);

/**
 * @brief copy a queue into another
 * 
 * @param s 
 * @return queue* 
 */
queue* copy_queue(queue* s);

/**
 * @brief free a queue and all the queue_cell inside
 * 
 * @param s 
 */
void destroy_queue(queue* s);


#endif
