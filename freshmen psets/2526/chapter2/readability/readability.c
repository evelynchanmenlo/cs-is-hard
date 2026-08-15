// Readability by Evelyn Chan
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define MIN 1
#define MAX 16
float letters = 0;
// This accounts for the first word in the string.
// The function for the word count counts the spaces, so there will always be one less "word" than
// there actually is.
float words = 1;
float sentences = 0;
// There are three functions created to find the letter, word, and sentence count.
void letters_count(string text);
void words_count(string text);
void sentences_count(string text);

int main(void)
{
    // This prompts the user for input.
    string text = get_string("Text: ");

    // Calls the three functions.
    letters_count(text);
    words_count(text);
    sentences_count(text);
    // This finds the average of letters per 100 words in the text.
    float L = (letters / words) * 100;
    // This finds the average of sentences per 100 words in the text.
    float S = (sentences / words) * 100;
    // Inputs L and S into the Coleman-Liau index to find the grade level.
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    // If the reading level is too low, it will print "Before Grade 1"
    if (index < MIN)
    {
        printf("Before Grade 1\n");
    }
    // If the reading level is too high, it will print that it is too high.
    else if (index >= MAX)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

void letters_count(string text)
{
    // This for loop uses strlen to go through every single char in the string.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // If each char is alphabetical, then it would add to the letters count.
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
}

void words_count(string text)
{
    // This also uses strlen to go through every char in the string.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // This counts the amount of spaces in the string.
        // So, every new space indicates that there is a new word.
        if (isblank(text[i]))
        {
            words++;
        }
    }
}

void sentences_count(string text)
{
    // This also uses strlen to go through every char in the string.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // This counts the amount of puncuation in the string.
        // The amount of puncuation used indiciates how many sentences there are.
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
}
