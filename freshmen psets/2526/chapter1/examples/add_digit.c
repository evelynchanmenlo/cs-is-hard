// Add Digits by Evelyn Chan
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number = get_int("Enter a non-negative integer: ");

    int last_digit;
    while (number > 0)
    {
      last_digit = number % 10;
      last_digit = number / 10;

    }

    printf("%d\n", number);

}
