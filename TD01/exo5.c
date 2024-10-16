#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int changed_digit(char* chaine)
{
    int n = atoi(chaine);
    int i = 0;
    while (!(n / pow(10, i) < 10 && n / pow(10, i) > -10))
    {
        i ++;
    }
    int div = pow(10, i);
    if ((n + 1) % div == 0 && n > 0) return 1;
    if (n % div == 0 && n < 0) return 1;
    if (n == 0) return 1;
    return 0;
}

int main(int argc, char* argv[])
{
    int changed = changed_digit(argv[1]);
    if (changed)
    {
        printf("%s va changer de chiffre de poids le plus fort.\n", argv[1]);
    }
    else
    {
        printf("%s ne va pas changer de chiffre de poids le plus fort.\n", argv[1]);
    }
}