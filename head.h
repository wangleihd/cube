#ifndef __HEAD_H__
#define __HEAD_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
// #include <conio.h>    //window lib
const int CMAX = 100;

typedef struct point_type
{
    /* data */
    float x, y, z;
    int id;
} point, *pos;

typedef struct cube
{
    /* data */
    // p(0) = (0,0)
    // p(1) = (0,1)
    // p(2) = (1,1)
    // (0,1) -> bottom
    // (1,2) -> right
    // (2,3) -> top
    // (3,0) -> left
    point dot[8];
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
} cubes, *cu;

typedef struct dot_in_cube
{
    float x;
    float y;
    struct cube *top;
    struct cube *bottom;
    struct cube *left;
    struct cube *right;
} dots, *dot;

typedef struct camera
{
    float x, y;
    int id;
    int select[3];
    int point[3][4];
    struct camera *next;
} ca;

typedef struct camerainfo
{
    struct camera ca;
    int pos;
} ci;

typedef struct point
{
    float x;
    float y;
    int total;
    struct camerainfo cinfo[CMAX];
} poi;

#endif
