#include <stdio.h>

int main(void)
{
    char name[20], number[20];
    while(scanf("%s %s", name, number))
    {
        printf("The name is %s and my number is %s\n", name, number);
    }
}
