// Vigenere by Evelyn Chan
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LETTERS_IN_ALPHABET 26
#define NULL_TERMINATOR 1

bool is_alphabetical(string key);
char encrypt_letter(char plaintext_letter, char key_letter);

int main(int argc, string argv[])
{
    // Check if the user provided the correct number of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check for proper key values
    if (!is_alphabetical(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string key = argv[1];
    // Get the plaintext from the user
    string plaintext = get_string("plaintext: ");

    // initizlize an empty array of chars for the ciphertext
    char ciphertext[strlen(plaintext) + NULL_TERMINATOR];

    char encrypted_letter;
    char plaintext_letter;
    char key_letter;
    int index = 0;

    // Runs for each letter in the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        plaintext_letter = plaintext[i];
        // If the plaintext letter is alphabetical, then you apply the shifts
        if (isalpha(plaintext_letter))
        {
            // This makes sure that the key wraps around and starts over if the word ends.
            if (index == strlen(key))
            {
                index = 0;
            }

            key_letter = key[index];
            encrypted_letter = encrypt_letter(plaintext_letter, key_letter);
            // Adds one to the index so the key letter changes to the next letter in key.
            index++;
            // Adds the encrypted letter to the final encrypted message
            ciphertext[i] = encrypted_letter;
        }
        // If it is not alphabetical (puncuation/space), then you just leave it as is
        else
        {
            ciphertext[i] = plaintext_letter;
        }
    }
    // This makes sure that the arry ends in a null terminator, so it could be a string.
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
}

// Verify that the string passed in is composed exclusively of letters.
bool is_alphabetical(string key)
{
    // This goes through every char in the key
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // If the key is not a letter, then it returns false
        if (isalpha(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}

// Function to perform Vigenere cipher encryption on all letters.
char encrypt_letter(char plaintext_letter, char key_letter)
{
    char cipher_letter;
    if (isupper(plaintext_letter))
    {
        // This adds the shifts of the plain text letter and the key letters to get the cipher
        // letter
        cipher_letter = ((plaintext_letter - 'A') + (toupper(key_letter) - 'A'));
        // Using the modulo operator to wrap around the alphabet if necessary
        cipher_letter = cipher_letter % LETTERS_IN_ALPHABET + 'A';
    }
    else
    {
        // This adds the shifts of the plain text letter and the key letters to get the cipher
        // letter
        cipher_letter = ((plaintext_letter - 'a') + (tolower(key_letter) - 'a'));
        // Using the modulo operator to wrap around the alphabet if necessary
        cipher_letter = cipher_letter % LETTERS_IN_ALPHABET + 'a';
    }
    return cipher_letter;
}
