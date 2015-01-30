#include <stdio.h>

struct circle
{
    int x,y,r;
};

struct box
{
    /*First coordinate is bottom left, second is top right*/
    int x1,y1,x2,y2;
};

typedef struct box box;
typedef struct circle circle;

circle toCircle(int x, int y, int r) 
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

void printBox(box b)
{
    printf("(%d,%d) (%d,%d)\n",b.x1,b.y1,b.x2,b.y2);
}
int main(void) 
{
   circle c = toCircle(1,2,3);
   box b = bofc(c);
   printBox(b); 
}
