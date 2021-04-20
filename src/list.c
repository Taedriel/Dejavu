#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * @brief Create a Queue object FILO
 * 
 * @return stack* 
 */
list * create_list() {
    list *s;
    s = malloc(sizeof(list));
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
int is_list_empty(list *s) {
    return s->size == 0;
}

/**
 * @brief add an element in the list at the end 
 * 
 * @param s 
 * @param a 
 */
void add_list(list *s, void *a) {
    list_cell *temp;
    list_cell *c = malloc(sizeof(list_cell));

    c->x = a;
    c->next = 0;
    c->prev = 0;

    if (is_list_empty(s)) {
        s->tail = c;
        s->head = c;
    } else {
        c->prev = s->tail;
        s->tail->next = c;
        s->tail = c;
    }
    s->size++;
}

/**
 * @brief remove an object from the list at indice i
 * 
 * @param s 
 * @param indice 
 */
void remove_list(list *s, int indice) {
    list_cell *temp;
    int cpt;

    if (!is_list_empty(s) && indice < s->size) {
        if (indice < 0)
            indice = s->size - indice;

        temp = s->head;
        cpt = 0;
        while (cpt != indice) {
            cpt++;
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        free(temp);
    }
}

/**
 * @brief get an element from the end of the queue,
 *  if the queue is empty, return a null element
 * 
 * @param s 
 * @return element 
 */
void *get_list(list *s, int i) {
    list_cell *temp;
    int cpt;

    if (is_list_empty(s)) {
        return NULL;
    }

    if (i >= s->size) {
        return NULL;
    }

    cpt = 0;
    temp = s->head;
    while (cpt != i) {
        cpt++;
        temp = temp->next;
    }

    return temp->x;
}
void print_list_int(int content, char *buf) {
    sprintf(buf, "%d", content);
}

void print_list_cell(list_cell *c, void(print_func)(void *, char *), FILE *file) {
    char *rep = malloc(sizeof(char) * 1024);
    print_func(c->x, rep);
    fprintf(file, "| %s |", rep);
    free(rep);
}

void print_list(list *s, void(print_func)(void *, char *), FILE *file) {
    list_cell *p = s->head;
    if (is_list_empty(s)) {
        fprintf(file, "Queue is Empty");
        return;
    }

    fprintf(file, "[");
    while (p != NULL) {
        print_list_cell(p, print_func, file);
        p = (list_cell *)(p->next);
    }
    fprintf(file, "] = %d\n", s->size);
}

/**
 * @brief copy a queue into another
 * 
 * @param s 
 * @return queue* 
 */
list *copy_list(list *s) {
    list *copy;
    list_cell *p = s->tail;

    copy = malloc(sizeof(list));

    if (is_list_empty(s)) {
        return copy;
    }

    while (p != NULL) {
        add_list(copy, p->x);
        p = (list_cell *)(p->prev);
    }
    return copy;
}

/**
 * @brief free a queue and all the queue_cell inside
 * 
 * @param s 
 */
void destroy_list(list *s) {
    while (s->size != 0) {
        remove_list(s, 0);
    }
    free(s);
}
