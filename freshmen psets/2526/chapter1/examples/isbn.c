// ISBN by Evelyn
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get a long long from the user, assumes the input is 10 digits
    long long isbn = get_long_long("ISBN: ");

    // Initialize sum to 0
    long long sum = 0;
    int multiplier = 10;
    int last_digit;
    // While is still a number to process:
    while (isbn > 0)
    {
        // Multiply last digit by multiplier
        last_digit = isbn % 10;
        last_digit = last_digit * multiplier;
        sum = sum + last_digit;
        // Decrease the multiplier by 1
        multiplier--;
        // Chop off the last digit
        isbn = isbn / 10;
    }

    // if the sum is evenly divisible by 11, it is a valid isbn number
    if (sum % 11 == 0)
    {
        printf("YES\n");
    }
    // if it is not evenly divishble by 11, then it is not a valid isbn number
    else
    {
        printf("NO\n");
    }
}
