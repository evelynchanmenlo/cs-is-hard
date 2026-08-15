// Hello, again! by Evelyn Chan
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./hello <name>\n");
        return 1;
    }
    string name = argv[1];
    printf("Hello, %s!\n", name);
}
