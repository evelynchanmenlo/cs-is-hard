// Calc by Evelyn Chan
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // If the user doesn't add enough words in their input, it will print an error message
    if (argc != 4)
    {
        printf("Usage: ./calc <number> <operator> <number>\n");
        return 1;
    }
    // If the user doesn't have two variables and a mathmatical operator in the input, it will print
    // an error message
    if (strcmp(argv[2], "+") != 0 && strcmp(argv[2], "-") != 0 && strcmp(argv[2], "x") != 0 &&
        strcmp(argv[2], "/") != 0 && strcmp(argv[2], "%") != 0)
    {
        printf("Usage: ./calc <number> <operator> <number>\n");
        return 1;
    }

    // This turns each of the strings into float variables
    float num1 = atof(argv[1]);
    float operator = atof(argv[2]);
    float num2 = atof(argv[3]);

    float end_product;
    // If the input includes the addition symbol (+), then it will do addition
    if (strcmp(argv[2], "+") == 0)
    {
        end_product = num1 + num2;
        printf("%f\n", end_product);
    }
    // If the input includes the subtraction symbol (-), then it will do subtraction
    else if (strcmp(argv[2], "-") == 0)
    {
        end_product = num1 - num2;
        printf("%f\n", end_product);
    }
    // If the input includes the multiplication symbol (x), then it will do multiplication
    else if (strcmp(argv[2], "x") == 0)
    {
        end_product = num1 * num2;
        printf("%f\n", end_product);
    }
    // If the input includes the division symbol (/), it will do division
    else if (strcmp(argv[2], "/") == 0)
    {
        end_product = num1 / num2;
        printf("%f\n", end_product);
    }
    // If the user includes the modulo symbol (%); it will do modulo
    else if (strcmp(argv[2], "%") == 0)
    {
        // Formula to do modulo, since it only works for integers normally
        int remainder = (int) (num1 / num2);
        end_product = num1 - (num2 * remainder);
        printf("%f\n", end_product);
    }
}
