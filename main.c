#include "head.h"

const int max_side = 100;
const float min_side = 0.5;
const double pi = 3.1415926;
const int dotleng = 8;
float dot_x[1000];
float dot_y[1000];
const int K = 2; //构造折线
const int B1 = 1;
const int K2 = -1;
const int B2 = 136;

struct point pitem[100];
int p_total = 0;

void min_cube_init(struct cube *);
void cube_init(struct cube *cube);
void cube_dot(struct cube *cube);
void cube_link(struct cube *head, struct cube *cube);
void result_out(struct cube *head);
void curve_x(double *result, int step);
void curve_y(double *res, int step);
void fpWriteCoord(double x, int height); //Writes the intersection of the curve and the grid to a file
int fpReadCoord();                       //Reads the intersection of the curves in the file with the grid
void cube_search(struct cube *, float *, int, int, struct dot_in_cube *);
void camera_link(struct camera *c, float x, float y, int id);

void search_point_in_camera(struct point *, struct camera *);
void init_camera(struct camera *);
void camera_link(struct camera *c, float x, float y, int id);

struct cube *search(struct cube *head, int row, int column);
int circleANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct camera *c);
int LeftOvalANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct camera *c);
int RigthOvalANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct camera *c);
int judgement(int X0, int Y0, int h, struct camera * c, struct point * gp);
void search_gridpoint_in_camera(struct point *, struct camera *);
void output_gridpoint(struct point * head);
void grid_init(struct point * t);

int main(void)
{
    //struct cube head;
    //struct dot_in_cube result;
    // float dot_x[] = {21, 41, 61, 81, 101, 121, 141, 161, 181, 201};
    // float dot_y[] = {4.5, 9.5, 14.5, 19.5, 24.5, 29.5, 34.5, 39.5, 44.5, 49.5};
    struct point phead, grid_point;
    struct camera chead;
    struct camera *p;
    float x[] = {10, 20, 30, 40, 55, 65, 75, 89, 95, 100};
    float y[] = {20, 40, 60, 80, 80, 70, 60, 50, 40, 40};
    //    float x = 0.0;
    //    float y = 0.0;
    int i;
    int id = 1;
    int len = 10;
    // min_cube_init(&head);
    // circleIntersectionPoint(70,60,1);
    // fpWriteCoord(0, 10);
    // fpReadCoord( );
    // result_out( &head );
    // flag = 1  x, flag  =2 y.
    // cube_search( &head, dot_x, len, 1,  &result);
    // cube_search( &head, dot_y, len, 2,  &result);
    //circleANDLineIntersectionPoint(20,40,5,2,1);
    //LeftOvalANDLineIntersectionPoint( 20, 50, 3, 2,  1);
    chead.next = NULL;
    grid_point.next = NULL;
    chead.id = 0;
    for (i = 0; i < 10; i++)
    {
        camera_link(&chead, x[i], y[i], i + 1);
    }
    p = &chead;
    while (p->next)
    {
        // printf('%d\t', p->next->x);
        p = p->next;
    }
    search_point_in_camera(&phead, &chead);
    search_gridpoint_in_camera(&grid_point, &chead);
    return 0;
}

void min_cube_init(struct cube *head)
{
    int i, k, f;
    struct cube *p;
    int num = 0;
    double res[12] = {0};

    cube_init(head);
    // printf("head.id=%d\n", head.id);
    for (f = 0; f < max_side / min_side; f++)
    {
        for (i = 0; i < 100 / 10; i++)
        {
            for (k = 0; k < 100 / 10; k++)
            {
                num += 1;
                p = malloc(sizeof(struct cube));
                cube_init(p);
                // head->left = p;
                p->id = num;
                p->floor = f + 1;
                p->row = i + 1;
                p->column = k + 1;
                p->width = min_side;
                cube_dot(p);
                cube_link(head, p);
            }
        }
    }
}

void cube_init(struct cube *p)
{
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

void cube_dot(struct cube *c)
{
    int i = 0;
    int side_lenght = min_side;
    int row = c->row;
    int column = c->column;
    int floor = c->floor;
    c->height = min_side;

    for (; i < dotleng; i++)
    {
        c->dot[i].id = i;
        if (i == 0)
        {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 1)
        {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 2)
        {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 3)
        {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor - 1) * side_lenght;
        }
        if (i == 4)
        {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
        if (i == 5)
        {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = (column - 1) * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
        if (i == 6)
        {
            c->dot[i].x = row * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
        if (i == 7)
        {
            c->dot[i].x = (row - 1) * side_lenght;
            c->dot[i].y = column * side_lenght;
            c->dot[i].z = (floor)*side_lenght;
        }
    }
}

void cube_link(struct cube *h, struct cube *p)
{
    struct cube *tmpright = h;
    struct cube *tmptop = h->right;
    int i = 0;
    int dot = 0;
    while (tmpright->right)
    {
        tmpright = tmpright->right;
        if (0 == (tmpright->column % (int)min_side))
        {
            if (tmptop->top)
            {
                tmpright = tmptop->top;
                tmptop = tmptop->top;
            }
            else
            {
                dot = 1;
                tmpright = tmptop;
                break;
            }
        }
    }
    if (dot == 1)
    {
        tmpright->top = p;
        p->bottom = tmpright;
    }
    else
    {
        tmpright->right = p;
        p->left = tmpright;
        if (tmpright->row > 1)
        {
            tmpright->bottom->right->top = p;
            p->bottom = tmpright->bottom->right;
        }
    }
}

void result_out(struct cube *m)
{
    struct cube *h = m->right;
    struct cube *row = m->right->top;
    int i;
    FILE *fp;
    // fp=fopen("All vertex coordinates.txt","w");//打开文件
    //if ((fp=fopen("All vertex coordinates.txt","w"))==NULL) //判断文件是否能打开
    fp = fopen("All vertex coordinates1.txt", "w");               //打开文件
    if ((fp = fopen("All vertex coordinates1.txt", "w")) == NULL) //判断文件是否能打开
    {
        printf("fail to open the file!\n");
        exit(0);
    }

    while (h)
    {
        //printf("column: %d", h->column);
        if (!(h->column % (int)min_side))
        {
            // printf("\n\nid = %d\t floot = %d\t row = %d\t column = %d\t height = %d\n", h -> id, h -> floor, h -> row, h -> column, h -> height);
            printf("\tid = %d \n", h->id);
            //fprintf(fp,"%d", h -> id);
            for (i = 0; i < dotleng; i++)
            {
                // printf("dot->id = %d\t (x, y, z) =  (%d, %d, %d)\n", h->dot[i].id, h->dot[i].x, h->dot[i].y, h->dot[i].z);
                printf("dot->id = %d\t  (%f, %f, %fq)\n", h->dot[i].id, h->dot[i].x, h->dot[i].y, h->dot[i].z);
                //fprintf(fp,"\t(%d, %d, %d)\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
                fprintf(fp, "%f, %f, %f\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
            }
            if (!row)
            {
                return;
            }
            else
            {
                h = row;
                row = row->top;
            }
        }
        // printf("\n\nid = %d\t floot = %d\t row = %d\t column = %d\t height = %d\n", h -> id, h -> floor, h -> row, h -> column, h -> height);
        printf("\tid = %d \n", h->id);
        // fprintf(fp,"%d", h -> id);
        for (i = 0; i < dotleng; i++)
        {
            // printf("dot->id = %d\t (x, y, z) =  (%d, %d, %d)\n", h->dot[i].id, h->dot[i].x, h->dot[i].y, h->dot[i].z);
            printf("dot->id = %d\t  (%f, %f, %f)\n", h->dot[i].id, h->dot[i].x, h->dot[i].y, h->dot[i].z);
            // fprintf(fp,"\t(%d, %d, %d)\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
            fprintf(fp, "%f, %f, %f\n", h->dot[i].x, h->dot[i].y, h->dot[i].z);
        }
        h = h->right;
    }
    fclose(fp); //关闭文件
}

// void curve_x (double * result, int step) {
//     int x, i;
//     for (x = 0, i = 0; x <= max_side; x += step, i++) {
//         double y = sin(x * pi / 180) + 1;
//         result[i] = y;
//     }
// }

// void curve_y (double * res, int step) {
//     int y;
//     for(y = 0; y <= max_side; y += step){
//         // double y = sin(x * PI/180) +1;
//         double x = asin(y % 10);
//             printf("y = %d, x = %f\n", y, x);
//     }
// }

void cube_search(struct cube *head, float *coordinate, int len, int flag, struct dot_in_cube *res)
{
    int i = 1;
    int step_x = 0;
    int step_y = 0;
    struct cube *p;
    struct cube *h = head;

    printf("flag: %d\n", flag);
    for (; i <= len; i++)
    {
        if (*coordinate > max_side)
        {
            coordinate++;
            continue;
        }
        else
        {
            if (1 == flag)
            {
                step_x = i;
                if (step_x <= 1)
                {
                    step_x = 1;
                }
                step_y = (int)*coordinate / min_side + 1;
                p = search(head, step_x, step_y);
            }
            else
            {
                step_y = i;
                if (step_y <= 1)
                {
                    step_y = 1;
                }
                step_x = (int)*coordinate / min_side + 1;
                p = search(head, step_x, step_y);
            }
        }
        // if(flag == 1) {
        //     printf("(x, y) = P(%d, %f)  [%d, %d], id = %d row = %d, column = %d,", i* min_side, *coordinate, step_x, step_y, p->id, p->row, p->column);
        //     if(p->right)
        //     printf("\tnext.id = %d, next.row = %d next.column = %d\n",p->right->id, p->right->row, p->right->column);

        // } else {
        //     printf("(x, y) = P(%f, %d)  [%d, %d], id = %d row = %d, column = %d,", *coordinate, i * min_side, step_x, step_y, p->id, p->row, p->column);
        //     if(p->top)
        //     printf("\tnext.id = %d, next.row = %d next.column = %d\n", p->top->id, p->top->row, p->top->column);

        // }
        coordinate++;
    }
}

struct cube *search(struct cube *head, int column, int row)
{
    struct cube *tmp = head->right;
    while (tmp->row != row)
    {
        tmp = tmp->top;
    }
    while (tmp->column != column)
    {
        tmp = tmp->right;
    }
    return tmp;
}

void fpWriteCoord(double x, int height)
{
    double y;
    int i, j;

    //x1=x;
    FILE *fp, *fp1, *fp2, *fp3;
    fp = fopen("CoordinatesY.txt", "w");               //打开文件 //x是固定的边长，所以不写，只写了Y
    if ((fp = fopen("CoordinatesY.txt", "w")) == NULL) //判断文件是否能打开
    {
        printf("fail to open the file!\n");
        exit(0);
    }

    while (x <= 45 && y <= 91)
    {
        for (i = 0; i <= 100; i += height)
        {
            for (j = 0; j <= 100; j += height)
            {
                //  y = 10*sin(x*3.14/180);
                y = 2 * x + 1;
                //if ((y == j || y == i|| x == i|| x == j )&& x!=0)
                if ((x == i || x == j) && x != 0 && x <= 45 && y <= 91)
                //if (y == j || y == i|| x == i|| x == j )
                {
                    printf("The intersection point is :x= %lf ,y= %lf\n", x, y);
                    // dot_x[j]=y;
                    //fprintf(fp,"%lf %lf\n",x, y);
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

    while (x <= 91 && y <= 45)
    {
        for (i = 0; i <= 100; i += height)
        {
            for (j = 0; j <= 100; j += height)
            {
                //  y = 10*sin(x*3.14/180);
                y = (x - 1) / 2; //反函数
                //if ((y == j || y == i|| x == i|| x == j )&& x!=0)
                if ((x == i) || (x == j && x != 0 && x <= 91 && y <= 45))
                //if (y == j || y == i|| x == i|| x == j )
                {
                    printf("The intersection point is :x= %lf ,y= %lf\n", y, x); //横纵坐标换一下输出
                                                                                 //dot_y[j]=x;
                                                                                 //fprintf(fp,"%lf %lf\n",y,x);
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
    while (x <= 100 && y <= 91)
    {
        for (i = 0; i <= 100; i += height)
        {
            for (j = 0; j <= 100; j += height)
            {
                //  y = 10*sin(x*3.14/180);
                y = -1 * x + 136;
                //if ((y == j || y == i|| x == i|| x == j )&& x!=0)
                if ((x == i) || (x == j && x != 0 && x <= 100 && y <= 91))
                //if (y == j || y == i|| x == i|| x == j )
                {
                    printf("The intersection point is :x= %lf ,y= %lf\n", x, y);
                    // dot_x[j]=y;
                    //fprintf(fp,"%lf %lf\n",x, y);
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
    while (x <= 91 && y <= 100)
    {
        for (i = 0; i <= 100; i += height)
        {
            for (j = 0; j <= 100; j += height)
            {
                //  y = 10*sin(x*3.14/180);
                y = -x + 136;
                //if ((y == j || y == i|| x == i|| x == j )&& x!=0)
                if ((x == i || x == j) && (x != 0 && x <= 91 && y <= 100))
                {
                    printf("The intersection point is :x= %lf ,y= %lf\n", y, x);
                    // dot_x[j]=y;
                    //fprintf(fp,"%lf %lf\n",x, y);
                    fprintf(fp2, "%lf %lf\n", y, x);
                    break;
                }
            }
            x = x + 1;
        }
    }
    fclose(fp3); //关闭文件
}
int fpReadCoord()
{

    int i = 0;
    FILE *fp, *fp1;

    fp = fopen("CoordinatesY.txt", "r");
    if (!fp)
    {
        printf("open file error\n");
        return -1;
    }

    while (!feof(fp))
    {
        if (fscanf(fp, "%f", &dot_x[i]) != 1.0)
            break;
        //  fscanf( fp , "%lf" ,&dot_x[i]);
        printf("%f\n", dot_x[i]);
        i++;
        //getchar() ;//过滤掉分隔符
    }
    fclose(fp);
    printf("aaa");

    fp1 = fopen("CoordinatesX.txt", "r");
    if (!fp1)
    {
        printf("open file error\n");
        return -1;
    }
    while (!feof(fp1))
    {
        if (fscanf(fp1, "%f", &dot_y[i]) != 1.0)
            break;
        printf("%f\n", dot_y[i]);
        i++;
        //fgetc(fp) ;//过滤掉分隔符
    }
    fclose(fp1);

    return 1;
}

int circleANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct camera *c)
{
    double x1, y1, x2, y2;
    int r = h / sqrt(3);
    double tem[4];
    int k, b;
    int flag = 0; //if or not has a IntersectionPoint
    if (f)
    {
        k = -1;
        b = 136;
    }
    else
    {
        k = 2;
        b = 1;
    }
    if (X0 <= 100)
    {

        x1 = (2 * X0 + 2 * k * Y0 - 2 * k * b + sqrt((2 * k * b - 2 * X0 - 2 * k * Y0) * (2 * k * b - 2 * X0 - 2 * k * Y0) - 4 * (k * k + 1) * (X0 * X0 + Y0 * Y0 + b * b - 2 * b * Y0 - r * r))) / (2 * (k * k + 1));
        y1 = k * x1 + b;
        x2 = (2 * X0 + 2 * k * Y0 - 2 * k * b - sqrt((2 * k * b - 2 * X0 - 2 * k * Y0) * (2 * k * b - 2 * X0 - 2 * k * Y0) - 4 * (k * k + 1) * (X0 * X0 + Y0 * Y0 + b * b - 2 * b * Y0 - r * r))) / (2 * (k * k + 1));
        y2 = k * x2 + b;
        tem[0] = x1;
        tem[1] = y1;
        tem[2] = x2;
        tem[3] = y2;
        if (x1 >= 0 && x1 <= 100)
        {
            flag = 1;
            // printf("x1=%lf,y1=%gcc mlf,x2=%lf,y2=%lf\n", x1, y1, x2, y2);

            c->select[1] = 1;
            c->point[1][0] = x1;
            c->point[1][1] = y1;
            c->point[1][2] = x2;
            c->point[1][3] = y2;

            pitem[p_total].x = x1;
            pitem[p_total].y = y1;
            pitem[p_total].total = 1;
            pitem[p_total].cinfo[pitem[p_total].total - 1].pos = 1;
            pitem[p_total].cinfo[pitem[p_total].total - 1].ca = *c;
            p_total += 1;

            pitem[p_total].x = x2;
            pitem[p_total].y = y2;
            pitem[p_total].total = 1;
            pitem[p_total].cinfo[pitem[p_total].total - 1].pos = 1;
            pitem[p_total].cinfo[pitem[p_total].total - 1].ca = *c;
            p_total += 1;
        }
    }
    if (flag == 0)
    {
        // printf("NO IntersectionPoint\n");
    }

    return 1;
}

int LeftOvalANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct camera *c) //Coordinates of the intersection of an ellipse and a line
{
    double x1, y1, x2, y2;
    float tem[4];
    int k, b;
    int flag = 0; //if or not has a IntersectionPoint
    if (f)
    {
        k = -1;
        b = 136;
    }
    else
    {
        k = 2;
        b = 1;
    }
    if (X0 <= 100)
    {
        if ((2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) * (2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) - 4 * (12 * k * k + 3) * (3 * X0 * X0 + 12 * Y0 * Y0 + 12 * b * b - 24 * b * Y0 - 2 * sqrt(3) * X0 * h - 3 * h * h) >= 0)
        {
            x1 = (6 * X0 + 24 * k * Y0 - 2 * sqrt(3) * h - 24 * k * b + sqrt((2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) * (2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) - 4 * (12 * k * k + 3) * (3 * X0 * X0 + 12 * Y0 * Y0 + 12 * b * b - 24 * b * Y0 - 2 * sqrt(3) * X0 * h - 3 * h * h))) / (24 * k * k + 6);
            y1 = k * x1 + b;
            x2 = (6 * X0 + 24 * k * Y0 - 2 * sqrt(3) * h - 24 * k * b - sqrt((2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) * (2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) - 4 * (12 * k * k + 3) * (3 * X0 * X0 + 12 * Y0 * Y0 + 12 * b * b - 24 * b * Y0 - 2 * sqrt(3) * X0 * h - 3 * h * h))) / (24 * k * k + 6);
            y2 = k * x2 + b;

            tem[0] = x1;
            tem[1] = y1;
            tem[2] = x2;
            tem[3] = y2;
            printf("x0 =%f, y0 = %f\t x1=%lf,y1=%lf,x2=%lf,y2=%lf\n", X0, Y0, x1, y1, x2, y2);
            if (x1 <= 100 && x1 >= 0)
            {
                c->select[0] = 1;
                c->point[0][0] = x1;
                c->point[0][1] = y1;
                c->point[0][2] = x2;
                c->point[0][3] = y2;

                pitem[p_total].x = x1;
                pitem[p_total].y = y1;
                pitem[p_total].total = 1;
                pitem[p_total].cinfo[pitem[p_total].total - 1].pos = 0;
                pitem[p_total].cinfo[pitem[p_total].total - 1].ca = *c;
                p_total += 1;

                pitem[p_total].x = x2;
                pitem[p_total].y = y2;
                pitem[p_total].total = 1;
                pitem[p_total].cinfo[pitem[p_total].total - 1].pos = 0;
                pitem[p_total].cinfo[pitem[p_total].total - 1].ca = *c;
                p_total += 1;

                flag = 1;
            }
        }
    }

    if (flag == 0)
    {
        // printf("NO IntersectionPoint! \n");
        // printf("LeftOvalANDLineIntersectionPoint: NO IntersectionPoint! \n");
    }
    return 1;
}

int RigthOvalANDLineIntersectionPoint(float X0, float Y0, int h, int f, struct camera *c) //Coordinates of the intersection of an ellipse and a line
{
    double x1, y1, x2, y2;
    double tem[4];
    int k, b;
    int flag = 0; //if or not has a IntersectionPoint
    if (f)
    {
        k = -1;
        b = 136;
    }
    else
    {
        k = 2;
        b = 1;
    }
    if (X0 <= 100)
    {
        if ((-2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) * (-2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) - 4 * (12 * k * k + 3) * (3 * X0 * X0 + 12 * Y0 * Y0 + 12 * b * b - 24 * b * Y0 + 2 * sqrt(3) * X0 * h - 3 * h * h) >= 0)
        {
            x1 = (6 * X0 + 24 * k * Y0 + 2 * sqrt(3) * h - 24 * k * b + sqrt((-2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) * (-2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) - 4 * (12 * k * k + 3) * (3 * X0 * X0 + 12 * Y0 * Y0 + 12 * b * b - 24 * b * Y0 + 2 * sqrt(3) * X0 * h - 3 * h * h))) / (24 * k * k + 6);
            y1 = k * x1 + b;
            x2 = (6 * X0 + 24 * k * Y0 + 2 * sqrt(3) * h - 24 * k * b - sqrt((-2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) * (-2 * sqrt(3) * h - 6 * X0 + 24 * k * b - 24 * k * Y0) - 4 * (12 * k * k + 3) * (3 * X0 * X0 + 12 * Y0 * Y0 + 12 * b * b - 24 * b * Y0 + 2 * sqrt(3) * X0 * h - 3 * h * h))) / (24 * k * k + 6);
            y2 = k * x2 + b;
            tem[0] = x1;
            tem[1] = y1;
            tem[2] = x2;
            tem[3] = y2;
            printf("x0 =%f, y0 = %f\t x1=%lf,y1=%lf,x2=%lf,y2=%lf\n", X0, Y0, x1, y1, x2, y2);
            if (x1 <= 100 && x1 >= 0)
            {
                // printf("x1=%lf,y1=%lf,x2=%lf,y2=%lf\n", x1, y1, x2, y2);
                c->select[2] = 1;
                c->point[2][0] = x1;
                c->point[2][1] = y1;
                c->point[2][2] = x2;
                c->point[2][3] = y2;

                pitem[p_total].x = x1;
                pitem[p_total].y = y1;
                pitem[p_total].total = 1;
                pitem[p_total].cinfo[pitem[p_total].total - 1].pos = 2;
                pitem[p_total].cinfo[pitem[p_total].total - 1].ca = *c;
                p_total += 1;

                pitem[p_total].x = x2;
                pitem[p_total].y = y2;
                pitem[p_total].total = 1;
                pitem[p_total].cinfo[pitem[p_total].total - 1].pos = 2;
                pitem[p_total].cinfo[pitem[p_total].total - 1].ca = *c;
                p_total += 1;

                flag = 1;
            }
        }
      
    }
    if (flag == 0)
    {
        // printf("LeftOvalANDLineIntersectionPoint: NO IntersectionPoint! \n");
    }
    return 1;
}

// int CameraGearSelection(int ID,int number){
//     switch (number)
//     {
//     case 1:
//         printf("left Oval\n");
//         LeftOvalANDLineIntersectionPoint(20, 50, 3, 2, 1);

//         break;
//     case 2:
//         printf("circle\n");
//         circleANDLineIntersectionPoint(20, 40, 5, 2, 1);
//         break;
//     case 3:
//         printf("right Oval\n");
//         RigthOvalANDLineIntersectionPoint(20, 50, 3, 2, 1);
//         break;
//     default:
//         printf("NO IntersectionPoint! \n");
//         break;
//     }
// }

void init_camera(struct camera *c)
{
    int i, j;
    int pos = 3;
    int coord = 4;
    for (i = 0; i < pos; i++)
    {
        for (j = 0; j < coord; j++)
        {
            if (i == 0 && j < pos)
            {
                c->select[i] = 0;
            }
            c->point[i][j] = 0;
        }
    }
    c->next = NULL;
}

void camera_link(struct camera *c, float x, float y, int id)
{
    struct camera *tmp;
    tmp = malloc(sizeof(struct camera));
    init_camera(tmp);
    while (c->next)
    {
        c = c->next;
    }
    c->next = tmp;
    tmp->x = x;
    tmp->y = y;
    tmp->id = id;
}

void search_point_in_camera(struct point *p, struct camera *e)
{
    struct camera *c = e->next;
    int x = c->x;
    int y = c->y;
    int i, j;

    while (c)
    {
        x = c->x;
        y = c->y;
        LeftOvalANDLineIntersectionPoint(x, y, 3, 0, c);
        LeftOvalANDLineIntersectionPoint(x, y, 3, 1, c);
        RigthOvalANDLineIntersectionPoint(x, y, 3, 0, c);
        RigthOvalANDLineIntersectionPoint(x, y, 3, 1, c);
        circleANDLineIntersectionPoint(x, y, 3, 0, c);
        circleANDLineIntersectionPoint(x, y, 3, 1, c);
        c = c->next;
    }

    for (i = 0; i < p_total; i++)
    {
        // for(j = 0; j < 3; j++) {
        //     if(pitem[i].cinfo[pitem[i].total - 1].ca.selecg[j])
        //     printf("select = %d\t", j);
        // }
        printf("select = %d   x = %f, y = %f, \t camera.x = %f camera.y = %f\n", pitem[i].cinfo[pitem[i].total - 1].pos, pitem[i].x, pitem[i].y, pitem[i].cinfo[pitem[i].total - 1].ca.x, pitem[i].cinfo[pitem[i].total - 1].ca.y);
    }
}

int judgement(int X0, int Y0, int h, struct camera * c, struct point * gp)
{

    int r = h / sqrt(3);
    struct point * tmp;
    int ret = 0;
    float x[2][25] = {4.500000, 9.500000, 14.500000, 19.500000, 24.500000, 29.500000, 34.500000, 39.500000, 44.500000, 96.000000, 86.000000, 76.000000, 66.000000, 56.000000, 46.000000, 10.000000, 20.000000, 30.000000, 40.000000, 50.000000, 60.000000, 70.000000, 80.000000, 90.000000, 100.000000, 10.000000, 20.000000, 30.000000, 40.000000, 50.000000, 60.000000, 70.000000, 80.000000, 90.000000, 40.000000, 50.000000, 60.000000, 70.000000, 80.000000, 90.000000, 21.000000, 41.000000, 61.000000, 81.000000, 86.000000, 76.000000, 66.000000, 56.000000, 46.000000, 36.000000};
    int i;

    for (i = 0; i < 25; i++)
    {
        if (x[0][i] <= X0 + r && x[0][i] >= X0 - r && x[1][i] <= Y0 + r && x[1][i] >= Y0 - r) {
            printf("the (%f, %f) is in the circle\n", x[0][i], x[1][i]);

            if(gp->total == 3) {
            tmp = malloc(sizeof(struct point));
            gp->next = tmp;
            gp = gp->next;
        }
                gp->x = x[0][i];
                gp->y = x[1][i];
                gp->total += 1;
                gp->cinfo[gp->total - 1].pos = 1;
                gp->cinfo[gp->total - 1].ca = *c;
                ret =  1;
        }

        if ((3 * (x[0][i] - X0 + h / sqrt(3)) * (x[0][i] - X0 + h / sqrt(3))) / (4 * h * h) + (3 * (x[1][i] - Y0) * (x[1][i] - Y0)) / (h * h) <= 1)
        {
            printf("the (%f, %f) is in the leftOval\n", x[0][i], x[1][i]);
                gp->x = x[0][i];
                gp->y = x[1][i];
                gp->total += 1;
                gp->cinfo[gp->total - 1].pos = 0;
                gp->cinfo[gp->total - 1].ca = *c;
                ret =  1;
        }

        if ((3 * (x[0][i] - X0 - h / sqrt(3)) * (x[0][i] - X0 + h / sqrt(3))) / (4 * h * h) + (3 * (x[1][i] - Y0) * (x[1][i] - Y0)) / (h * h) <= 1)
        {
            printf("the (%f, %f) is in the rightOval\n", x[0][i], x[1][i]);
                gp->x = x[0][i];
                gp->y = x[1][i];
                gp->total += 1;
                gp->cinfo[gp->total - 1].pos = 2;
                gp->cinfo[gp->total - 1].ca = *c;
                ret =  1;
        }
        
    }
    return ret;
}
void grid_init(struct point * t) {
    t->total = 0;
    t->x = -1.0;
    t->y = -1.0;
}

void output_gridpoint(struct point * head){
    struct point *g = head->next;
    int i;
    while(g) {
        
        printf("grid x = %f, y = %f, total = %d, next = %p\n", g->x, g->y, g->total, g->next);
        for(i = 0; i < g->total; i++) {
            printf("\ttotal = %d select = %d camera ID = %d\n ", i, g->cinfo[i].pos, g->cinfo[i].ca.id);
        }
        printf("\n");
        g = g->next;
    }

}

void search_gridpoint_in_camera(struct point * gp, struct camera * cp) {
    struct camera *c = cp->next;
    struct point * gtmp;
    struct point * htmp = gp;
    int x = c->x;
    int y = c->y;
    int ret;
    while (c) {
        gtmp = malloc(sizeof(struct point));
        grid_init(gtmp);
        x = c->x;
        y = c->y;
        ret = judgement(x, y, 3, c, gtmp);
        if(ret) {
            while(gp->next) {
                gp = gp->next;
            } 
            gp->next = gtmp;
        } else {
            free(gtmp);
        }
        c = c->next;
    }
    output_gridpoint(htmp);
}


