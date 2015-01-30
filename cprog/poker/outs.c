#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cards
{
    unsigned long long int c : 52;
};

/*struct cards lcshift(struct cards x)
{
    x.c = (x.c << 13) | (x.c >> 39);
    return x;
}*/

/*void pair(struct cards *x) 
{
    struct cards y = *x;
    int i;
    for(i = 0; i < 4; i++)
    {
        if(i<3)
        {
            y.c = lcshift(y).c;
            x->c = x->c | y.c;
        }
        else
        {
            x->c = x->c ^ lcshift(y).c; 
        }   
    }  
}*/

int testNumber(struct cards *x, int i, int n) 
{
    if(n == 1 && (((x->c >> i) & 1) & ~((x->c >> (i+13)) & 1) & ~((x->c >> (i+26)) & 1) & ~((x->c >> (i+39)) & 1)) |
       (~((x->c >> i) & 1) & ((x->c >> (i+13)) & 1) & ~((x->c >> (i+26)) & 1) & ~((x->c >> (i+39)) & 1)) |
       (~((x->c >> i) & 1) & ~((x->c >> (i+13)) & 1) & ((x->c >> (i+26)) & 1) & ~((x->c >> (i+39)) & 1)) |
       (~((x->c >> i) & 1) & ~((x->c >> (i+13)) & 1) & ~((x->c >> (i+26)) & 1) & ((x->c >> (i+39)) & 1)))
    {
        return 1;
    }
    else if(n == 2 && (~((x->c >> i) & 1) & ~((x->c >> (i+13)) & 1) & ((x->c >> (i+26)) & 1) & ((x->c >> (i+39)) & 1)) |
       (~((x->c >> i) & 1) & ((x->c >> (i+13)) & 1) & ~((x->c >> (i+26)) & 1) & ((x->c >> (i+39)) & 1)) |
       (((x->c >> i) & 1) & ((x->c >> (i+13)) & 1) & ~((x->c >> (i+26)) & 1) & ~((x->c >> (i+39)) & 1)) |
       (((x->c >> i) & 1) & ~((x->c >> (i+13)) & 1) & ((x->c >> (i+26)) & 1) & ~((x->c >> (i+39)) & 1)))
    {
        return 1;
    }
    else if(n == 3 && (~((x->c >> i) & 1) & ((x->c >> (i+13)) & 1) & ((x->c >> (i+26)) & 1) & ((x->c >> (i+39)) & 1)) |
       (((x->c >> i) & 1) & ~((x->c >> (i+13)) & 1) & ((x->c >> (i+26)) & 1) & ((x->c >> (i+39)) & 1)) |
       (((x->c >> i) & 1) & ((x->c >> (i+13)) & 1) & ~((x->c >> (i+26)) & 1) & ((x->c >> (i+39)) & 1)) |
       (((x->c >> i) & 1) & ((x->c >> (i+13)) & 1) & ((x->c >> (i+26)) & 1) & ~((x->c >> (i+39)) & 1)))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

struct cards ttf(struct cards x, int n) /*stands for two, three, four of a kind*/
{
    if(n < 5 && n > 1) 
    {
        struct cards y = x;
        int i;
        for(i = 0; i < 13; i++)
        {
            if(testNumber(&y, i, n-1) == 1)
            {
                x.c = x.c | (0x0008004002001 << i) ;
            }
            
        }
        x.c = x.c ^ y.c;
    }
    else 
    {
        exit(EXIT_FAILURE);
    }
    return x;
    
}

const char *byte_to_binary(unsigned long long int x) /*From http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format*/
{
    static char b[65];
    b[0] = '\0';

    unsigned long long int z;
    for (z = 0x8000000000000; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

int main(void)
{
    struct cards myCards;
    myCards.c = 0x0110004002001;
    struct cards result;
    result.c = myCards.c;
    printf("|---Clubs---||-Diamonds--||--Hearts---||--Spades---|\n");
    printf("KQJt98765432AKQJt98765432AKQJt98765432AKQJt98765432A\n");
    printf("%s\n", byte_to_binary(myCards.c));
    result.c = ttf(myCards, 4).c | ttf(myCards, 3).c | ttf(myCards, 2).c;
    printf("%s\n", byte_to_binary(result.c));
}
