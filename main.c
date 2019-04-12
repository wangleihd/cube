#include "head.h"

const int max_side = 100;
const int min_side = 10;

void min_cube_init();
void cube_init ( struct cube * cube);
void cube_dot ( struct cube * cube );
void cube_link ( struct cube * head, struct cube * cube);

int main(void) {
    min_cube_init();
    return 0;
}

void min_cube_init(){
    int i, k;
    struct cube head, *p;
    int num = 0;
    cube_init( &head );
    printf("head.id=%d\n", head.id);
    for(i = 0; i < 100/10; i++){
        for(k = 0; k < 100/10; k++){
            num += 1;
            p = malloc( sizeof( struct cube ) );
            cube_init( p );
            head.left = p;
            p->id = num;
            p->floor = 0;
            p->row = k + 1;
            p->column = i + 1;
            p->height = min_side;
            printf("\nid = %d\t floot = %d\t row = %d\t column = %d\t height = %d\n", p -> id, p -> floor, p -> row, p -> column, p -> height);
            cube_dot( p );
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
        printf("dot->id = %d\t (x, y) =  (%d, %d)\n", c->dot[i].id, c->dot[i].x, c->dot[i].y);
    }
}

void cube_link( struct cube * h, struct cube * p ) {


}

