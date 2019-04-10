#ifndef __HEAD_H__
#define __HEAD_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
// #include <conio.h>    //window lib


typedef struct point_type
{
    /* data */
    int x, y;
    int id;

}point, *pos;

typedef struct cube
{
    /* data */
    point  dot[4];
    double height;
    int id;
    int floor;
    struct cube *top;
    struct cube *below;
    struct cube *left;
    struct cube *right;
}cubes, *cu;





#endif
