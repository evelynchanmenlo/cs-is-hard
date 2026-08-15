// Cash by Evelyn Chan
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#define DOLLAR 1
#define QUARTERS 25
#define DIMES 10
#define NICKELS 5
#define PENNIES 1

int main(void)
{
    float change_owed;
    do
    {
        change_owed = get_float("Change owed: ");
    }
    // Prompts the user to keep trying until they input a number above zero.
    while (change_owed <= 0);
    // This converts the "cents" that the user inputs into a whole number, and rounds it up.
    change_owed = round(change_owed * 100);

    int count = 0;
    while (QUARTERS <= change_owed)
    {
        // For as many times you can use quarters, this decreases the amount by a quarter and
        // increases the count by 1
        change_owed = change_owed - QUARTERS;
        count = count + 1;
    }

    while (DIMES <= change_owed)
    {
        // The same goes for dimes
        change_owed = change_owed - DIMES;
        count = count + 1;
    }

    while (NICKELS <= change_owed)
    {
        // The same goes for nickels
        change_owed = change_owed - NICKELS;
        count = count + 1;
    }

    while (PENNIES <= change_owed)
    {
        // The same goes for pennies
        change_owed = change_owed - PENNIES;
        count = count + 1;
    }

    printf("Count:%i\n", count);
}
