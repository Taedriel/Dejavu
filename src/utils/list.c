#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list *create_list() {
    list *s;
    s = malloc(sizeof(list));
    s->head = 0;
    s->tail = 0;
    s->size = 0;

    return s;
}

int is_list_empty(list *s) {
    return s->size == 0;
}

void add_list(list *s, void *a) {
    list_cell *c = malloc(sizeof(list_cell));

    c->x = a;
    c->next = 0;
    c->prev = 0;

    if (is_list_empty(s)) {
        s->head = c;
    } else {
        c->prev = s->tail;
        s->tail->next = c;
    }
    s->tail = c;
    s->size++;
}

void remove_list(list *s, int indice) {
    list_cell *temp;
    int cpt;
    if (!is_list_empty(s) && indice < abs(s->size)) {
        if (indice < 0)
            indice = s->size - indice;
        temp = s->head;
        cpt = 0;
        while (cpt != indice) {
            cpt++;
            temp = temp->next;
        }
        if (temp == s->head) {
            s->head = temp->next;
            temp->next = 0;
        } else if (temp == s->tail) {
            s->tail = temp->prev;
            temp->prev->next = 0;
        } else {
            temp->prev->next = temp->next;
        }
        free(temp);
    }
    s->size--;
}

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

void destroy_list(list *s) {
    while (s->size > 1) {
        remove_list(s, 0);
    }
    free(s);
}

void **list_to_tab(list *s) {
    int i = 0;
    void **ret = malloc(sizeof(void *) * s->size + 1);
    list_cell *temp = s->head;
    while (temp != NULL) {
        ret[i] = temp->x;
        i++;
        temp = temp->next;
    }

    return ret;
}

list * create_list_from_obj(void * o) {
    list * ret = create_list();
    add_list(ret, o);
    return ret;
}

list * tab_to_list(void ** elems, int size_tabs) {

    int i;
    list * ret = create_list();

    for(i = 0; i < size_tabs; i++) {
        add_list(ret, elems[i]);
    }

    return ret;

}
