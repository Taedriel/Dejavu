#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorted_list.h"

sorted_list *create_sorted_list() {
    sorted_list *s;
    s = malloc(sizeof(sorted_list));
    s->head = 0;
    s->tail = 0;
    s->size = 0;

    return s;
}

int is_sorted_list_empty(sorted_list *s) {
    return s->size == 0;
}

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
    } else if (s->size == 1) {
        if (score > s->head->score){
            s->head->next = c;
            c->prev = s->head;
            s->tail = c;
        }else {
            s->tail->prev = c;
            c->next = s->tail;
            s->head = c;
        }
    } else {
        temp = s->head;        
        while (temp != s->tail) {            
            if (score < temp->score){
                break;
            }

            temp = temp->next;
        }
        if (temp == s->head && score < temp->score) {
            //insertion au debut
            s->head->prev = c;
            c->next = s->head;
            s->head = c;
        } else if (temp == s->tail && score > temp->score) {
            //insertion a la fin
            s->tail->next = c;
            c->prev = s->tail;
            s->tail = c;
        } else {
            //insertion entre deux, temp est à droite
            //temp-1 -> temp -> temp+1
            //insertion entre temp-1 et temp
            temp->prev->next = c;
            c->prev = temp->prev;
            c->next = temp;
            temp->prev = c;
        }
        }
    s->size++;
}

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

void destroy_sorted_list(sorted_list *s) {
    while (s->size != 0) {
        remove_sorted_list(s, 0);
    }
    free(s);
}
