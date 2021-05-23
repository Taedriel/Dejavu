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

/**
 * @brief Create a Queue object FILO
 * 
 * @return stack* 
 */
sorted_list *create_sorted_list();

/**
 * @brief return whether the queue is empty or not
 * 
 * @param s 
 * @return int 
 */
int is_sorted_list_empty(sorted_list *s);

/**
 * @brief add an element in the ordered list keeping the list ordered 
 * 
 * @param s 
 * @param a 
 */
void add_sorted_list(sorted_list *s, void *a, float score);

/**
 * @brief remove an object from the list at indice i
 * 
 * @param s 
 * @param indice 
 */
void remove_sorted_list(sorted_list *s, int indice);

/**
 * @brief get an element from the end of the queue,
 *  if the queue is empty, return a null element
 * 
 * @param s 
 * @return element 
 */
void *get_sorted_list(sorted_list *s, int i, float * score);

void print_sorted_list_int(int content, char *buf);

void print_sorted_list_cell(sorted_list_cell *c, void(print_func)(void *, char *), FILE *file);

void print_sorted_list(sorted_list *s, void(print_func)(void *, char *), FILE *file);

/**
 * @brief copy a queue into another
 * 
 * @param s 
 * @return queue* 
 */
sorted_list *copy_sorted_list(sorted_list *s);

/**
 * @brief free a queue and all the queue_cell inside
 * 
 * @param s 
 */
void destroy_sorted_list(sorted_list *s);

#endif