#include "head.h"

const int max_side = 100;
const int min_side = 10;
const double PI = 3.1415926;

void min_cube_init();
void cube_init ( struct cube * cube);
void cube_dot ( struct cube * cube );
void cube_link ( struct cube * head, struct cube * cube);
void result_out ( struct cube * head );
void curve_x (double * result, int step);
void curve_y (double * res, int step);

int main(void) {
    min_cube_init();
    return 0;
}

void min_cube_init(){
    int i, k;
    struct cube head, *p;
    int num = 0;
    double res[12] = {0};

    cube_init(&head);
    // printf("head.id=%d\n", head.id);
    for(i = 0; i < 100/10; i++){
        for(k = 0; k < 100/10; k++){
            num += 1;
            p = malloc( sizeof( struct cube ) );
            cube_init( p );
            head.left = p;
            p->id = num;
            p->floor = 0;
            p->row = i + 1;
            p->column = k + 1;
            p->height = min_side;
            cube_dot( p );
            cube_link( &head, p);
        }
    }
    result_out( &head);
    // curve_x(res, min_side);
    // curve_y (res, min_side);
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
    struct cube *tmptop = h;
    int i = 0;
    int dot = 0;
    while ( tmpright->right ) {
        tmpright = tmpright->right;
        if(!(p->column % min_side))
         {
            tmpright = tmptop;
            tmptop = tmptop->top;
            printf("i %d %d\n", i, tmptop, p->column);
            if(tmptop) {
                dot = 0;
            } else {
                dot = 1;
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
        // if(tmpright->column > 0) {
        //         tmpright->bottom->right->top = p;
        //         p->bottom = tmpright->bottom->right;
        // }
        }

}

void result_out ( struct cube *m ) {
    struct cube * h = m->right;
    struct cube * row = m->top;

    while (h) {
        printf("column: %d", h->column);
        if(!(h->column % min_side)) {
            h = row;
            row = row->top;
            printf("\n\ncoumn[%d] = %d\t\n", h->id, h->column);
        }
        printf("\nid = %d\t floot = %d\t row = %d\t column = %d\t height = %d\n", h -> id, h -> floor, h -> row, h -> column, h -> height);
        for (int i = 0; i < 4; i++) {
            printf("dot->id = %d\t (x, y) =  (%d, %d)\n", h->dot[i].id, h->dot[i].x, h->dot[i].y);
        }
        h = h->right;
    }
}


void curve_x (double * result, int step) {

    for (int x = 0, i = 0; x <= max_side; x += step, i++) {
        double y = sin(x * PI / 180) + 1;
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
