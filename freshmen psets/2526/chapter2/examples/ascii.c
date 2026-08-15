//ASCII by Evelyn Chan
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string message = get_string("Message: ");
    for (int i = 0, n = strlen(message); i < n; i++);
    {
        char letter = message[i];
        printf("%i", letter);
    }
}
