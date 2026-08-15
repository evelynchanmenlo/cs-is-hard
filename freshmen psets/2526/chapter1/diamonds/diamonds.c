// Diamonds by Evelyn Chan
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#define MIN 1
#define MAX 20

int main(void)
{
    int size;
    do
    {
        // Prompts the user for input with restrictions
        size = get_int("Size: ");
    }
    while (size < MIN || size > MAX);

    int row;
    int stars = 1;
    // This is the formula to find the starting number of spaces
    int spaces = round((size - 1) / 2);
    // This loop creates the top half of the diamond
    for (row = 0; row < size / 2; row++)
    {
        // This calculates the number of spaces there are for each row
        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }
        // This calculates the number of stars there are for each row
        for (int j = 0; j < stars; j++)
        {
            printf("* ");
        }
        // This makes sure the amount of spaces decreases for each row
        spaces = spaces - 1;
        // This makes sure the amount of stars increases for each row
        stars = stars + 1;
        printf("\n");
    }

    // If the user input is odd, then it will add an extra row in between the top and bottom halves
    if (size % 2 == 1)
    {
        for (int i = 0; i < stars; i++)
        {
            printf("* ");
        }
        printf("\n");
        spaces = spaces + 1;
        stars = stars - 1;
    }
    // If the user input is odd, then it will just start making the bottom half
    else
    {
        spaces = spaces + 1;
        stars = stars - 1;
    }

    // This loop makes the bottom half of the diamond
    for (row = 0; row < size / 2; row++)
    {
        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }
        for (int j = 0; j < stars; j++)
        {
            printf("* ");
        }
        // This makes sure that the bottom is flipped from the top
        // So spaces increases each row
        spaces = spaces + 1;
        // Stars decreases each row
        stars = stars - 1;
        printf("\n");
    }
}
