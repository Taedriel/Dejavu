#ifndef H_RACING_TYPES_INCLUDED
#define H_RACING_TYPES_INCLUDED

struct car
{
    int gasLevel;
    int boosts;
    int accelerationX;
    int accelerationY;
    int speedX;
    int speedY;
};

struct map
{
    int width;
    int height;
    int **array;
};


#endif