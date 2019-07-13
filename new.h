#ifndef __NEW_H__
#define __NEW_H__
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct camera {
    int x;
    int y;
    int h;
    int id;
    int pos;
    int sum;
    int resum;
    int lineId;
    int cameraId;
    int isdelete;
    int lines[100];
    int reline[100];
    struct camera * next;
    struct camera * pre;
} c;

typedef struct point {
    float x;
    float y;
    int id;
    struct point *next;
    struct point *pre;
} p;

typedef struct line {
    float startx, starty;
    float endx, endy;
    float timestamp;
    int id;
    struct line *next;
} l;


#endif