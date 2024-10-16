#include <stdio.h>
#include <stdlib.h>

int same_sum(int n, int c)
{
    int i = 1;
    int sum = c;
    while (sum <= n)
    {
        if (sum == n) return i;
        sum += c;
        i += 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    int c = atoi(argv[2]);
    int sum = same_sum(n, c);
    if (sum)
    {
        printf("%d est égal à une somme finie de %d. %d x %d = %d\n", n, c, c, sum, n);
    }
    else
    {
        printf("%d n'est pas égal à une somme finie de %d.\n", n, c);
    }
    return 0;
}