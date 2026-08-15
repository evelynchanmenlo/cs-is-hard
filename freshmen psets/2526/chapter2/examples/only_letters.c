// Only Letters by Evelyn Chan
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    string str = get_string("String: ");
   // This goes through every char in the key
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // If the key is not a number, then it returns false
        if (isdigit(key[i]) == false)
        {
            return false;
        }
    }
    return true;

    if (return == true)
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
}

