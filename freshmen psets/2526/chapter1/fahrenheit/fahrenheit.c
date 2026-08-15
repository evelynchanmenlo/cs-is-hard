// Fahrenheit by Evelyn Chan
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float celcius = get_float("C: ");
    // converts celcius into fahrenheit, using this formula
    float fahrenheit = (celcius * 1.8) + 32;
    printf("F: %.1f\n", fahrenheit);
}
