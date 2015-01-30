#include <stdio.h>

double power(double x, int y) 
{
    double current = 1;
    /*printf("Current initialised to: %f\n", current);*/
    if (y < 0) 
    {
        printf("you have passed in a negative exponent!");
        return 0;
    }
    for (;y > 0; y--)
    {
        current *= x;
    }
    return current;
}

int main(void)
{
    printf("£%.2f\n",1000 * power(1+5.0/100,25)); 
    return 0;
}       
