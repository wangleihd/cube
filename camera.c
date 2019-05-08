#include "camera.h"

const int max_side = 100;
const float min_side = 5;

struct point pitem[100];
int p_total = 0;

void cube_create(struct cube *);
void cube_init(struct cube *cube);
void cube_dot(struct cube *cube);
void cube_link(struct cube *head, struct cube *cube);
void result_out(struct cube *head);
void cube_search(struct cube *, float *, int, int, struct dot_in_cube *);
struct cube *search(struct cube *head, int row, int column);
void point_create(struct point *);
void point_init(struct point *);
void point_out(struct point *);
void line_init(struct line *);
void line_create(struct line *lh, struct point *ph);
void line_out(struct line *lh);
float distance(struct point *p, struct point *q);
// void curve_x(double *result, int step);
// void curve_y(double *res, int step);
// void fpWriteCoord(double x, int height); //Writes the intersection of the
// curve and the grid to a file int fpReadCoord();                       //Reads
// the intersection of the curves in the file with the grid void
// camera_link(struct camera *c, float x, float y, int id);

// void search_point_in_camera(struct point *, struct camera *);
// void init_camera(struct camera *);
// void camera_link(struct camera *c, float x, float y, int id);

// int circleANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct
// camera *c, struct point * gp); int LeftOvalANDLineIntersectionPoint(float X0,
// float Y0, int h, int f, struct camera *c, struct point *gp); int
// RigthOvalANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct
// camera *c, struct point * gp); int judgement(int X0, int Y0, int h, struct
// camera * c, struct point * gp); void search_gridpoint_in_camera(struct point
// *, struct camera *); void output_gridpoint(struct point * head); void
// grid_init(struct point * t); void link_point(struct point * p, struct line *
// lp); float distance(struct point * p, struct point * q); void out_line(struct
// line * lp);
void grid_init(struct point *t);

int main(void) {
  struct cube head;
  struct point ph;
  struct line lh;

  struct dot_in_cube result;
  int i;
  int id = 1;
  int len = 10;
  cube_create(&head);
  result_out(&head);

  point_create(&ph);
  point_out(&ph);

  line_create(&lh, &ph);
  line_out(&lh);

  // circleANDLineIntersectionPoint(20,40,5,2,1);
  // LeftOvalANDLineIntersectionPoint( 20, 50, 3, 2,  1);
  //     chead.next = NULL;
  //     grid_point.next = NULL;
  //     phead.next = NULL;
  //     lhead.next = NULL;
  //     plhead.next = NULL;
  //     chead.id = 0;

  //   for (i = 0; i < 10; i++)
  //     {
  //         camera_link(&chead, x[i], y[i], i + 1);
  //     }

  //     search_gridpoint_in_camera(&grid_point, &chead);
  //     output_gridpoint(&grid_point);
  //     link_point(&grid_point, &lhead);
  //     out_line(&lhead);

  //     search_point_in_camera(&phead, &chead);
  //     output_gridpoint(&phead);
  //     link_point(&phead, &plhead);
  //     out_line(&plhead);
  return 0;
}

float distance(struct point *p, struct point *q) {
  return sqrt((p->x - q->x) * (p->x - q->x) + (p->y - q->y) * (p->y - q->y));
}

void point_init(struct point *tmp) {
  tmp->x = 0;
  tmp->y = 0;
  tmp->total = 0;
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
    tmp->total = num;
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
      tmp->total = num;
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
    printf("(x,y) = (%f, %f) total = %d \n", p->x, p->y, p->total);
    p = p->next;
  }
}

void line_init(struct line *l) {
  l->startx = 0;
  l->starty = 0;
  l->endx = 0;
  l->endy = 0;
  l->timestamp = 0;
  l->total = 0;
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
    tmp->total = p->total;
    tmp->timestamp = distance(p->next, p);

    while (lh->next) {
      lh = lh->next;
    }
    lh->next = tmp;
    printf("(x,y) = (%f, %f) total = %d \n", p->x, p->y, p->total);
    p = p->next;
  }
}

void line_out(struct line *lh) {
  struct line *p = lh->next;
  while (p->next) {
    printf(
        "start(x,y) = (%f, %f) end(x,y) = (%f, %f)\n total = %d time = %f\n\n",
        p->startx, p->starty, p->endx, p->endy, p->total, p->timestamp);

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
    if (0 == (tmpright->column % (int)min_side)) {
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
      // fprintf(fp,"\t(%d, %d, %d)\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
      fprintf(fp, "%f, %f, %f\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
    }
    h = h->right;
  }
  fclose(fp); //关闭文件
}

void cube_search(struct cube *head, float *coordinate, int len, int flag,
                 struct dot_in_cube *res) {
  int i = 1;
  int step_x = 0;
  int step_y = 0;
  struct cube *p;
  struct cube *h = head;

  printf("flag: %d\n", flag);
  for (; i <= len; i++) {
    if (*coordinate > max_side) {
      coordinate++;
      continue;
    } else {
      if (1 == flag) {
        step_x = i;
        if (step_x <= 1) {
          step_x = 1;
        }
        step_y = (int)*coordinate / min_side + 1;
        p = search(head, step_x, step_y);
      } else {
        step_y = i;
        if (step_y <= 1) {
          step_y = 1;
        }
        step_x = (int)*coordinate / min_side + 1;
        p = search(head, step_x, step_y);
      }
    }
    // if(flag == 1) {
    //     printf("(x, y) = P(%d, %f)  [%d, %d], id = %d row = %d, column =
    //     %d,", i* min_side, *coordinate, step_x, step_y, p->id, p->row,
    //     p->column); if(p->right) printf("\tnext.id = %d, next.row = %d
    //     next.column = %d\n",p->right->id, p->right->row, p->right->column);

    // } else {
    //     printf("(x, y) = P(%f, %d)  [%d, %d], id = %d row = %d, column =
    //     %d,", *coordinate, i * min_side, step_x, step_y, p->id, p->row,
    //     p->column); if(p->top) printf("\tnext.id = %d, next.row = %d
    //     next.column = %d\n", p->top->id, p->top->row, p->top->column);

    // }
    coordinate++;
  }
}

struct cube *search(struct cube *head, int column, int row) {
  struct cube *tmp = head->right;
  while (tmp->row != row) {
    tmp = tmp->top;
  }
  while (tmp->column != column) {
    tmp = tmp->right;
  }
  return tmp;
}

void fpWriteCoord(double x, int height) {
  double y;
  int i, j;

  // x1=x;
  FILE *fp, *fp1, *fp2, *fp3;
  fp = fopen("CoordinatesY.txt",
             "w"); //打开文件 //x是固定的边长，所以不写，只写了Y
  if ((fp = fopen("CoordinatesY.txt", "w")) == NULL) //判断文件是否能打开
  {
    printf("fail to open the file!\n");
    exit(0);
  }

  while (x <= 45 && y <= 91) {
    for (i = 0; i <= 100; i += height) {
      for (j = 0; j <= 100; j += height) {
        //  y = 10*sin(x*3.14/180);
        y = 2 * x + 1;
        // if ((y == j || y == i|| x == i|| x == j )&& x!=0)
        if ((x == i || x == j) && x != 0 && x <= 45 && y <= 91)
        // if (y == j || y == i|| x == i|| x == j )
        {
          printf("The intersection point is :x= %lf ,y= %lf\n", x, y);
          // dot_x[j]=y;
          // fprintf(fp,"%lf %lf\n",x, y);
          fprintf(fp, "%lf %lf\n", x, y);
          break;
        }
      }
      x = x + 1;
    }
  }
  fclose(fp); //关闭文件

  x = 1;
  y = 0;
  fp1 = fopen("CoordinatesX.txt", "w");               //打开文件
  if ((fp1 = fopen("CoordinatesX.txt", "w")) == NULL) //判断文件是否能打开
  {
    printf("fail to open the file!\n");
    exit(0);
  }

  while (x <= 91 && y <= 45) {
    for (i = 0; i <= 100; i += height) {
      for (j = 0; j <= 100; j += height) {
        //  y = 10*sin(x*3.14/180);
        y = (x - 1) / 2; //反函数
        // if ((y == j || y == i|| x == i|| x == j )&& x!=0)
        if ((x == i) || (x == j && x != 0 && x <= 91 && y <= 45))
        // if (y == j || y == i|| x == i|| x == j )
        {
          printf("The intersection point is :x= %lf ,y= %lf\n", y,
                 x); //横纵坐标换一下输出
                     // dot_y[j]=x;
                     // fprintf(fp,"%lf %lf\n",y,x);
          fprintf(fp1, "%lf %lf\n", y, x);
          break;
        }
      }
      x = x + 1;
    }
  }
  fclose(fp1); //关闭文件

  fp2 = fopen("CoordinatesY.txt", "a");               //打开文件
  if ((fp2 = fopen("CoordinatesY.txt", "a")) == NULL) //判断文件是否能打开
  {
    printf("fail to open the file!\n");
    exit(0);
  }

  x = 45; //设计折线
  while (x <= 100 && y <= 91) {
    for (i = 0; i <= 100; i += height) {
      for (j = 0; j <= 100; j += height) {
        //  y = 10*sin(x*3.14/180);
        y = -1 * x + 136;
        // if ((y == j || y == i|| x == i|| x == j )&& x!=0)
        if ((x == i) || (x == j && x != 0 && x <= 100 && y <= 91))
        // if (y == j || y == i|| x == i|| x == j )
        {
          printf("The intersection point is :x= %lf ,y= %lf\n", x, y);
          // dot_x[j]=y;
          // fprintf(fp,"%lf %lf\n",x, y);
          fprintf(fp2, "%lf %lf\n", x, y);
          break;
        }
      }
      x = x + 1;
    }
  }
  fclose(fp2);                                        //关闭文件
  fp3 = fopen("CoordinatesX.txt", "a");               //打开文件
  if ((fp3 = fopen("CoordinatesX.txt", "a")) == NULL) //判断文件是否能打开
  {
    printf("fail to open the file!\n");
    exit(0);
  }

  x = 36;
  while (x <= 91 && y <= 100) {
    for (i = 0; i <= 100; i += height) {
      for (j = 0; j <= 100; j += height) {
        //  y = 10*sin(x*3.14/180);
        y = -x + 136;
        // if ((y == j || y == i|| x == i|| x == j )&& x!=0)
        if ((x == i || x == j) && (x != 0 && x <= 91 && y <= 100)) {
          printf("The intersection point is :x= %lf ,y= %lf\n", y, x);
          // dot_x[j]=y;
          // fprintf(fp,"%lf %lf\n",x, y);
          fprintf(fp2, "%lf %lf\n", y, x);
          break;
        }
      }
      x = x + 1;
    }
  }
  fclose(fp3); //关闭文件
}
int fpReadCoord() {
  int i = 0;
  FILE *fp, *fp1;

  fp = fopen("CoordinatesY.txt", "r");
  if (!fp) {
    printf("open file error\n");
    return -1;
  }

  while (!feof(fp)) {
    if (fscanf(fp, "%f", &dot_x[i]) != 1.0)
      break;
    //  fscanf( fp , "%lf" ,&dot_x[i]);
    printf("%f\n", dot_x[i]);
    i++;
    // getchar() ;//过滤掉分隔符
  }
  fclose(fp);
  printf("aaa");

  fp1 = fopen("CoordinatesX.txt", "r");
  if (!fp1) {
    printf("open file error\n");
    return -1;
  }
  while (!feof(fp1)) {
    if (fscanf(fp1, "%f", &dot_y[i]) != 1.0)
      break;
    printf("%f\n", dot_y[i]);
    i++;
    // fgetc(fp) ;//过滤掉分隔符
  }
  fclose(fp1);

  return 1;
}
