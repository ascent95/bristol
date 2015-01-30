#include <stdio.h>

typedef struct circle
{
    int x, y, r;
} circle;

typedef struct line
{
    int x1,y1,x2,y2;
} line;

typedef struct box
{
    /*First coordinate is bottom left, second is top right*/
    int x1,y1,x2,y2,null;
} box;

typedef enum { IsLine, IsCircle } ShapeTag;

typedef struct shape
{
    ShapeTag tag;
    union 
    {
        line l;
        circle c;
    } s;
} shape;

circle toCircle(int x, int y, int r) 
{
    circle result;
    result.x = x;
    result.y = y;
    result.r = r;
    return result;
}

box bofshp(shape in)
{
    box result;
    result.null = 0;
    if(in.tag == IsCircle)
    {
        result.x1 = in.s.c.x - in.s.c.r;
        result.x2 = in.s.c.x + in.s.c.r;
        result.y1 = in.s.c.y - in.s.c.r;
        result.y2 = in.s.c.y + in.s.c.r;
    }
    else if(in.tag == IsLine)
    {
        result.x1 = in.s.l.x1;
        result.y1 = in.s.l.y1;
        result.x2 = in.s.l.x2;
        result.y2 = in.s.l.y2;
    }
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
    printf("(%d,%d) (%d,%d)\n",b.x1,b.y1,b.x2,b.y2);
}

int main(void) 
{
    char coords[256];
    box bbox;
    bbox.null = 1;
    shape shp;
    if(fgets(coords, 256, stdin) == NULL)
    {
       return 1; 
    }
    else
    {
        int i,j;
	    while(i<256 && coords[i] !='\0')
        {
            
            if(coords[i] == 'L')
            {
                for(j=0;j<10;j++)
                {
                    if(j == 2) {shp.s.l.x1 = coords[i+j] - '0';}
                    if(j == 4) {shp.s.l.y1 = coords[i+j] - '0';}
                    if(j == 6) {shp.s.l.x2 = coords[i+j] - '0';}
                    if(j == 8) {shp.s.l.y2 = coords[i+j] - '0';}
                    else {continue;}
                }
                shp.tag = IsLine;
                i += 10;
            }
            else if(coords[i] == 'C') 
            {
                for(j=0;j<8;j++)
                {
                    if(j == 2) {shp.s.c.x = coords[i+j] - '0';}
                    if(j == 4) {shp.s.c.y = coords[i+j] - '0';}
                    if(j == 6) {shp.s.c.r = coords[i+j] - '0';}
                    else {continue;}
                }
                shp.tag = IsCircle;
                i += 8;
            }
            else
            {
                i++;
                continue;
            }
            if(bbox.null == 1) 
            {
                bbox = bofshp(shp);
                bbox.null = 0;
            }
            else {bbox = bofb(bbox, bofshp(shp));}         
        }
    }
    printBox(bbox);
}
