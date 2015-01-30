#include <stdio.h>

double powerIndian(double x, int n) 
{
    double c;
    if (n < 0)
    {
        return 1.0/powerIndian(x,-n);
    }
    if (n == 0) 
    {
        return 1;
    }
    else if (n % 2 == 0) 
    {
        c = powerIndian(x, n/2);
        return c*c;
    }
    else 
    {
        return x * powerIndian(x, n-1);
    }
}   

int main(void) 
{
    printf("£%.2f\n",1000 * powerIndian(1+5.0/100,25)); 
    printf("£%.2f\n",1000 * powerIndian(1+4.0/100,-12)); 
    printf("%f\n", powerIndian(1.0000000001,1000000000));
}
