// Swap - No Swap by Evelyn Chan
#include <stdio.h>

void swap(int *x, int *y);

int main(void)
{
    int x = 3;
    int y = 4;
    printf("x is %i and y is %i\n", x, y);
    printf("Swapping...\n");
    swap(&x, &y);
    printf("x is %i and y is %i\n", x, y);
}

// Swaps values of x and y
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
