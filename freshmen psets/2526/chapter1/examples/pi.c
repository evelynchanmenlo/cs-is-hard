//Pi by Evelyn Chan
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long big_pi = 314159;
    double pi = (double) big_pi / 100000;
    printf("pi is %.5f", pi);
}
