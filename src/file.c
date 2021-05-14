#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

queue *create_queue() {
    queue *s;
    
    s = malloc(sizeof(queue));
    s->head = 0;
    s->tail = 0;
    s->size = 0;

    return s;
}

int is_queue_empty(queue *s) {
    return s->size == 0;
}

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

void destroy_queue(queue *s) {
    while (s->head != NULL) {
        last_queue(s);
    }
    free(s);
}
