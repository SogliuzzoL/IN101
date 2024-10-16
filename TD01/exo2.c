#include <stdio.h>
#include <stdlib.h>

double poly(double x)
{
    double result = 5.0 - 2.0 * x + 5.0 * x * x * x - 3.0 * x * x * x * x;
    return result;
}

int main(int argc, char* argv[])
{
    double x = atof(argv[1]);
    printf("f(%.2f) = %.2f\n", x, poly(x));
    return 0;
}
