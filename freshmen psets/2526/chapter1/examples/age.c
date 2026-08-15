// Age.c by Evelyn Chan
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int year = get_int("What year were you born? ");
    int adj = get_int("Have you had your birthday yet? (0 = yes, 1 = no) ");
    int age = 2025 - year - adj;
    printf("You are %i years old. /n", age);
    printf("half your age is: %.1f . /n", age / 2.0);
    // %.1f means you want the deciaml number only to the tens
}
