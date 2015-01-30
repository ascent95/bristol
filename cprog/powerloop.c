#include <stdio.h>

double powerLoop(double x, int n) 
{
    double c = 1;
    int negative = 0;
    if (n < 0) negative = 1;

    while (n > 0) 
    {
        if (n % 2 == 0) /*Even case*/
        {
            c = powerIndian(x, n/2);
            return c*c;
        }
        else 
        {
            c *= x
            n--
        }
    }
}   

int main(void) 
{
    printf("£%.2f\n",1000 * powerIndian(1+5.0/100,25)); 
    printf("£%.2f\n",1000 * powerIndian(1+4.0/100,-12)); 
    printf("%f\n", powerIndian(1.0000000001,1000000000));
}
