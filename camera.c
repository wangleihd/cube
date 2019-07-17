
#include "camera.h"

// 摄像头的个数
#define X 10      // 每行摄像头的数量
#define Y 10      // 每列摄像头的数量
#define X_WIDTH 5 // 每行相邻摄像头的间距
#define Y_WIDTH 5 // 每列相邻摄像头的间距
#define H 3       // 摄像头水平高度


const int max_side = 100;
const float min_side = 5;
const float max = 20;

const int max_side_x = 100;
const int max_side_y = 100;
const int min_side_x = 5;
const int min_side_y = 5;
const int height = 20;             //max_side_x / min_side_x;

struct point pitem[100];
int p_total = 0;

void cube_create(struct cube *);
void cube_init(struct cube *cube);
void cube_dot(struct cube *cube);
void cube_link(struct cube *head, struct cube *cube);
void result_out(struct cube *head);
int newpoint(struct npoint *nh);
void newpoint_out(struct npoint *nh);
void point_create(struct point *po);
void point_init(struct point *po);
void point_sort(struct point *ph);
void point_sort1(struct point *ph);
void point_delete(struct point *ph);
void insert_sort(struct point *ph);
void point_out(struct point *);
void line_init(struct line *);
void line_create(struct line *lh, struct point *ph);
void line_out(struct line *lh);
float distance(struct point *p, struct point *q);
int line(struct npoint *head, struct line *lp, struct camerainfo *ci,
         struct lineinfo *li);
int lineincircle(float x, float y, float x0, float y0, float h);

int lineinOval(float x, float y, float x0, float y0, float h, int flag);

void save_init(struct camerainfo *ctmp);
void save_init_line(struct lineinfo *ltmp);
void save(struct npoint *head, struct line *lp, struct camerainfo *ci,
          struct lineinfo *li, int pos);
void resum(struct camerainfo *ch, struct camerainfo *newch);
void save_out(struct camerainfo *ch);

void algorithm_one(struct camerainfo *ch, struct camerainfo *reh,
                   struct line *l);
void one_out(struct camerainfo *reh, struct line *l);
void two_out(struct camerainfo *reh, struct line *l);

void algorithm_two(struct camerainfo *ch, struct camerainfo *reh,
                   struct line *l);

void grid_init(struct point *t);
void line_lengthSum(struct line *lh);

int main(void) {
    struct cube head;
    struct point ph;
    struct line lh;
    struct camerainfo ch, tch, newch;
    struct lineinfo lih;
    struct npoint nh;
    struct camerainfo one, two;

    int i;
    int id = 1;
    int len = 10;
    // cube_create(&head);  // A network of layers of squares forms the logical
                         // cube
    // result_out(&head);     //Outputs the vertex coordinates of each cube

    newpoint(&nh);  // Place the camera on top of the vertex of the top cube
    // newpoint_out(&nh);

    point_create(&ph);  // Coordinates of the ground path and grid focus
    // point_out(&ph);
    // point_sort(&ph);
    point_sort1(&ph);  // Sort the camera Numbers from smallest to largest
    // printf(" after sort\n");
    // insert_sort(&ph);
    // point_out(&ph);
    point_delete(&ph);
    point_out(&ph);

    line_create(&lh, &ph);  // Connect the ground line to the intersection of
                            // the grid into a line segment
    line_out(&lh);
    line_lengthSum(&lh);
    save_init(&ch);
    save_init(&tch);
    save_init_line(&lih);
    line(&nh, &lh, &ch, &lih);
    line(&nh, &lh, &tch,&lih);  // The ground segment establishes contact with the camera

    resum(&ch, &newch);
    resum(&tch, &newch);  // Calculate the repeated sum
     //save_out(&newch);//有错误，内存访问错误
    // save_out(&ch);
    // save_out(&tch);

    save_init(&one);
    algorithm_one(&ch, &one, &lh);
    one_out(&one, &lh);

    save_init(&two);
    algorithm_two(&tch, &two, &lh);
    printf("\n\n");
    two_out(&two, &lh);

    return 0;
}

void newpoint_init(struct npoint *tmp) {
    tmp->x = 0;
    tmp->y = 0;
    tmp->height = 0;
    tmp->cameraId = 0;
    tmp->next = NULL;
}

int newpoint(struct npoint *nh) {
    struct npoint *tmp;
    newpoint_init(nh);
    int i, j, k = 1;
    for (i = 0; i < Y; i++) {
      for (j = 0; j < X; j++) {
        tmp = malloc(sizeof(struct npoint));
        newpoint_init(tmp);
        tmp->x = j * X_WIDTH;
        tmp->y = i * Y_WIDTH;
        tmp->height = H;
        tmp->cameraId = k;
        nh->next = tmp;
        nh = nh->next;
        k++;
      }
    }
    return 0;
}

void newpoint_out(struct npoint *nh) {
    struct npoint *p = nh->next;
    while (p) {
        printf("x =%d, y=%d, cameraId=%d\n", p->x, p->y, p->cameraId);
        p = p->next;
    }
}

float distance(struct point *p, struct point *q) {
    return sqrt((p->x - q->x) * (p->x - q->x) + (p->y - q->y) * (p->y - q->y));
}

void point_init(struct point *tmp) {
    tmp->x = 0;
    tmp->y = 0;
    tmp->id = 0;
    tmp->next = NULL;
    tmp->pre = NULL;
}

void insert_sort(struct point *ph) {
    struct point *tmp;
    struct point *q;
    struct point *t;
    point_init(tmp);
    q = ph;
    t = q->next;  // q指向待排序节点的前一个节点，t指向待排序节点
    while (t) {
        if (q->x < t->x) {
            tmp = t;
            t = t->next;
            if (t) {
                t->pre = q;
            }
            q->next = t;
            while (q && (q->x < tmp->x)) {
                q = q->pre;
            }
            if (q) {
                tmp->next = q->next;
                q->next->pre = tmp;
                q->next = tmp;
                tmp->pre = q;
            } else {
                tmp->next = ph;
                tmp->pre = NULL;
                ph->pre = tmp;
                ph = tmp;
            }
            if (t) {
                q = t->pre;
            }
        } else {
            t = t->next;
            q = q->next;
        }
    }
}

void point_sort(struct point *ph) {
    struct point *one = ph->next;
    struct point *two = ph->next;
    struct point *tmp, *onep;
    struct point *p;
    while (one) {
        p = one;
        onep = one;
        two = one->next;
        while (two) {
            if ((p->x - two->x) > 0 && (p->y - two->y) >= 0) {
                p = two;
            }
            two = two->next;
        }
        if (p != onep) {
            tmp = malloc(sizeof(struct point));
            memcpy(tmp, p, sizeof(struct point));
            memcpy(p, one, sizeof(struct point));
            memcpy(one, tmp, sizeof(struct point));
            // p->next = onep->next;
            // p->pre = onep->pre;
            // onep->next->pre = p;
            // onep->pre->next = p;

            // tmp->pre->next = onep;
            // tmp->next->pre = onep;
            // onep->pre = tmp->pre;
            // onep->next = tmp->next;
            // one = p;
            free(tmp);
        }
        one = one->next;
    }
}

void point_sort1(struct point *ph) {
    struct point *temp;
    struct point *p = ph;
    struct point *q = ph->next;
    while (p) {
        while (q) {
            if (q->x < p->x) {
                temp = malloc(sizeof(struct point));
                temp->x = p->x;
                temp->y = p->y;
                // temp->id = p->id;

                p->x = q->x;
                p->y = q->y;
                // p->id = q->id;

                q->x = temp->x;
                q->y = temp->y;
                // q->id = temp->id;

                free(temp);
            }
            q = q->next;
        }
        p = p->next;
        q = p;
    }
}
void point_delete(struct point *ph)
{
    struct point *p = ph;
    struct point *q = p->next;
    while (q)
    {
        
        if (q->x == p->x && q->y == p->y)
        {
            p->next = q->next;
            
            
        }
        p = p->next;
        q = p->next;
    }
}

// void point_create(struct point *ph) {// 124
//     struct point *tmp;
//     float limit_x = 19;
//     float limit_y = 39;
//     float x = 0, y;
//     int num = 1;
//     int temp;
//     point_init(ph);

//     while (x <= limit_x && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = 2 * x + 1;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     while (x <= 100 && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = x + 20;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     y = min_side_y;
//     while (y <= limit_y && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = (y - 1) / 2;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
   
//    // y = limit_x - min_side_y;
//     while (y <= 100 && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = y - 20;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
// }

// void point_create(struct point *ph) {// 141
//     struct point *tmp;
//     float limit_x = 72;
//     float limit_y = 82;//两直线的交点坐标
//     float x = 0, y;
//     int num = 1;
//     int temp;
//     point_init(ph);

//     while (x <= limit_x && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = x + 10;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     while (x <= 100 && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = -1 * x + 154;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     y = min_side_y;
//     while (y <= limit_y && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = y - 10;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
   
//    // y = limit_x - min_side_y;
//     while (y <= 100 && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = -1 * y +154;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
// }

void point_create(struct point *ph) {// 164
    struct point *tmp;
    int max_x = (X - 1) * X_WIDTH;
    int max_y = (Y - 1) * Y_WIDTH;
    float limit_x = 80;
    float limit_y = 21;
    float x = 0, y;
    int num = 1;
    //int temp;
    point_init(ph);

    while (x <= limit_x && x >= 0 && y<=max_side_y && y >= 0) {
        tmp = malloc(sizeof(struct point));
        point_init(tmp);
        y = 0.25 * x + 1;
        if(y>=max_side_y){
            break;
        }
        tmp->x = x;
        tmp->y = y;
        tmp->id = num;
        while (ph->next) {
            ph = ph->next;
        }
        ph->next = tmp;
        tmp->pre = ph;
        x += min_side_x;
        num += 1;
    }
    while (x <= max_x && x >= 0 && y<=max_side_y && y >= 0) {
        tmp = malloc(sizeof(struct point));
        point_init(tmp);
        y = 4 * x - 299;
        if(y>=max_side_y){
            break;
        }
        tmp->x = x;
        tmp->y = y;
        tmp->id = num;
        while (ph->next) {
            ph = ph->next;
        }
        ph->next = tmp;
        tmp->pre = ph;
        x += min_side_x;
        num += 1;
    }
    y = min_side_y;
    while (y <= limit_y && y >= 0 && x<=max_side_x && x>=0) {
        tmp = malloc(sizeof(struct point));
        point_init(tmp);
        x = 4 * y - 4;
         if(x<=0){
            break;
        }
        tmp->x = x;
        tmp->y = y;
        tmp->id = num;
        while (ph->next) {
            ph = ph->next;
        }
        ph->next = tmp;
        tmp->pre = ph;
        y += min_side_y;
        num += 1;
    }
   
   // y = limit_x - min_side_y;
    while (y <= max_y && y >= 0 && x<=max_side_x && x>=0) {
        tmp = malloc(sizeof(struct point));
        point_init(tmp);
        x = (y + 299) / 4;
         if(x<=0){
            break;
        }
        tmp->x = x;
        tmp->y = y;
        tmp->id = num;
        while (ph->next) {
            ph = ph->next;
        }
        ph->next = tmp;
        tmp->pre = ph;
        y += min_side_y;
        num += 1;
    }
}
// void point_create(struct point *ph) {// 181
//     struct point *tmp;
//     float limit_x = 49;
//     float limit_y = 99;
//     float x = 0, y;
//     int num = 1;
//     int temp;
//     point_init(ph);

//     while (x <= limit_x && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = 2 * x + 1;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     while (x <= 100 && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = -1 * x + 148;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     y = min_side_y;
//     while (y <= limit_y && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = (y - 1) / 2;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
   
//    // y = limit_x - min_side_y;
//     while (y <= 100 && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = -1 * y + 148;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
// }

// void point_create(struct point *ph) {// 203
//     struct point *tmp;
//     float limit_x = 22.8;
//     float limit_y = 95.2;
//     float x = 0, y;
//     int num = 1;
//     int temp;
//     point_init(ph);

//     while (x <= limit_x && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = 4 * x + 4;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     while (x <= 100 && x >= 0 && y<=max_side_y && y >= 0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         y = -1 * x + 118;
//         if(y>=max_side_y){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         x += min_side_x;
//         num += 1;
//     }
//     y = min_side_y;
//     while (y <= limit_y && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = (y - 4) / 4;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
   
//    // y = limit_x - min_side_y;
//     while (y <= 100 && y >= 0 && x<=max_side_x && x>=0) {
//         tmp = malloc(sizeof(struct point));
//         point_init(tmp);
//         x = -1 * y + 118;
//          if(x<=0){
//             break;
//         }
//         tmp->x = x;
//         tmp->y = y;
//         tmp->id = num;
//         while (ph->next) {
//             ph = ph->next;
//         }
//         ph->next = tmp;
//         tmp->pre = ph;
//         y += min_side_y;
//         num += 1;
//     }
// }

void point_out(struct point *ph) {
    struct point *p;
    p = ph->next;
    while (p) {
        printf("(x,y) = (%f, %f) id = %d \n", p->x, p->y, p->id);
        // printf("pre (x,y) = (%f, %f) id = %d \n", p->pre->x, p->pre->y,
        //  p->pre->id);
        p = p->next;
    }
}

void line_init(struct line *l) {
    l->startx = 0;
    l->starty = 0;
    l->endx = 0;
    l->endy = 0;
    l->timestamp = 0;
    l->id = 0;
    l->next = NULL;
}
void line_create(struct line *lh, struct point *ph) {
    struct point *p;
    struct line *tmp;
    p = ph->next;
    line_init(lh);
    while (p->next) {
        tmp = malloc(sizeof(struct point));
        line_init(tmp);
        tmp->startx = p->x;
        tmp->starty = p->y;
        tmp->endx = p->next->x;
        tmp->endy = p->next->y;
        tmp->id = p->id;
        tmp->timestamp = distance(p->next, p);

        while (lh->next) {
            lh = lh->next;
        }
        lh->next = tmp;
        p = p->next;
    }
}
void line_lengthSum(struct line *lh)
{
   struct line *p = lh->next;
    float sum=0;
    while (p)
    {
        sum = sum + p->timestamp;
        p=p->next;
        
    }
    printf("all line 's length is %f\n",sum);
}
void line_out(struct line *lh) {
    struct line *p = lh->next;
    int n=1;
    while (p) {
        printf(
            "start(x,y) = (%f, %f) end(x,y) = (%f, %f)\n id = %d time = %f\n\n",
            p->startx, p->starty, p->endx, p->endy, n, p->timestamp);

        p = p->next;
        n++;
        /* code */
    }
}

int line(struct npoint *head, struct line *lp, struct camerainfo *ci,
         struct lineinfo *li) {
    struct npoint *ph = head->next;
    struct line *plh;
    int i = 0;
    plh = lp->next;
    while (ph) {
        // printf("camerid = %d, (x,y) = %f, %f\n", ph->cameraId, ph->x, ph->y);
        while (plh) {
            int startret =
                lineincircle(plh->startx, plh->starty, ph->x, ph->y, height);
            int endret =
                lineincircle(plh->endx, plh->endy, ph->x, ph->y, height);

            int sl =
                lineinOval(plh->startx, plh->starty, ph->x, ph->y, height, 0);
            int el =
                lineinOval(plh->endx, plh->endy, ph->x, ph->y, height, 0);

            int sr =
                lineinOval(plh->startx, plh->starty, ph->x, ph->y, height, 1);
            int er =
                lineinOval(plh->endx, plh->endy, ph->x, ph->y, height, 1);

            if (startret && endret) {
                // printf("### Circle cameraId= %d \t in circle (x, y) = %f, %f
                // "
                //        "s=%d, e=%d line = %d\n",
                //        ph->cameraId, ph->x, ph->y, startret, endret,
                //        plh->id);
                save(ph, plh, ci, li, 1);
            }
            if (sl && el) {
                save(ph, plh, ci, li, 0);
                // printf("### Oval left camerid =%d i = %d \t in circle (x, y)
                // = %f, %f
                // "
                //        " s=%d, e=%d line = %d\n",
                //        ph->cameraId, i, ph->x, ph->y, sl, el, plh->id);
                // saveret(struct camerainfo *ci, struct lineinfo * li);
            }

            if (sr && er) {
                save(ph, plh, ci, li, 2);
                // printf("### Oval right camerid =%d i = %d \t in circle (x, y)
                // = %f, %f "
                //        "  s=%d, e=%d line = %d\n",
                //        ph->cameraId, i, ph->x, ph->y, sl, el, plh->id);
                // saveret(struct camerainfo *ci, struct lineinfo * li);
            }

            plh = plh->next;
        }
        plh = lp->next;
        ph = ph->next;
    }
    return 0;
}



// int lineincircle(float x, float y, float x0, float y0, float h) {//cita = 20 
//     float r = (x - x0) * (x - x0) + (y - y0) * (y - y0);
//     int ret = 0;
//     float r2 = sqrt(0.0311) * h;
//     float l = r2 * r2;
//     if (l >= r) {
//         ret = 1;
//     }
//     return ret;
// }

// int lineinOval(float x, float y, float x0, float y0, float h, int flag) {//cita = 20 
//     int ret = 0;
//     float fun, tma;
//     if (flag) {// flag=1, left
//         tma = (x - x0 + 0.3639 * h);
//     } else {
//         tma = (x - x0 - 0.3639 * h);
//     }

//     fun =
//         (( tma * tma) / (0.0564 * h * h)) + (((y - y0) * (y - y0)) / (0.0311 * h * h));

//     if (1 >= fun) {
//         ret = 1;
//     }
//     return ret;
// }

// int lineincircle(float x, float y, float x0, float y0, float h) {//cita = 30 
//     float r = (x - x0) * (x - x0) + (y - y0) * (y - y0);
//     int ret = 0;
//     float r2 = 0.27 * h;
//     float l = r2 * r2;
//     if (l >= r) {
//         ret = 1;
//     }
//     return ret;
// }

// int lineinOval(float x, float y, float x0, float y0, float h, int flag) {//cita = 30 
//     int ret = 0;
//     float fun, tma;
//     if (flag) {
//         tma = (x - x0 + 0.27 * h);
//     } else {
//         tma = (x - x0 - 0.27 * h);
//     }

//     fun =
//         (( tma * tma) / (0.1369 * h * h)) + (( (y - y0) * (y - y0)) / (0.0729 * h * h));

//     if (1 >= fun) {
//         ret = 1;
//     }
//     return ret;
// }

// int lineincircle(float x, float y, float x0, float y0, float h) {//cita = 40 
//     float r = (x - x0) * (x - x0) + (y - y0) * (y - y0);
//     int ret = 0;
//     float r2 = sqrt(0.1325) * h;
//     float l = r2 * r2;
//     if (l >= r) {
//         ret = 1;
//     }
//     return ret;
// }

// int lineinOval(float x, float y, float x0, float y0, float h, int flag) {//cita = 40 
//     int ret = 0;
//     float fun, tma;
//     if (flag) {// flag=1, left
//         tma = (x - x0 + 0.1763 * h);
//     } else {
//         tma = (x - x0 - 0.1763 * h);
//     }

//     fun =
//         (( tma * tma) / (0.2578 * h * h)) + (((y - y0) * (y - y0)) / (0.1325 * h * h));

//     if (1 >= fun) {
//         ret = 1;
//     }
//     return ret;
// }

// int lineincircle(float x, float y, float x0, float y0, float h) {//cita = 50 
//     float r = (x - x0) * (x - x0) + (y - y0) * (y - y0);
//     int ret = 0;
//     float r2 = sqrt(0.2174) * h;
//     float l = r2 * r2;
//     if (l >= r) {
//         ret = 1;
//     }
//     return ret;
// }

// int lineinOval(float x, float y, float x0, float y0, float h, int flag) {//cita = 50 
//     int ret = 0;
//     float fun, tma;
//     if (flag) {// flag=1, left
//         tma = (x - x0 + 0.0875 * h);
//     } else {
//         tma = (x - x0 - 0.0875 * h);
//     }

//     fun =
//         (( tma * tma) / (0.4493 * h * h)) + (((y - y0) * (y - y0)) / (0.2174 * h * h));

//     if (1 >= fun) {
//         ret = 1;
//     }
//     return ret;
// }

int lineincircle(float x, float y, float x0, float y0, float h) {//cita = 60 
    float r = (x - x0) * (x - x0) + (y - y0) * (y - y0);
    int ret = 0;
    float r2 = sqrt(3) / 3 * h;
    float l = r2 * r2;
    if (l >= r) {
        ret = 1;
    }
    return ret;
}

int lineinOval(float x, float y, float x0, float y0, float h, int flag) {//cita = 60 
    int ret = 0;
    float fun, tma;
    if (flag) {
        tma = (x - x0 + sqrt(3) / 2 * h);
    } else {
        tma = (x - x0 - sqrt(3) / 2 * h);
    }

    fun =
        ((4 * tma * tma) / (3 * h * h)) + ((3 * (y - y0) * (y - y0)) / (h * h));

    if (1 >= fun) {
        ret = 1;
    }
    return ret;
}

void save_init(struct camerainfo *ctmp) {
    ctmp->pos = 0;
    ctmp->cameraId = 0;
    ctmp->sum = 0;
    ctmp->resum = 0;
    ctmp->isdelete = 0;
    ctmp->line = NULL;
    ctmp->camera = NULL;
    ctmp->next = NULL;
}

void save_init_line(struct lineinfo *ltmp) {
    ltmp->lineId = 0;
    ltmp->line = NULL;
    ltmp->camera = NULL;
    ltmp->next = NULL;
}

void save(struct npoint *head, struct line *l, struct camerainfo *ci,
          struct lineinfo *li, int pos) {
    struct camerainfo *cp, *tcp;
    struct camerainfo *ctmp;
    struct lineinfo *lip, *tlp;
    struct lineinfo *ltmp;
    struct npoint *cnext;
    struct line *lnext;
    int flag = 0;

    cp = ci;
    tcp = cp->next;
    lip = li;
    tlp = li->next;
    while (tcp) {
        if (tcp->cameraId == head->cameraId && tcp->pos == pos) {
            flag = 1;
            break;
        }
        tcp = tcp->next;
    }

    if (flag) {
        tcp->sum += 1;
        tcp->lines[l->id] = 1;
        // cnext = tcp->camera;
        // while(cnext->next) {
        //   cnext = cnext->next;
        // }
        // cnext->next = head;

    } else {
        ctmp = malloc(sizeof(struct camerainfo));
        save_init(ctmp);
        ctmp->pos = pos;
        ctmp->cameraId = head->cameraId;
        ctmp->sum += 1;
        ctmp->line = l;
        ctmp->camera = head;
        ctmp->lines[l->id] = 1;
        while (cp->next) {
            cp = cp->next;
        }
        cp->next = ctmp;
    }
    flag = 0;

    while (tlp) {
        if (l->id == tlp->lineId) {
            flag = 1;
            break;
        }
        tlp = tlp->next;
    }
    if (flag) {
        // tlp->sum += 1;

    } else {
        ltmp = malloc(sizeof(struct lineinfo));
        save_init_line(ltmp);

        ltmp->lineId = l->id;
        ltmp->line = l;
        ltmp->camera = head;

        while (lip->next) {
            lip = lip->next;
        }
        lip->next = ltmp;
    }
}

void resum(struct camerainfo *ch, struct camerainfo *newch) {
    struct camerainfo *cp, *tcp, *newp, *tmp, *tmp2;
    int i;
    cp = ch->next;
    // newp = newch;
    // save_init(newch);

    while (cp->next) {
        tcp = cp->next;
        for (i = 0; i < 100; i++) {
            if (cp->lines[i] == 1 && tcp->lines[i] == 1) {
                cp->reline[i] = 1;
                cp->resum += 1;

                tcp->reline[i] = 1;
                tcp->resum += 1;

                // tmp = malloc(sizeof(struct camerainfo));
                // tmp2 = malloc(sizeof(struct camerainfo));
                // save_init(tmp);
                // save_init(tmp2);
                // memcpy(tmp, cp, sizeof(struct camerainfo));
                // memcpy(tmp2, tcp, sizeof(struct camerainfo));
                // tmp->next = tmp2;
                // tmp2->next = NULL;
                // while (newp->next) {
                //     newp = newp->next;
                // }
                // newp->next = tmp;
            }
        }
        cp = cp->next;
    }
}

void save_out(struct camerainfo *ch) {
    struct npoint *n;
    ch = ch->next;
    while (ch) {
        printf("id = %d sum=%d pos=%d resum=%d\n", ch->cameraId, ch->sum,
               ch->pos, ch->resum);
        n = ch->camera;

        // while(n) {
        //   printf("aaaaaaa\t cid=%d, (x,y) = (%f, %f) \n\n", n->cameraId,
        //   n->x, n->y); n = n->next;
        // }
        ch = ch->next;
    }
}

void one_out(struct camerainfo *reh, struct line *l) {
    struct camerainfo *tmp = reh->next;
    struct line *ltmp;
    int i, j;
    j = 1;

    while (tmp) {
        printf(
            "one:%d\n===================\ncamera Id = %3d, pos = %d, sum = %2d "
            "resum=%2d\n",
            j, tmp->cameraId, tmp->pos, tmp->sum, tmp->resum);
        printf("-------------------\n");
        for (i = 0; i < 100; i++) {
            if (tmp->lines[i] == 1) {
                printf("line = %d\t", i);
                ltmp = l->next;
                while (ltmp) {
                    if (ltmp->id == i) {
                        printf(
                            "start(x,y) = (%f, %f), end(x, y) = (%f, %f), long "
                            "= %f\n",
                            ltmp->startx, ltmp->starty, ltmp->endx, ltmp->endy,
                            ltmp->timestamp);
                    }
                    ltmp = ltmp->next;
                }
            }
        }
        if (tmp->resum) {
            printf("+++++++++++++++++++\n");
            for (i = 0; i < 100; i++) {
                if (tmp->reline[i] == 1) {
                    printf("reline = %d\t", tmp->reline[i]);
                    ltmp = l->next;
                    while (ltmp) {
                        if (ltmp->id == i) {
                            printf(
                                "start(x,y) = (%f, %f), end(x, y) = (%f, %f), "
                                "long = %f\n",
                                ltmp->startx, ltmp->starty, ltmp->endx,
                                ltmp->endy, ltmp->timestamp);
                        }
                        ltmp = ltmp->next;
                    }
                }
            }
        }

        tmp = tmp->next;
        printf("===================\n\n");
        j++;
    }
}

void algorithm_one(struct camerainfo *ch, struct camerainfo *reh, struct line *l) {
    struct camerainfo min;
    struct camerainfo *tmp = ch->next;
    struct camerainfo *pret = reh;
    struct camerainfo *ret;
    struct camerainfo *comp;
    struct line *line;
    int max, i, j, k;
    int num = 1;
    int flag = 0;
    int lineisdel[100] = {0};
    int isline[100] = {0};


    line = l->next;
    while(line) {
        isline[line->id] = 1;
        line = line->next;
    }
    
    while (num) {
        num = 0;
        tmp = ch->next;
        max = 1000;
        min.resum = 1000;

        while (tmp) {  //找到重复累加和最小的摄像头
            if (!tmp->isdelete) {
                num = 1;
                if (max > tmp->resum) {
                    max = tmp->resum;  //  这里的max其实代表的是min，最小的重复累加和
                    memcpy(&min, tmp, sizeof(struct camerainfo));
                }
            } else {
                // printf(" delete camera id =%d and pos = %d\n", tmp->cameraId, tmp->pos);
            }
            tmp = tmp->next;
        }


        if(num && min.resum < 999) {
            num = 0;
            flag = 0;
            for(j = 0; j < 100; j++) {
                for(k = 0 ; k < 100; k ++) {
                if(min.lines[k] && k == j) {
                            flag = 1;
                }
                }
                if(isline[j]) {
                    num = 1;
                    // printf("is line id = %d\n", j);
                    for(k = 0 ; k < 100; k ++) {
                        if(min.lines[k] && k == j) {
                            // printf("lnne and camera id = %d  min id = %d  resum = %d\n", k, min.cameraId, min.resum);
                            isline[j] = 0;
                            
                        } 
                    }
                }

            }
            if(flag) {
                ret = malloc(sizeof(struct camerainfo));
                memcpy(ret, &min, sizeof(struct camerainfo));
                ret->next = NULL;
                while (pret->next) {
                    if(pret->cameraId == ret->cameraId) {
                        ret->isdelete = 1;
                    }
                    pret = pret->next;
                }
                pret->next = ret;
            }

            tmp = ch->next;
            while (tmp) {  //将摄像头信息删除
            if(!tmp->isdelete) {
                if (tmp->cameraId == min.cameraId) {
                    tmp->isdelete = 1;
                }
            }
                tmp = tmp->next;
                
            }


        } else {
            num = 0;
        }
        

        // line = l->next;
        // while (line) {  // 找到最小累加和摄像头覆盖的线段，并将其从线段集合中删掉
        //     flag = 0;
        //     comp = reh->next;
        //     if (lineisdel[line->id] != 1) {
        //         while (comp) {
        //             if (comp->lines[line->id] != 1) {
        //                 lineisdel[line->id] = 1;
        //                 flag = 1;
        //                 break;
        //             }
        //             comp = comp->next;
        //         }
        //     }
        //     if (flag) {
        //         break;
        //     }
        //     line = line->next;
        // }

        // if (!line) {
        //     return;
        // }
    }
}

void two_out(struct camerainfo *reh, struct line *l) {
    struct camerainfo *tmp = reh->next;
    struct line *ltmp;
    int i;

    while (tmp) {
        printf(
            "two :line Id = %2d\n===================\ncamera Id = %3d, pos = "
            "%d, sum = %2d resum=%2d\n",
            tmp->lineId, tmp->cameraId, tmp->pos, tmp->sum, tmp->resum);
        printf("-------------------\n");
        for (i = 0; i < 100; i++) {
            if (tmp->lines[i] == 1) {
                printf("line = %d\t", i);
                ltmp = l->next;
                while (ltmp) {
                    if (ltmp->id == i) {
                        printf(
                            "start(x,y) = (%f, %f), end(x, y) = (%f, %f), long "
                            "= %f\n",
                            ltmp->startx, ltmp->starty, ltmp->endx, ltmp->endy,
                            ltmp->timestamp);
                    }
                    ltmp = ltmp->next;
                }
            }
        }
        if (tmp->resum) {
            printf("+++++++++++++++++++\n");
            for (i = 0; i < 100; i++) {
                if (tmp->reline[i] == 1) {
                    printf("reline = %d\t", tmp->reline[i]);
                    ltmp = l->next;
                    while (ltmp) {
                        if (ltmp->id == i) {
                            printf(
                                "start(x,y) = (%f, %f), end(x, y) = (%f, %f), "
                                "long = %f\n",
                                ltmp->startx, ltmp->starty, ltmp->endx,
                                ltmp->endy, ltmp->timestamp);
                        }
                        ltmp = ltmp->next;
                    }
                }
            }
        }

        tmp = tmp->next;
        printf("===================\n\n");
    }
}

void algorithm_two(struct camerainfo *ch, struct camerainfo *reh,
                   struct line *l) {
    // find line sum min
    struct camerainfo *ret;
    struct camerainfo min;
    struct camerainfo *tmp;

    struct camerainfo *pret = reh;
    struct line *line = l->next;
    int i, j, k, flag;

    int max = 999;
    int isline[100] = {0};


    while(line) {
        isline[line->id] = 1;
        line = line->next;
    }

    line = l->next;
    while (line) {  //以线段为主体，对覆盖该线段的摄像头进行重复累加和最小的选择
        tmp = ch->next;
        min.resum = 1000;
        max = 1000;
        while (tmp) {
            // printf("cameraId = %d  lines = %d, line=%d delete = %d\n",
            // line->id, tmp->lines[line->id], line->id, tmp->isdelete);
            if (tmp->isdelete == 0) {
                if (tmp->resum) {
                    if (tmp->reline[line->id] == 1) {
                        if (max >
                            tmp->resum) {  //这里的max其实还是min
                                           //，找到的是重复累加和最小的摄像头
                            max = tmp->resum;
                            memcpy(&min, tmp, sizeof(struct camerainfo));
                            min.lineId = line->id;
                        }
                    }

                } else {
                    if (tmp->lines[line->id] == 1) {
                        if (max > tmp->sum) {
                            max = tmp->sum;
                            memcpy(&min, tmp, sizeof(struct camerainfo));
                            min.lineId = line->id;
                        }
                    }  //算法二允许摄像头被多次选择（即切换不同的档位），所以摄像头不用删除，区别与算法1
                }
            }
            tmp = tmp->next;
        }
        if (min.resum < 999) {
            ret = malloc(sizeof(
                struct
                camerainfo));  //同样为了显示结果，将摄像头信息存放在ret中
            memcpy(ret, &min, sizeof(struct camerainfo));
            ret->next = NULL;
            while (pret->next) {
                pret = pret->next;
            }
            pret->next = ret;
            flag = 0;
            for(j = 0; j < 100; j++) {
                if(isline[j]) {
                    flag = 1;
                    for(k = 0 ; k < 100; k ++) {
                        if(min.lines[k] && k == j) {
                            isline[j] = 0;
                        } 
                    }
                }
        
            }
            if(!flag) {
                return ;
            }
        }
        line = line->next;
    }
}
