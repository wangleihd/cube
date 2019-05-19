
#include "camera.h"
const int max_side = 100;
const float min_side = 5;
const float max = 20;
const float h = 3;

struct point pitem[100];
int p_total = 0;

void cube_create(struct cube *);
void cube_init(struct cube *cube);
void cube_dot(struct cube *cube);
void cube_link(struct cube *head, struct cube *cube);
void result_out(struct cube *head);
int newpoint(struct cube *head, struct npoint *nh);
void newpoint_out(struct npoint *nh);
void point_create(struct point *);
void point_init(struct point *);
void point_sort(struct point *ph);
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

void algorithm_one(struct camerainfo *ch, struct retcam *reh, struct line *l);
void one_init(struct retcam *);
void one_out(struct retcam *reh);
void two_out(struct retcam *reh);

void algorithm_two(struct camerainfo *ch, struct retcam *reh, struct line *l);

void grid_init(struct point *t);

int main(void) {
    struct cube head;
    struct point ph;
    struct line lh;
    struct camerainfo ch, tch, newch;
    struct lineinfo lih;
    struct npoint nh;
    struct retcam one, two;

    int i;
    int id = 1;
    int len = 10;
    cube_create(&head);
    // result_out(&head);

    newpoint(&head, &nh);
    // newpoint_out(&nh);

    point_create(&ph);
    point_sort(&ph);
    point_out(&ph);

    line_create(&lh, &ph);
    // line_out(&lh);

    save_init(&ch);
    save_init(&tch);
    save_init_line(&lih);
    line(&nh, &lh, &ch, &lih);
    line(&nh, &lh, &tch, &lih);

    // resum(&ch, &newch);
    // save_out(&newch);
    // save_out(&ch);

    one_init(&one);
    algorithm_one(&ch, &one, &lh);
    // one_out(&one);

    one_init(&two);
    algorithm_two(&tch, &two, &lh);
    printf("\n\n");
    // two_out(&two);

    return 0;
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
            if ((p->x - two->x) >= 0 && (p->y - two->y) >= 0) {
            printf("p = %p id=%d (%f, %f) n = %p, p=%p \ntmp = %p id=%d (%f, %f) n->%p, p=%p\nn = %p, p=%p\n", p, p->id, p->x, p->y, p->next, p->pre, two, two->id, two->x, two->y, two->next, two->pre, onep->next, onep->pre);
                p = two;
            }
            two = two->next;
        }
        if (p != onep) {
            tmp = malloc(sizeof(struct point));
            memcpy(tmp, p, sizeof(struct point));
            p->next = onep->next;
            p->pre = onep->pre;
            onep->next->pre = p;
            onep->pre->next = p;

            tmp->pre->next = onep;
            tmp->next->pre = onep;
            onep->pre = tmp->pre;
            onep->next = tmp->next;
            one = p;
           free(tmp);
        }
        one = one->next;
    }
}

void point_create(struct point *ph) {
    struct point *tmp;
    int limit_x = 45;
    int limit_y = 51;
    int x = 0, y;
    int num = 1;
    int temp;
    point_init(ph);
    y = 5;
    while (y <= limit_y) {
        tmp = malloc(sizeof(struct point));
        point_init(tmp);
        x = (y + 1) / 2;
        tmp->x = x;
        tmp->y = y;
        tmp->id = num;
        while (ph->next) {
            ph = ph->next;
        }
        ph->next = tmp;
        tmp->pre = ph;
        y += 5;
        num += 1;
    }
    x = 0;
    while (x <= limit_x) {
        tmp = malloc(sizeof(struct point));
        point_init(tmp);
        y = 2 * x + 1;
        tmp->x = x;
        tmp->y = y;
        tmp->id = num;
        while (ph->next) {
            ph = ph->next;
        }
        ph->next = tmp;
        tmp->pre = ph;
        x += 5;
        num += 1;
    }

    while (0 <= y && 100 > x) {
        x = -y + 136;

        if (100 > x) {
            tmp = malloc(sizeof(struct point));
            point_init(tmp);
            tmp->x = x;
            tmp->y = y;
            tmp->id = num;
            while (ph->next) {
                ph = ph->next;
            }
            ph->next = tmp;
            tmp->pre = ph;
        }

        temp = y % 10;
        if (temp) {
            y -= temp;
        } else {
            y -= 5;
        }
        num += 1;
    }
    // x = 45;
    // y = 91;
    // while (0 <= y && 100 > x) {
    //     x = -y + 136;

    //     if (100 > x) {
    //         tmp = malloc(sizeof(struct point));
    //         point_init(tmp);
    //         tmp->x = x;
    //         tmp->y = y;
    //         tmp->id = num;
    //         while (ph->next) {
    //             ph = ph->next;
    //         }
    //         ph->next = tmp;
    //     }

    //     temp = y % 10;
    //     if (temp) {
    //         y -= temp;
    //     } else {
    //         y -= 5;
    //     }
    //     num += 1;
    // }
}

void point_out(struct point *ph) {
    struct point *p;
    p = ph->next;
    while (p->next) {
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

void line_out(struct line *lh) {
    struct line *p = lh->next;
    while (p->next) {
        printf(
            "start(x,y) = (%f, %f) end(x,y) = (%f, %f)\n id = %d time = %f\n\n",
            p->startx, p->starty, p->endx, p->endy, p->id, p->timestamp);

        p = p->next;
        /* code */
    }
}

void cube_create(struct cube *head) {
    int i, k, f;
    struct cube *p;
    int num = 0;
    double res[12] = {0};

    cube_init(head);
    // printf("head.id=%d\n", head.id);
    for (i = 0; i < max_side / min_side; i++) {
        for (k = 0; k < max_side / min_side; k++) {
            num += 1;
            p = malloc(sizeof(struct cube));
            cube_init(p);
            // head->left = p;
            p->id = num;
            p->floor = 0;
            p->row = i + 1;
            p->column = k + 1;
            p->width = min_side;
            cube_dot(p);
            cube_link(head, p);
        }
    }
}

void cube_init(struct cube *p) {
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

void cube_dot(struct cube *c) {
    int i = 0;
    int side_lenght = min_side;
    int row = c->row;
    int column = c->column;
    int floor = c->floor;
    c->height = min_side;

    for (; i < dotleng; i++) {
        c->dot[i].id = i;
        if (i == 0) {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 1) {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 2) {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 3) {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 4) {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
        if (i == 5) {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
        if (i == 6) {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
        if (i == 7) {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
    }
}

void cube_link(struct cube *h, struct cube *p) {
    struct cube *tmpright = h;
    struct cube *tmptop = h->right;
    int i = 0;
    int dot = 0;
    while (tmpright->right) {
        tmpright = tmpright->right;
        if (0 == (tmpright->column % (int)max)) {
            if (tmptop->top) {
                tmpright = tmptop->top;
                tmptop = tmptop->top;
            } else {
                dot = 1;
                tmpright = tmptop;
                break;
            }
        }
    }
    if (dot == 1) {
        tmpright->top = p;
        p->bottom = tmpright;
    } else {
        tmpright->right = p;
        p->left = tmpright;
        if (tmpright->row > 1) {
            tmpright->bottom->right->top = p;
            p->bottom = tmpright->bottom->right;
        }
    }
}

void result_out(struct cube *m) {
    struct cube *h = m->right;
    struct cube *row = m->right->top;
    int i;
    FILE *fp;
    // fp=fopen("All vertex coordinates.txt","w");//打开文件
    // if ((fp=fopen("All vertex coordinates.txt","w"))==NULL)
    // //判断文件是否能打开
    fp = fopen("All vertex coordinates1.txt", "w");  //打开文件
    if ((fp = fopen("All vertex coordinates1.txt", "w")) ==
        NULL)  //判断文件是否能打开
    {
        printf("fail to open the file!\n");
        exit(0);
    }

    while (h) {
        // printf("column: %d", h->column);
        if (!(h->column % (int)min_side)) {
            // printf("\n\nid = %d\t floot = %d\t row = %d\t column = %d\t
            // height = %d\n", h -> id, h -> floor, h -> row, h -> column, h ->
            // height);
            printf("\tid = %d \n", h->id);
            // fprintf(fp,"%d", h -> id);
            for (i = 0; i < dotleng; i++) {
                // printf("dot->id = %d\t (x, y, z) =  (%d, %d, %d)\n",
                // h->dot[i].id, h->dot[i].x, h->dot[i].y, h->dot[i].z);
                printf("dot->id = %d\t  (%f, %f, %fq)\n", h->dot[i].id,
                       h->dot[i].x, h->dot[i].y, h->dot[i].z);
                // fprintf(fp,"\t(%d, %d, %d)\n", h->dot[i].x, h->dot[i].y,
                // h->dot[i].z);
                fprintf(fp, "%f, %f, %f\n", h->dot[i].x, h->dot[i].y,
                        h->dot[i].z);
            }
            if (!row) {
                return;
            } else {
                h = row;
                row = row->top;
            }
        }
        // printf("\n\nid = %d\t floot = %d\t row = %d\t column = %d\t height =
        // %d\n", h -> id, h -> floor, h -> row, h -> column, h -> height);
        printf("\tid = %d \n", h->id);
        // fprintf(fp,"%d", h -> id);
        for (i = 0; i < dotleng; i++) {
            // printf("dot->id = %d\t (x, y, z) =  (%d, %d, %d)\n",
            // h->dot[i].id, h->dot[i].x, h->dot[i].y, h->dot[i].z);
            printf("dot->id = %d\t  (%f, %f, %f)\n", h->dot[i].id, h->dot[i].x,
                   h->dot[i].y, h->dot[i].z);
            // fprintf(fp,"\t(%d, %d, %d)\n", h->dot[i].x, h->dot[i].y,
            // h->dot[i].z);
            fprintf(fp, "%f, %f, %f\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
        }
        h = h->right;
    }
    fclose(fp);  //关闭文件
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
                lineincircle(plh->startx, plh->starty, ph->x, ph->y, h);
            int endret = lineincircle(plh->endx, plh->endy, ph->x, ph->y, h);

            int sl = lineinOval(plh->startx, plh->starty, ph->x, ph->y, h, 0);
            int el = lineinOval(plh->startx, plh->starty, ph->x, ph->y, h, 0);

            int sr = lineinOval(plh->startx, plh->starty, ph->x, ph->y, h, 1);
            int er = lineinOval(plh->startx, plh->starty, ph->x, ph->y, h, 1);

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

int lineincircle(float x, float y, float x0, float y0, float h) {
    float r = (x - x0) * (x - x0) + (y - y0) * (y - y0);
    int ret = 0;
    float r2 = sqrt(3) / 3 * h;
    float l = r2 * r2;
    if (l >= r) {
        ret = 1;
    }
    return ret;
}

int lineinOval(float x, float y, float x0, float y0, float h, int flag) {
    int ret = 0;
    float fun, tma;
    if (flag) {
        tma = (x - x0 + sqrt(3) / 2 * h);
    } else {
        tma = (x - x0 - sqrt(3) / 2 * h);
    }

    fun = ((4 * tma * tma) / (3 * h * h)) +
          ((12 * (y - y0) * (y - y0)) / (h * h));

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
    save_init(newch);
    newp = newch;

    while (cp->next) {
        tcp = cp->next;
        for (i = 0; i < 100; i++) {
            if (cp->lines[i] == 1 && tcp->lines[i] == 1) {
                cp->reline[i] = 1;
                cp->resum += 1;
                tcp->reline[i] = 1;
                tcp->resum += 1;

                tmp = malloc(sizeof(struct camerainfo));
                tmp2 = malloc(sizeof(struct camerainfo));
                save_init(tmp);
                save_init(tmp2);
                memcpy(tmp, cp, sizeof(struct camerainfo));
                memcpy(tmp2, tcp, sizeof(struct camerainfo));
                tmp->next = tmp2;
                tmp2->next = NULL;
                while (newp->next) {
                    newp = newp->next;
                }
                newp->next = tmp;
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

void newpoint_init(struct npoint *tmp) {
    tmp->x = 0;
    tmp->y = 0;
    tmp->height = 0;
    tmp->cameraId = 0;
    tmp->next = NULL;
}

int newpoint(struct cube *head, struct npoint *nh) {
    struct cube *ph = head->right;
    struct cube *ptop = ph->top;
    struct npoint *tmp;
    newpoint_init(nh);
    while (ph) {
        tmp = malloc(sizeof(struct npoint));
        newpoint_init(tmp);
        tmp->x = ph->dot[0].x;
        tmp->y = ph->dot[0].y;
        tmp->height = ph->height;
        tmp->cameraId = ph->id;
        while (nh->next) {
            nh = nh->next;
        }
        nh->next = tmp;

        if (!(ph->column % (int)max)) {
            tmp = malloc(sizeof(struct npoint));
            newpoint_init(tmp);
            tmp->x = ph->dot[1].x;
            tmp->y = ph->dot[1].y;
            tmp->height = ph->height;
            tmp->cameraId = ph->id + 1;
            while (nh->next) {
                nh = nh->next;
            }
            nh->next = tmp;

            if (!ptop) {
                return 0;
            } else {
                ph = ptop;
                ptop = ptop->top;
            }
        }
        ph = ph->right;
    }
    return 0;
}
void newpoint_out(struct npoint *nh) {
    struct npoint *p = nh->next;
    while (p) {
        printf("x =%f, y=%f, cameraId=%d\n", p->x, p->y, p->cameraId);
        p = p->next;
    }
}

void one_init(struct retcam *tmp) {
    tmp->pos = 0;
    tmp->cameraId = 0;
    tmp->sum = 0;
    tmp->next = NULL;
}

void one_out(struct retcam *reh) {
    struct retcam *tmp = reh->next;

    while (tmp) {
        printf("# one\t id= %3d, pos = %d, sum = %2d\n", tmp->cameraId,
               tmp->pos, tmp->sum);
        tmp = tmp->next;
    }
}

void algorithm_one(struct camerainfo *ch, struct retcam *reh, struct line *l) {
    struct camerainfo *min;
    struct camerainfo *tmp = ch->next;
    struct retcam *pret = reh;
    struct retcam *ret;
    struct retcam *comp;
    struct line *line = l->next;
    int max = 999;
    int num = 1;
    int flag = 0;

    while (num) {
        num = 0;
        while (tmp) {
            if (tmp->isdelete == 0) {
                num += 1;
                if (max >= tmp->sum) {
                    max = tmp->sum;
                    min = tmp;
                }
            }
            tmp = tmp->next;
        }
        ret = malloc(sizeof(struct retcam));
        one_init(ret);
        ret->pos = min->pos;
        ret->cameraId = min->cameraId;
        ret->sum = min->sum;
        memcpy(ret->lines, min->lines, 100 * sizeof(int));
        while (pret->next) {
            pret = pret->next;
        }
        pret->next = ret;

        // delete camera and pos
        tmp = ch->next;
        while (tmp) {
            if (tmp->cameraId == min->cameraId) {
                tmp->isdelete = 1;
            }
            tmp = tmp->next;
        }
        // printf("tmp: %d, %d, %d num = %d\n", min->cameraId, min->sum,
        // min->pos, num);

        max = 999;
        tmp = ch->next;

        while (line) {
            flag = 0;
            comp = reh->next;
            while (comp) {
                if (comp->lines[line->id] != 1) {
                    flag = 1;
                    break;
                }
                comp = comp->next;
            }
            if (flag) {
                break;
            }
            line = line->next;
        }

        if (!line) {
            return;
        }

        line = l->next;
    }
}

void two_out(struct retcam *reh) {
    struct retcam *tmp = reh->next;

    while (tmp) {
        printf("# tow\t id= %2d, cameraId = %3d, pos = %d, sum = %2d\n",
               tmp->lineId, tmp->cameraId, tmp->pos, tmp->sum);
        tmp = tmp->next;
    }
}

void algorithm_two(struct camerainfo *ch, struct retcam *reh, struct line *l) {
    // find line sum min
    struct line *line = l->next;
    struct camerainfo *tmp = ch->next;
    struct camerainfo *min;
    struct retcam *pret = reh;
    struct retcam *ret;
    int max = 999;

    while (line) {
        while (tmp) {
            // printf("cameraId = %d\n", line->id);
            if (tmp->isdelete == 0) {
                if (tmp->lines[line->id] == 1) {
                    if (max >= tmp->sum) {
                        max = tmp->sum;
                        min = tmp;
                    }
                }
            }
            tmp = tmp->next;
        }

        if (min) {
            min->isdelete = 1;
            ret = malloc(sizeof(struct retcam));
            one_init(ret);
            ret->pos = min->pos;
            ret->cameraId = min->cameraId;
            ret->sum = min->sum;
            ret->lineId = line->id;
            memcpy(ret->lines, min->lines, 100 * sizeof(int));
            while (pret->next) {
                pret = pret->next;
            }
            pret->next = ret;
        } else {
            printf("min is error \n");
        }

        min = NULL;
        line = line->next;
        tmp = ch->next;
        max = 999;
    }
}

