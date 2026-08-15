// Makin' Bank by Evelyn Chan
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 31
#define MIN_DAYS 28

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("ERROR\n");
        return 1;
    }

    float days = atof(argv[1]);
    if (days < MIN_DAYS || days > MAX_DAYS)
    {
        printf("ERROR\n");
        return 1;
    }

    int pennies = atoi(argv[2]);
    if (pennies <= 0)
    {
        printf("ERROR\n");
        return 1;
    }

    long long total = pennies;

    for (int i = 1; i < days; i++)
    {
        total += pennies * pow(2, i);
    }

    printf("$%.2f\n", ((double) total) / 100);
}
