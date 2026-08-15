// Dog Years by Evelyn Chan
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int age = get_int("What is your age? ");
    int dog_age = age * 7;
    printf("You are %i dog-years old. /n", dog_age);
}
