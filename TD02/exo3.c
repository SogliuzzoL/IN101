#include <stdio.h>
#include <math.h>

void affichage(int hauteur)
{
    for (int i = 1; i <= pow(2, hauteur); i ++)
    {
        if (i == pow(2, hauteur - 1) + 1)
        {
            printf("*");
        }
        else printf(" ");
    }
    printf("\n");
    for (int i = 0; i < hauteur - 1; i ++)
    {
        for (int j = 1; j <= pow(2, hauteur); j ++)
        {
            int diviseur = hauteur - i;
            if (j % diviseur == 0)
            {
                printf("*");
            }
            else printf(" ");
        }
        printf("\n");
    }
}

int main()
{
    affichage(3);
}