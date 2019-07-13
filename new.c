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
void funpoint_create(struct point *head);
void funpoint_out(struct point *head);
void funpoint_init(struct point *head);

// 创建线段
void line_create(struct line *head);
void line_out(struct line *head);
void line_init(struct line *head);

int main(void) {
  struct camera point;
  struct line dline;
  struct point funpoint;

  // 创建摄像头的点
  point_init(&point);
  point_create(&point);
  point_out(&point);

  // 线段方程的点

  funpoint_init(&funpoint);
  funpoint_create(&funpoint);
  funpoint_out(&funpoint);

  // 创建线段
  line_init(&dline);
  line_create(&dline);
  line_out(&dline);

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

void funpoint_create(struct point *head) {
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
    funpoint_init(tmp);
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
    funpoint_init(tmp);
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
    funpoint_init(tmp);
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
    funpoint_init(tmp);
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

void funpoint_out(struct point *head) {
  head = head->next;
  while (head) {
    printf("fun point ID: %2d\t x=%9f, y=%9f\n", head->id, head->x, head->y);
    head = head->next;
  }
}
void funpoint_init(struct point *head) {
  head->x = 0;
  head->y = 0;
  head->id = 0;
  head->next = NULL;
  head->pre = NULL;
}

void line_create(struct line *head) {}

void line_out(struct line *head) {}

void line_init(struct line *head) {}
