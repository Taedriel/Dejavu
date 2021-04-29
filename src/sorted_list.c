#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorted_list.h"

/**
 * @brief Create a Queue object FILO
 * 
 * @return stack* 
 */
sorted_list *create_sorted_list() {
    sorted_list *s;
    s = malloc(sizeof(sorted_list));
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
int is_sorted_list_empty(sorted_list *s) {
    return s->size == 0;
}

/**
 * @brief add an element in the ordered list keeping the list ordered 
 * 
 * @param s 
 * @param a 
 */
void add_sorted_list(sorted_list *s, void *a, float score) {
    sorted_list_cell * temp;
    sorted_list_cell * c = malloc(sizeof(sorted_list_cell));

    c->x = a;
    c->next = 0;
    c->prev = 0;
    c->score = score;

    if (is_sorted_list_empty(s)) {
        s->tail = c;
        s->head = c;
    } else {
        temp = s->head;
        /*
        fprintf(stderr, "%p --> %p\n",(void *) s->head, (void *) s->tail);
        */
        while (temp != s->tail) {
            /*
            fprintf(stderr, "!= %p\n", (void *) temp);
            */
            if (score < temp->score){
                break;
            }

            temp = temp->next;
        }
        /*
        fprintf(stderr, "end == %p (%f)\n", (void *) temp, score);
        */

        if (temp == s->tail && score > temp->score) {
            temp->next = c;
            c->prev = temp;
            s->tail = c;
        } else if (temp == s->head && score < temp->score){
            temp->prev = c;
            c->next = temp;
            s->head = c;
        } else {
            temp->prev->next = c;
            c->prev = temp->prev;
            c->next = temp;
            temp->prev = c;
        }
    }
    s->size++;
}

/**
 * @brief remove an object from the list at indice i
 * 
 * @param s 
 * @param indice 
 */
void remove_sorted_list(sorted_list *s, int indice) {
    sorted_list_cell * temp;
    int cpt;

    if (!is_sorted_list_empty(s) && indice < s->size){
        if (indice < 0)
            indice = s->size - indice;

        temp = s->head;
        cpt = 0;
        while (cpt != indice){
            cpt ++;
            temp = temp->next;
        }
        if (temp == s->head){
            s->head = temp->next;
        } else if (temp == s->tail) {
            temp->prev->next = temp->next;
        } else {
            s->tail = temp->prev;
        }
        s->size--;
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
void *get_sorted_list(sorted_list *s, int i, float * cout) {
    sorted_list_cell *temp;
    int cpt; 

    if (is_sorted_list_empty(s)) {
        return NULL;
    }

    if (i >= s->size) {
        return NULL;
    }

    cpt = 0;
    temp = s->head;
    while (cpt != i){
        cpt ++;
        temp = temp->next;
    }

    *cout = temp->score;
    return temp->x;
}
void print_sorted_list_int(int content, char *buf) {
    sprintf(buf, "%d", content);
}

void print_sorted_list_cell(sorted_list_cell *c, void(print_func)(void *, char *), FILE *file) {
    char *rep = malloc(sizeof(char) * 1024);
    print_func(c->x, rep);
    fprintf(file, "| %s :%f|", rep, c->score);
    free(rep);
}

void print_sorted_list(sorted_list *s, void(print_func)(void *, char *), FILE *file) {
    sorted_list_cell *p = s->head;
    if (is_sorted_list_empty(s)) {
        fprintf(file, "Queue is Empty");
        return;
    }

    fprintf(file, "[");
    while (p != NULL) {
        print_sorted_list_cell(p, print_func, file);
        p = (sorted_list_cell *)(p->next);
    }
    fprintf(file, "] = %d\n", s->size);
}

/**
 * @brief copy a queue into another
 * 
 * @param s 
 * @return queue* 
 */
sorted_list *copy_sorted_list(sorted_list *s) {
    sorted_list *copy;
    sorted_list_cell *p = s->tail;

    copy = malloc(sizeof(sorted_list));

    if (is_sorted_list_empty(s)) {
        return copy;
    }

    while (p != NULL) {
        add_sorted_list(copy, p->x, p->score);
        p = (sorted_list_cell *)(p->prev);
    }
    return copy;
}

/**
 * @brief free a queue and all the queue_cell inside
 * 
 * @param s 
 */
void destroy_sorted_list(sorted_list *s) {
    while (s->size != 0) {
        remove_sorted_list(s, 0);
    }
    free(s);
}
