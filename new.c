#include "new.h"

// 摄像头的个数
#define X 10      // 每行摄像头的数量
#define Y 10      // 每列摄像头的数量
#define X_WIDTH 5 // 每行相邻摄像头的间距
#define Y_WIDTH 5 // 每列相邻摄像头的间距
#define H 3       // 摄像头水平高度

// 线段
#define FUN_1_X y-20    
#define FUN_1_Y y-20    
#define FUN_2_X y-20    
#define FUN_2_Y y-20    

// 创建摄像头的点
void point_create(struct camera *head);
void point_init(struct camera *c);
void point_out(struct camera *head);

//
void fucamera_create(struct point *head);
void fucamera_out(struct point *head);
void fucamera_init(struct point *head);

// 创建线段
void line_create(struct line *head, struct point *);
void line_out(struct line *head);
void line_init(struct line *head);
void line_lengthSum(struct line *head);

// 覆盖函数
int over_create(struct camera *head, struct line *lp, struct camera *ci);




int main(void) {
  struct camera point, over;
  struct line dline;
  struct point funcamera;

  // 创建摄像头的点
  point_init(&point);
  point_create(&point);
  point_out(&point);

  // 线段方程的点
  fucamera_init(&funcamera);
  fucamera_create(&funcamera);
  fucamera_out(&funcamera);

  // 创建线段
  line_init(&dline);
  line_create(&dline, &funcamera);
  line_out(&dline);
  line_lengthSum(&dline);


  // 覆盖
  point_init(&over);
  over_create(&point, &dline, &over);

  return 0;
}

void point_init(struct camera *c) {
  c->id = 0;
  c->pos = 0;
  c->sum = 0;
  c->resum = 0;
  c->lineId = 0;
  c->cameraId = 0;
  c->isdelete = 0;
  c->x = 0;
  c->y = 0;
  c->h = 0;
  c->next = NULL;
  c->pre = NULL;
}

void point_create(struct camera *head) {
  struct camera *tmp;
  int i, j, k = 1;
  for (i = 0; i < Y; i++) {
    for (j = 0; j < X; j++) {
      tmp = malloc(sizeof(struct camera));
      point_init(tmp);
      tmp->x = j * X_WIDTH;
      tmp->y = i * Y_WIDTH;
      tmp->h = H;
      tmp->id = k;
      head->next = tmp;
      head = head->next;
      k++;
    }
  }
}

void point_out(struct camera *head) {
  head = head->next;
  while (head) {
    printf("ID: %d\t   x= %d \t y= %d\t h=%d\n", head->id, head->x, head->y,
           head->h);
    head = head->next;
  }
}

float distance(struct point *p, struct point *q) {
  return sqrt((p->x - q->x) * (p->x - q->x) + (p->y - q->y) * (p->y - q->y));
}

void fucamera_create(struct point *head) {
  struct point *tmp;
  float limit_x = 19;
  float limit_y = 39;
  float x = 0, y;
  int num = 1;
  int temp;
  int max_side_y = Y_WIDTH * (Y - 1);
  int max_side_x = X_WIDTH * (X - 1);
  int min_side_x = X_WIDTH;
  int min_side_y = Y_WIDTH;

  while (x <= limit_x && x >= 0 && y <= max_side_y && y >= 0) {
    tmp = malloc(sizeof(struct point));
    fucamera_init(tmp);
    y = 2 * x + 1;
    if (y >= max_side_y) {
      break;
    }
    tmp->x = x;
    tmp->y = y;
    tmp->id = num;
    while (head->next) {
      head = head->next;
    }
    head->next = tmp;
    tmp->pre = head;
    x += min_side_x;
    num += 1;
  }
  while (x <= 100 && x >= 0 && y <= max_side_y && y >= 0) {
    tmp = malloc(sizeof(struct point));
    fucamera_init(tmp);
    y = x + 20;
    if (y >= max_side_y) {
      break;
    }
    tmp->x = x;
    tmp->y = y;
    tmp->id = num;
    while (head->next) {
      head = head->next;
    }
    head->next = tmp;
    tmp->pre = head;
    x += min_side_x;
    num += 1;
  }
  y = min_side_y;
  while (y <= limit_y && y >= 0 && x <= max_side_x && x >= 0) {
    tmp = malloc(sizeof(struct point));
    fucamera_init(tmp);
    x = (y - 1) / 2;
    if (x <= 0) {
      break;
    }
    tmp->x = x;
    tmp->y = y;
    tmp->id = num;
    while (head->next) {
      head = head->next;
    }
    head->next = tmp;
    tmp->pre = head;
    y += min_side_y;
    num += 1;
  }

  // y = limit_x - min_side_y;
  while (y <= 100 && y >= 0 && x <= max_side_x && x >= 0) {
    tmp = malloc(sizeof(struct point));
    fucamera_init(tmp);
    x = y - 20;
    if (x <= 0) {
      break;
    }
    tmp->x = x;
    tmp->y = y;
    tmp->id = num;
    while (head->next) {
      head = head->next;
    }
    head->next = tmp;
    tmp->pre = head;
    y += min_side_y;
    num += 1;
  }
}

void fucamera_out(struct point *head) {
  head = head->next;
  while (head) {
    printf("fun point ID: %2d\t x=%9f, y=%9f\n", head->id, head->x, head->y);
    head = head->next;
  }
}
void fucamera_init(struct point *head) {
  head->x = 0;
  head->y = 0;
  head->id = 0;
  head->next = NULL;
  head->pre = NULL;
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
    while (p) {
        printf(
            "start(x,y) = (%9f, %9f) end(x,y) = (%9f, %9f)\t id = %2d time = %f\n\n",
            p->startx, p->starty, p->endx, p->endy, p->id, p->timestamp);
        p = p->next;
    }
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

    fun =
        ((4 * tma * tma) / (3 * h * h)) + ((3 * (y - y0) * (y - y0)) / (h * h));

    if (1 >= fun) {
        ret = 1;
    }
    return ret;
}

int over_create(struct camera *head, struct line *lp, struct camera *ci) {
    struct camera *ph = head->next;
    struct line *plh;
    int i = 0;
    int height = H;
    plh = lp->next;
    while (ph) {
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
        // printf("camerid = %d, (x,y) = %d, %d [1] = (%d, %d)\n", ph->cameraId, ph->x, ph->y, startret, endret);

            if (startret && endret) {
                // save(ph, plh, ci, li, 1);
                printf("### Circle cameraId= %d \t in circle (x, y) = %d, %d s=%d, e=%d line = %d \n", ph->id, ph->x, ph->y, startret, endret, plh->id);
            }
            if (sl && el) {
                // save(ph, plh, ci, li, 0);
                // printf("### Oval left camerid =%d i = %d \t in circle (x, y)
                // = %f, %f
                // "
                //        " s=%d, e=%d line = %d\n",
                //        ph->cameraId, i, ph->x, ph->y, sl, el, plh->id);
                // saveret(struct camera *ci, struct lineinfo * li);
            }

            if (sr && er) {
                // save(ph, plh, ci, li, 2);
                // printf("### Oval right camerid =%d i = %d \t in circle (x, y)
                // = %f, %f "
                //        "  s=%d, e=%d line = %d\n",
                //        ph->cameraId, i, ph->x, ph->y, sl, el, plh->id);
                // saveret(struct camera *ci, struct lineinfo * li);
            }

            plh = plh->next;
        }
        plh = lp->next;
        ph = ph->next;
    }
    return 0;
}

void save(struct camera *head, struct line *l, struct camera *ci, int pos) {
    struct camera *cp, *tcp;
    struct camera *ctmp;
    struct camera *cnext;
    struct line *lnext;
    int flag = 0;

    cp = ci;
    tcp = cp->next;
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
        ctmp = malloc(sizeof(struct camera));
        point_init(ctmp);
        // ctmp->line = l;
        // ctmp->camera = head;

        ctmp->pos = pos;
        ctmp->cameraId = head->cameraId;
        ctmp->sum += 1;
        ctmp->lines[l->id] = 1;
        while (cp->next) {
            cp = cp->next;
        }
        cp->next = ctmp;
    }
}



void one_out(struct camera *reh, struct line *l) {
    struct camera *tmp = reh->next;
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

void algorithm_one(struct camera *ch, struct camera *reh,
                   struct line *l) {
    struct camera min;
    struct camera *tmp = ch->next;
    struct camera *pret = reh;
    struct camera *ret;
    struct camera *comp;
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
                    memcpy(&min, tmp, sizeof(struct camera));
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
                if(isline[j]) {
                    num = 1;
                    // printf("is line id = %d\n", j);
                    for(k = 0 ; k < 100; k ++) {
                        if(min.lines[k] && k == j) {
                            flag = 1;
                            // printf("lnne and camera id = %d  min id = %d  resum = %d\n", k, min.cameraId, min.resum);
                            isline[j] = 0;
                            
                        } 
                    }
                }

            }
            if(flag) {
                ret = malloc(sizeof(struct camera));
                memcpy(ret, &min, sizeof(struct camera));
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

void two_out(struct camera *reh, struct line *l) {
    struct camera *tmp = reh->next;
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

void algorithm_two(struct camera *ch, struct camera *reh, struct line *l) {
    // find line sum min
    struct camera *ret;
    struct camera min;
    struct camera *tmp;

    struct camera *pret = reh;
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
                            memcpy(&min, tmp, sizeof(struct camera));
                            min.lineId = line->id;
                        }
                    }

                } else {
                    if (tmp->lines[line->id] == 1) {
                        if (max > tmp->sum) {
                            max = tmp->sum;
                            memcpy(&min, tmp, sizeof(struct camera));
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
                camera));  //同样为了显示结果，将摄像头信息存放在ret中
            memcpy(ret, &min, sizeof(struct camera));
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


