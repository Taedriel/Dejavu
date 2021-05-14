#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

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

/**
 * @brief Create a Queue object FILO
 * 
 * @return stack* 
 */
list *create_list();

/**
 * @brief return whether the queue is empty or not
 * 
 * @param s 
 * @return int 
 */
int is_list_empty(list *s);

/**
 * @brief add an element in the list at the end 
 * 
 * @param s 
 * @param a 
 */
void add_list(list *s, void *a);

/**
 * @brief remove an object from the list at indice i
 * 
 * @param s 
 * @param indice 
 */
void remove_list(list *s, int indice);

/**
 * @brief get an element from the end of the queue,
 *  if the queue is empty, return a null element
 * 
 * @param s 
 * @return element 
 */
void *get_list(list *s, int i);

void print_list_int(int content, char *buf);

void print_list_cell(list_cell *c, void(print_func)(void *, char *), FILE *file);

void print_list(list *s, void(print_func)(void *, char *), FILE *file);

/**
 * @brief copy a queue into another
 * 
 * @param s 
 * @return queue* 
 */
list *copy_list(list *s);

/**
 * @brief free a queue and all the queue_cell inside
 * 
 * @param s 
 */
void destroy_list(list *s);

void **list_to_tab(list *s);

#endif