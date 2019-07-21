#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <conio.h>    //window lib

const double pi = 3.1415926;
const int dotleng = 8;
const int K = 2;  //构造折线
const int B1 = 1;
const int K2 = -1;
const int B2 = 136;

typedef struct point_type {
    /* data */
    float x, y, z;
    int id;
} point, *pos;

typedef struct cube {
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

typedef struct camera {
    float x, y;
    int id;
    int select[3];
    struct cube cube;
    struct camera *next;
} ca;

typedef struct point {
    float x;
    float y;
    int id;
    struct point *next;
    struct point *pre;
} poi;

typedef struct npoint {
    int x;
    int y;
    int height;
    int cameraId;
    struct npoint *next;
} n;

typedef struct line {
    float startx, starty;
    float endx, endy;
    float timestamp;
    int id;
    struct line *next;
} l;

typedef struct camerainfo {
    int pos;
    int cameraId;
    int sum;
    float resum;
    int isdelete;
    int lines[600];
    int reline[600];
    struct camerainfo *next;
} cii;

struct lineinfo {
    int lineId;
    int cameraId[600];
    int isdelete;
    int isCoverage;
    struct lineinfo *next;
};

struct retcam {
    int pos;
    int cameraId;
    int sum;
    int lines[600];
    int lineId;
    struct retcam *next;
};

#endif
