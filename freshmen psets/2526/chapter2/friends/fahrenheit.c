// Chill Out by Evelyn Chan
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("ERROR\n");
        return 1;
    }
    float celsius = atof(argv[1]);
    printf("F: %.1f\n", celsius * 1.8 + 32);
}
