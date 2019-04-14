#ifndef __HEAD_H__
#define __HEAD_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
// #include <conio.h>    //window lib

typedef struct point_type {
    /* data */
    int x, y;
    int id;
}point, *pos;

typedef struct cube {
    /* data */
    // (0,1) -> bottom point (0)
    // (1,2) -> right  point (1)
    // (2,3) -> top    point (2)
    // (3,0) -> left   point (3)
    point  dot[4];
    int id;
    int floor;
    int row;
    int column;
    int width;
    int height;
    struct cube *top;
    struct cube *bottom;
    struct cube *left;
    struct cube *right;
}cubes, *cu;

typedef struct dot_in_cube {
    float x;
    float y;
    struct cube *top;
    struct cube *bottom;
    struct cube *left;
    struct cube *right;
}dots, *dot;



#endif
