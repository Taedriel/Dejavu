#ifndef H_UTILS_INCLUDED
#define H_UTILS_INCLUDED

#include "racing_types.h"

void print_tuple(void * t, char * rep);

tuple_int * copy_tuple_int(tuple_int o);

tuple_int * create_tuple_int(int a, int b);


int max(int a, int b);

int min(int a, int b);



#endif