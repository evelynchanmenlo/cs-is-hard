// Pennies by Evelyn Chan
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#define MIN_DAYS 28
#define MAX_DAYS 31

int main(void)
{
    int days = 0;
    do
    {
        days = get_int("Days in month: ");
    }
    // Prompts user to keep trying until they type in a number that is between 28 and 31
    while (days < MIN_DAYS || days > MAX_DAYS);

    long long pennies = 0;
    do
    {
        pennies = get_long_long("Pennies on the first day: ");
    }
    // Prompts the user to keep trying until they type in a number greater than 0
    while (pennies < 1);

    long long total = 0;
    for (int i = 0; i < days; i++)
    {
        // This calculates the total amount of money after doubling the pennies each day
        total = total + pennies;
        pennies = pennies * 2;
    }
    // The printf statement converts that total value from dollars into pennies
    printf("$%0.2f\n", total / 100.00);
}
