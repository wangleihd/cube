#include "head.h"

const int max_side = 100;
const int min_side = 10;
const double pi = 3.1415926;

void min_cube_init(struct cube *);
void cube_init ( struct cube * cube);
void cube_dot ( struct cube * cube );
void cube_link ( struct cube * head, struct cube * cube);
void result_out ( struct cube * head );
void curve_x (double * result, int step);
void curve_y (double * res, int step);

void cube_search(struct cube *, float * , int, struct dot_in_cube *);

int main(void) {
    struct cube head;
    struct dot_in_cube result;
    float dot_x[] = {21, 41, 61, 81, 101, 121, 141, 161, 181, 201};
    float dot_y[] = {4.5, 9.5, 14.5, 19.5, 24.5, 29.5, 34.5, 44.5, 49.5};
    int len = 10;
    min_cube_init(&head);

    result_out( &head );
    cube_search( &head, dot_x, len, &result);
    return 0;
}

void min_cube_init(struct cube * head){
    int i, k;
    struct cube *p;
    int num = 0;
    double res[12] = {0};

    cube_init( head );
    // printf("head.id=%d\n", head.id);
    for(i = 0; i < 100/10; i++){
        for(k = 0; k < 100/10; k++){
            num += 1;
            p = malloc( sizeof( struct cube ) );
            cube_init( p );
            head->left = p;
            p->id = num;
            p->floor = 0;
            p->row = i + 1;
            p->column = k + 1;
            p->height = min_side;
            cube_dot( p );
            cube_link( head, p);
        }
    }
}

void cube_init( struct cube * p ) {
    p->top = NULL;
    p->left = NULL;
    p->bottom = NULL;
    p->right = NULL;
    p->id = 0;
    p->floor = 0;
    p->height = 0;
    p->row = 0;
    p->column = 0;
}



void cube_dot( struct cube * c ) {
    int i = 0;
    int side_lenght = c->height;
    int row = c->row;
    int column = c->column;

    for ( ; i < 4; i++) {
        c->dot[i].id = i;
        if (i == 0) {
        c->dot[i].x = (row - 1) * side_lenght;
        c->dot[i].y = (column - 1) * side_lenght;
        }
        if (i == 1) {
        c->dot[i].x = row * side_lenght;
        c->dot[i].y = (column - 1) * side_lenght;
        }
        if (i == 2) {
        c->dot[i].x = row * side_lenght;
        c->dot[i].y = column * side_lenght;
        }
        if (i == 3) {
        c->dot[i].x = (row - 1) * side_lenght;
        c->dot[i].y = column * side_lenght;
        }
    }
}

void cube_link( struct cube * h, struct cube * p ) {
    struct cube *tmpright = h;
    struct cube *tmptop = h->right;
    int i = 0;
    int dot = 0;
    while ( tmpright->right ) {
        tmpright = tmpright->right;
        if(0 == (tmpright->column % min_side)) {
            if(tmptop->top) {
                tmpright = tmptop->top;
                tmptop = tmptop->top;
            } else {
                dot = 1;
                tmpright = tmptop;
                break;
            }
        }
    }
        if(dot == 1) {
            tmpright->top = p;
            p->bottom = tmpright;
        } else {
            tmpright->right = p;
            p->left = tmpright;
        if(tmpright->row > 1) {
                tmpright->bottom->right->top = p;
                p->bottom = tmpright->bottom->right;
        }
        }
}

void result_out ( struct cube *m ) {
    struct cube * h = m->right;
    struct cube * row = m->right->top;

    while (h) {
        printf("column: %d", h->column);
        if(!(h->column % min_side)) {
            printf("\n\nid = %d\t floot = %d\t row = %d\t column = %d\t height = %d\n", h -> id, h -> floor, h -> row, h -> column, h -> height);
            for (int i = 0; i < 4; i++) {
                printf("dot->id = %d\t (x, y) =  (%d, %d)\n", h->dot[i].id, h->dot[i].x, h->dot[i].y);
            }
            if(!row){
                return;
            } else {
                h = row;
                row = row->top;
            }
        }
        printf("\n\nid = %d\t floot = %d\t row = %d\t column = %d\t height = %d\n", h -> id, h -> floor, h -> row, h -> column, h -> height);
        for (int i = 0; i < 4; i++) {
            printf("dot->id = %d\t (x, y) =  (%d, %d)\n", h->dot[i].id, h->dot[i].x, h->dot[i].y);
        }
        h = h->right;
    }
}


void curve_x (double * result, int step) {
    for (int x = 0, i = 0; x <= max_side; x += step, i++) {
        double y = sin(x * pi / 180) + 1;
        result[i] = y;
    }
}

void curve_y (double * res, int step) {
    for(int y = 0; y <= max_side; y += step){
        // double y = sin(x * PI/180) +1;
        double x = asin(y % 10);
            printf("y = %d, x = %f\n", y, x);
    }
}

void cube_search(struct cube * head, float * coordinate, int len, struct dot_in_cube * res) {
    int i = 1;
    for(; i <= len; i++) {
        printf("(x,y): (%d, %f)\n", i*10, *coordinate);
        coordinate ++;

    }
}



