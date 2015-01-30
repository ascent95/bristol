#include <stdio.h>

struct circle
{
    double x, y, r;
};

struct box
{
    /*First coordinate is bottom left, second is top right*/
    double x1,y1,x2,y2;
};

typedef struct box box;
typedef struct circle circle;

circle toCircle(double x, double y, double r) 
{
    circle result;
    result.x = x;
    result.y = y;
    result.r = r;
    return result;
}

box bofc(circle in)
{
    box result;
    result.x1 = in.x - in.r;
    result.x2 = in.x + in.r;
    result.y1 = in.y - in.r;
    result.y2 = in.y + in.r;
    return result;
}

box bofb(box a, box b)
{
    box result;
    if(a.x1 < b.x1) {result.x1 = a.x1;}
    else {result.x1 = b.x1;}
    if(a.y1 < b.y1) {result.y1 = a.y1;}
    else {result.y1 = b.y1;}
    if(a.x2 > b.x2) {result.x2 = a.x2;}
    else {result.x2 = b.x2;}
    if(a.y2 > b.y2) {result.y2 = a.y2;}
    else {result.y2 = b.y2;}
    return result;
}

void printBox(box b)
{
    printf("(%f,%f) (%f,%f)\n",b.x1,b.y1,b.x2,b.y2);
}
int main(void) 
{
   circle a;
   circle b; 
   scanf("%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &a.r, &b.x, &b.y, &b.r);
   box c = bofc(a);
   box d = bofc(b);
   box combined = bofb(c,d);
   printBox(combined);
}
