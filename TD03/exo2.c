#include <stdio.h>
#include <stdlib.h>

int move_bishop(int xi, int yi, int xf, int yf)
{
    if(xi >= 0 && xi < 8 && yi >= 0 && yi < 8 && xf >= 0 && xf < 8 && yf >= 0 && yf < 8)
    {
        if (xi == xf)
        {
            return 0;
        }
        
        return abs(xi - xf) == abs(yi - yf);
    }
    else return 0;
}

int main(int argc, char* argv[])
{
    int xi = atoi(argv[1]);
    int yi = atoi(argv[2]);
    int xf = atoi(argv[3]);
    int yf = atoi(argv[4]);

    printf("%d\n", move_bishop(xi, yi, xf, yf));
}