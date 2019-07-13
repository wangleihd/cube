#include "new.h"

// 摄像头的个数
#define X 10             // 每行摄像头的数量
#define Y 10             // 每列摄像头的数量
#define X_WIDTH 5        // 每行相邻摄像头的间距
#define Y_WIDTH 5        // 每列相邻摄像头的间距
#define H 3              // 摄像头水平高度

// 线段

// 创建摄像头的点
void point_create(struct camera * head);
void point_init(struct camera * c);
void point_out(struct camera * head);

//
void funpoint_create(struct point * head);
void funpoint_out(struct point * head);
void funpoint_init(struct point * head);

// 创建线段
void line_create(struct line * head);
void line_out(struct line * head);
void line_init(struct line * head);




int main(void) {
    struct camera point;
    struct line dline;
    struct point funpoint;

    // 创建摄像头的点
    point_init(&point);
    point_create(&point);
    point_out(&point);

    // 线段方程的点
    funpoint_create(&funpoint);

    // 创建线段
    line_init(&dline);
    line_create(&dline);
    line_out(&dline);


    return 0;
}

void point_init(struct camera * c) {
    c -> id = 0;
    c -> pos = 0;
    c -> sum = 0;
    c -> resum = 0;
    c -> lineId = 0;
    c -> cameraId = 0;
    c -> isdelete = 0;
    c -> x = 0;
    c -> y = 0;
    c -> h = 0;
    c -> next = NULL;
    c -> prv = NULL;
}

void point_create(struct camera * head) {
    struct camera * tmp;
    int i, j, k = 0;
    for(i = 0; i < Y; i++) {
        for(j = 0; j < X; j++) {
            tmp = malloc (sizeof (struct camera));
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

void point_out(struct camera * head) {
    while (head) {
        printf("ID: %d \t x= %d \t y= %d\t h=%d\n", head->id, head->x, head->y, head->h);
        head = head -> next;
    }
}

float distance(struct point *p, struct point *q) {
    return sqrt((p->x - q->x) * (p->x - q->x) + (p->y - q->y) * (p->y - q->y));
}

void funpoint_create(struct point * head) {}
void funpoint_out(struct point * head) {}
void funpoint_init(struct point * head) {}

void line_create(struct line * head) {

}

void line_out(struct line * head) {

}

void line_init(struct line * head) {

}
