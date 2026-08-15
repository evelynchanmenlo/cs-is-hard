// Mario by Evelyn Chan
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    int spaces = height;
    for (int row = 1; row <= height; row++)
    {
        for (int j = 0; j < spaces - row; j++)
        {
            printf(" ");
        }
        for (int hashes = 1; hashes <= row; hashes++)
        {
            printf("#");
        }
        printf("  ");
        for (int hashes = 1; hashes <= row; hashes++)
        {
            printf("#");
        }
        printf("\n");
    }
}
