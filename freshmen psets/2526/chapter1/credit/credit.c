// Credit by Evelyn Chan
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#define AMEX_LENGTH 15
#define AMEX_START_NUM 34
#define OTHER_AMEX_START_NUM 37
#define MASTERCARD_LENGTH 16
#define MIN_MASTER_START_NUM 51
#define MAX_MASTER_START_NUM 55
#define VISA_LENGTH 13
#define OTHER_VISA_LENGTH 16
#define VISA_START_NUM 4

int main(void)
{
    long long number = get_long_long("Number: ");

    // The variable, cred_number, stays the same throughout the problem set; this is used to reset
    // number every time
    long long cred_number = number;
    int check_sum = 0;
    int doubled_number = 0;
    int sum = 0;
    while (number > 0)
    {
        // This makes sure that every other number is doubled and added to the sum.
        check_sum += number % 10;
        number = number / 10;
        doubled_number = (number % 10) * 2;

        // If the doubled number is a single digit number, then you just add it to the sum.
        if (doubled_number <= 9)
        {
            check_sum += doubled_number;
        }
        // However, if it contains two digits, then you take each of the digits and add them
        // together.
        else
        {
            sum = 0;
            sum += doubled_number % 10;
            doubled_number = doubled_number / 10;
            sum += doubled_number;
            check_sum += sum;
        }
        // Chops it off so the process repeats while the number is greater than 0.
        number = number / 10;
    }

    // This resets the number to the original (instead of what it currently is, 0) so we can keep
    // using it.
    number = cred_number;
    int num_of_digits = 0;
    int length = 0;
    // Must pass Luhn's algorithm
    if (check_sum % 10 == 0)
    {
        while (number > 0)
        {
            // This calculates the amount of digits there are in the number.
            number = number / 10;
            num_of_digits++;
        }

        // The number resets to what the user orignally inputs.
        number = cred_number;
        // This calculates and gets what the first two digits are in the number.
        length = number / pow(10, num_of_digits - 2);

        // Setting the conditions for it to be an AMEX card.
        if (num_of_digits == AMEX_LENGTH &&
            (length == AMEX_START_NUM || length == OTHER_AMEX_START_NUM))
        {
            printf("AMEX\n");
        }
        else
        {
            // If the number doesn't fulfill AMEX conditions, it checks to see if it fulfills the
            // MASTERCARD conditions.
            if (num_of_digits == MASTERCARD_LENGTH &&
                (length >= MIN_MASTER_START_NUM && length <= MAX_MASTER_START_NUM))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                // If the number doesn't fulfill MASTERCARD conditions, it chekcs to see if it
                // fulfills VISA conditions.
                if ((num_of_digits == VISA_LENGTH || num_of_digits == OTHER_VISA_LENGTH) &&
                    (length / 10 == VISA_START_NUM))
                {
                    printf("VISA\n");
                }
                else
                {
                    // If it doesn't fulfills any conditions, it is an invalid card.
                    printf("INVALID\n");
                }
            }
        }
    }
    else
    {
        // If the number does not pass Luhn's algorithm, it is invalid.
        printf("INVALID\n");
    }
}
