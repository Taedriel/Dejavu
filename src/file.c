#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Create a Queue object FILO
 * 
 * @return stack* 
 */
queue *create_queue() {
    queue *s;
    s = malloc(sizeof(queue));
    s->head = 0;
    s->tail = 0;
    s->size = 0;

    return s;
}

/**
 * @brief return whether the queue is empty or not
 * 
 * @param s 
 * @return int 
 */
int is_queue_empty(queue *s) {
    return s->size == 0;
}

/**
 * @brief push an element at the beginning of the queue 
 * 
 * @param s 
 * @param a 
 */
void add_queue(queue *s, void *a) {
    queue_cell *c = malloc(sizeof(queue_cell));
    c->x = a;
    c->next = 0;
    c->prev = 0;

    if (is_queue_empty(s)) {
        s->tail = c;
    } else {
        c->next = s->head;
        c->next->prev = c;
    }
    s->head = c;
    s->size++;
}

/**
 * @brief pop an element from the end of the queue,
 *  if the queue is empty, return a null element
 * 
 * @param s 
 * @return element 
 */
void *last_queue(queue *s) {
    queue_cell *temp;
    void *v;

    if (is_queue_empty(s)) {
        return NULL;
    }
    temp = s->tail;
    v = temp->x;

    s->tail = (queue_cell *)(s->tail->prev);
    s->size--;
    free(temp);

    if (is_queue_empty(s)) {
        s->head = NULL;
        s->tail = NULL;
    }

    return v;
}
void print_queue_int(int content, char *buf) {
    sprintf(buf, "%d", content);
}

void print_queue_cell(queue_cell *c, void(print_func)(void *, char *), FILE *file) {
    char *rep = malloc(sizeof(char) * 1024);
    print_func(c->x, rep);
    fprintf(file, "| %s |", rep);
    free(rep);
}

void print_queue(queue *s, void(print_func)(void *, char *), FILE *file) {
    queue_cell *p = s->head;
    if (is_queue_empty(s)) {
        fprintf(file, "Queue is Empty");
        return;
    }

    fprintf(file, "[");
    while (p != NULL) {
        print_queue_cell(p, print_func, file);
        p = (queue_cell *)(p->next);
    }
    fprintf(file, "] = %d\n", s->size);
}

/**
 * @brief concat the second queue at the end of the first, 
 * not regarding whether there are empty or not
 * 
 * @param s1 
 * @param s2 
 */
void concat_queue(queue *s1, queue *s2) {
    if (is_queue_empty(s1)) {
        /* swap s1 and s2 */
        s1->head = s2->head;
        s1->tail = s2->tail;
        return;
    }

    if (!is_queue_empty(s2)) {
        s1->tail->next = s2->head;
        s1->tail = s2->tail;
    }
}

/**
 * @brief copy a queue into another
 * 
 * @param s 
 * @return queue* 
 */
queue *copy_queue(queue *s) {
    queue *copy;
    queue_cell *p = s->tail;

    copy = malloc(sizeof(queue));

    if (is_queue_empty(s)) {
        return copy;
    }

    while (p != NULL) {
        add_queue(copy, p->x);
        p = (queue_cell *)(p->prev);
    }
    return copy;
}

/**
 * @brief free a queue and all the queue_cell inside
 * 
 * @param s 
 */
void destroy_queue(queue *s) {
    while (s->head != NULL) {
        last_queue(s);
    }
    free(s);
}
