#include <stdio.h>

double power(double x, int y) 
{
    double current = 1;
    /*printf("Current initialised to: %f\n", current);*/
    if (y >= 0) 
    {
        for (;y > 0; y--)
        {
            current *= x;
        }
        return current;
    }
    else 
    {
        for (;y < 0; y++)
        {
            current *= x;
        }
        return 1.0/current;
    }
    
}

int main(void)
{
    printf("£%.2f\n",1000 * power(1+5.0/100,25)); 
    printf("£%.2f\n",1000 * power(1+4.0/100,-12)); 
    /*printf("%f\n",power(1.0000000001,1000000000));*/
    return 0;
}       
