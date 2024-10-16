#include <stdio.h>
#include <stdlib.h>

int sum(int x, int y)
{
    int somme = 0;
    for (int i = x; i <= y; i++)
    {
        if (i % 5 == 0 && i % 2) somme += i;
    }
    return somme;
}

int main(int argc, char* argv[])
{
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    int somme = sum(x, y);
    printf("La somme est de %d.\n", somme);
    return 0;
}