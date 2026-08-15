//Total Letters by Evelyn Chan
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int total_letters = 0;
    for (;;)
    {
        string word = get_string("word: ");
        if (strcmp(word, "STOP") == 0)
        {
            break;
        }
        int i = 0;
        while (word[i] == '\0')
        {
            char letter = word[i];
            if (isalpha(letter))
            {
                total_letters = total_letters + 1;
            }
             i ++;
        }
    }
    printf("%i\n", total_letters);
}
