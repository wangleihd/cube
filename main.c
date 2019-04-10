#include "head.h"

const int max_side = 100;
const int min_side = 10;

int min_cube_init();
int cube_init(struct cube *);

int main(void) {
    min_cube_init();

    
    return 0;
}

int min_cube_init(){
    int i, k;
    struct cube head, *p;
    cube_init(&head);
    for(i = 0; i < 100/10; i++){
        for(k = 0; k < 100/10; k++){
            p = malloc(sizeof(struct cube));
            head.left = p;
            

        }
    }
}

int cube_init(struct cube * p) {
    p->top = NULL;
    p->below = NULL;
    p->left = NULL;
    p->id = 0;
    p->floor = 0;
}