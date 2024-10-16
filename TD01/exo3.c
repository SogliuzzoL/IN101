#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int col(double xA, double yA, double xB, double yB, double xC, double yC)
{
    double det = (xB - xA) * (yC - yA) - (yB - yA) * (xC - xA);
    double erreur = 0.0001;
    if (det <= erreur && det >= (-1.0) * erreur)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    double x = 13.1;
    double y = sqrt(x);;
    int colineaire = col(1, 1, y * y, x, 5, 5);
    if (colineaire)
    {
        printf("Les trois points sont alignés\n");
    }
    else
    {
        printf("Les trois points ne sont pas alignés\n");
    }

    return 0;
}