#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void division(int a, int b, int n)
{
    if (n < 0) 
    {
        printf("n doit être positif");
        return;
    }
    if (b == 0)
    {
        printf("b doit être non nul");
        return;
    }
    for (int i = 0; i <= n; i++)
    {
        int multi = a / b;
        if (i != 0)
        {
            if (multi < 0)
            {
                printf("%d", -multi);
            }
            else printf("%d", multi);
        }
        else printf("%d", multi);        
        if (a % b == 0)
        {
            break;
        }
        if (i == 0)
        {
            printf(",");
        }
        
        a %= b;
        a *= 10;
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    if (argc != 4) 
    {
        printf("a: int, b: int, n: int");
        return -1;
    }
    division(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
}