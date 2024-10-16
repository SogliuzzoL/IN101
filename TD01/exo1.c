#include <stdio.h>
#include <stdlib.h>

char nth(char* chaine, int position)
{
    int i = 0;
    while(chaine[i] != 0)
    {
        if (position == i)
        {
            // printf("%c\n", chaine[position]);
            return chaine[position];
        }
        i ++;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    char c = nth(argv[1], atoi(argv[2]));
    printf("Le caractère en position %d de %s est %c\n", atoi(argv[2]), argv[1], c);

    return 0;
}
