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
void point_out(struct point *);
void line_init(struct line *);
void line_create(struct line *lh, struct point *ph);
void line_out(struct line *lh);
float distance(struct point *p, struct point *q);
int line(struct npoint *head, struct line *lp, struct camerainfo *ci,
         struct lineinfo *li);
int lineincircle(float x, float y, float x0, float y0, float h);

int lineinOval(float a, float b, float x0, float y0);
float af(float h);
float bf(float h, float x, float y, int flag);
void save_init(struct camerainfo *ctmp);
void save_init_line(struct lineinfo *ltmp);
void save(struct npoint *head, struct line *lp, struct camerainfo *ci,
          struct lineinfo *li, int pos);
void save_out(struct camerainfo * ch);

void grid_init(struct point *t);

int main(void) {
  struct cube head;
  struct point ph;
  struct line lh;
  struct camerainfo ch;
  struct lineinfo lih;
  struct npoint nh;

  int i;
  int id = 1;
  int len = 10;
  cube_create(&head);
  // result_out(&head);

  newpoint(&head, &nh);
  // newpoint_out(&nh);

  point_create(&ph);
  // point_out(&ph);

  line_create(&lh, &ph);
  // line_out(&lh);

  save_init(&ch);
  save_init_line(&lih);
  line(&nh, &lh, &ch, &lih);
  save_out(&ch);

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
}

void point_create(struct point *ph) {
  struct point *tmp;
  int limit_x = 45;
  int limit_y = 51;
  int x = 0, y;
  int num = 1;
  int temp;
  point_init(ph);
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
    }

    temp = y % 10;
    if (temp) {
      y -= temp;
    } else {
      y -= 5;
    }
    num += 1;
  }
}

void point_out(struct point *ph) {
  struct point *p;
  p = ph->next;
  while (p->next) {
    printf("(x,y) = (%f, %f) id = %d \n", p->x, p->y, p->id);
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
    printf("start(x,y) = (%f, %f) end(x,y) = (%f, %f)\n id = %d time = %f\n\n",
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
  fp = fopen("All vertex coordinates1.txt", "w"); //打开文件
  if ((fp = fopen("All vertex coordinates1.txt", "w")) ==
      NULL) //判断文件是否能打开
  {
    printf("fail to open the file!\n");
    exit(0);
  }

  while (h) {
    // printf("column: %d", h->column);
    if (!(h->column % (int)min_side)) {
      // printf("\n\nid = %d\t floot = %d\t row = %d\t column = %d\t height =
      // %d\n", h -> id, h -> floor, h -> row, h -> column, h -> height);
      printf("\tid = %d \n", h->id);
      // fprintf(fp,"%d", h -> id);
      for (i = 0; i < dotleng; i++) {
        // printf("dot->id = %d\t (x, y, z) =  (%d, %d, %d)\n", h->dot[i].id,
        // h->dot[i].x, h->dot[i].y, h->dot[i].z);
        printf("dot->id = %d\t  (%f, %f, %fq)\n", h->dot[i].id, h->dot[i].x,
               h->dot[i].y, h->dot[i].z);
        // fprintf(fp,"\t(%d, %d, %d)\n", h->dot[i].x, h->dot[i].y,
        // h->dot[i].z);
        fprintf(fp, "%f, %f, %f\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
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
      // printf("dot->id = %d\t (x, y, z) =  (%d, %d, %d)\n", h->dot[i].id,
      // h->dot[i].x, h->dot[i].y, h->dot[i].z);
      printf("dot->id = %d\t  (%f, %f, %f)\n", h->dot[i].id, h->dot[i].x,
             h->dot[i].y, h->dot[i].z);
      // fprintf(fp,"\t(%d, %d, %d)\n", h->dot[i].x, h->dot[i].y,
      // h->dot[i].z);
      fprintf(fp, "%f, %f, %f\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
    }
    h = h->right;
  }
  fclose(fp); //关闭文件
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

      int startret = lineincircle(ph->x, ph->y, plh->startx, plh->starty, h);
      int endret = lineincircle(ph->x, ph->y, plh->endx, plh->endy, h);

      int a = af(h);
      int bl = bf(h, ph->x, ph->y, 0);
      int br = bf(h, ph->x, ph->y, 1);

      int sl = lineinOval(a, bl, plh->startx, plh->starty);
      int el = lineinOval(a, bl, plh->endx, plh->endy);

      int sr = lineinOval(a, br, plh->startx, plh->starty);
      int er = lineinOval(a, br, plh->endx, plh->endy);

      if (startret && endret) {
        printf("### Circle cameraId= %d \t in circle (x, y) = %f, %f   "
               "s=%d, e=%d line = %d\n",
               ph->cameraId, ph->x, ph->y, startret, endret, plh->id);
        save(ph, plh, ci, li, 1);
      }
      if (sl && el) {
        save(ph, plh, ci, li, 0);
        // printf("### Oval left camerid =%d i = %d \t in circle (x, y) = %f,
        // %f
        // "
        //        " s=%d, e=%d line = %d\n",
        //        ph->cameraId, i, ph->x, ph->y, sl, el, plh->id);
        // saveret(struct camerainfo *ci, struct lineinfo * li);
      }

      if (sr && er) {
        save(ph, plh, ci, li, 2);
        // printf("### Oval right camerid =%d i = %d \t in circle (x, y) = %f,
        // %f "
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

int lineinOval(float a, float b, float x0, float y0) {
  int fun = ((x0 * x0) / a) + ((y0 * y0) / b);
  int ret = 0;
  if (1 >= fun) {
    ret = 1;
  }
  return ret;
}

float af(float h) { return (4 * h * h) / 3; }

float bf(float h, float x, float y, int flag) {
  int ret = (4 * h * h * (y - sqrt(3) * h) * (y - sqrt(3) * h)) /
            (4 * h * h - 3 * x * x);
  if (flag) {
    ret = (4 * h * h * (y + sqrt(3) * h) * (y + sqrt(3) * h)) /
          (4 * h * h - 3 * x * x);
  }
  return ret;
}
void save_init(struct camerainfo *ctmp) {
  ctmp->pos = 0;
  ctmp->cameraId = 0;
  ctmp->sum = 0;
  ctmp->line = NULL;
  ctmp->camera = NULL;
  ctmp->next = NULL;
}

void save_init_line(struct lineinfo *ltmp){
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
  while(tcp) {
    if(tcp->cameraId == head->cameraId && tcp->pos == pos) {
      flag = 1;
      break;
    }
    tcp = tcp->next;
  }

  if(flag) {
    tcp->sum += 1;
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
  while (cp->next) {
    cp = cp->next;
  }
  cp->next = ctmp;
  }
  flag = 0;

  while ( tlp ){
    if (l->id == tlp->lineId)
    {
      flag = 1;
      break;
    }
    tlp=tlp->next;
  }
  if(flag) {
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

void save_out(struct camerainfo * ch) {
  struct npoint *n;
  ch=ch->next;
  while(ch) {
    printf("id = %d sum=%d pos=%d\n", ch->cameraId, ch->sum, ch->pos);
    n=ch->camera;
    // while(n) {
    //   printf("aaaaaaa\t cid=%d, (x,y) = (%f, %f) \n\n", n->cameraId, n->x, n->y);
    //   n = n->next;
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
