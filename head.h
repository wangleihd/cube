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
    // p(0) = (0,0)
    // p(1) = (0,1)
    // p(2) = (1,1)
    // (0,1) -> bottom 
    // (1,2) -> right  
    // (2,3) -> top   
    // (3,0) -> left 
    point  dot[4];
    int id;
    int row;
    int width;
    int column;
    int floor;
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
 