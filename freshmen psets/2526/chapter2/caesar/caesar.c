// Caesar.c
// Written by Zach Blick on Nov. 17, 2023
// for CS1 @ Menlo School in Atherton, CA

// Finished by Evelyn Chan
// on 11/12

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LETTERS_IN_ALPHABET 26

bool is_numerical(string key);
void encrypt(string plaintext, int key);

int main(int argc, string argv[])
{
    // Check if the user provided the correct number of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check for proper key values
    if (!is_numerical(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert the key to an integer
    int key = atoi(argv[1]);

    // Get the plaintext from the user
    string plaintext = get_string("plaintext:  ");

    // Perform Caesar cipher encryption
    encrypt(plaintext, key);

    // Print the ciphertext
    printf("ciphertext: %s\n", plaintext);

    return 0;
}

// Verify that the string passed in is composed exclusively of digits.
bool is_numerical(string key)
{
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
}

// Function to perform Caesar cipher encryption on all letters.
void encrypt(string plaintext, int key)
{
    // This goes through every single char in the string
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // If the char is lowercase, then it will preserve the case and stay lowercase
        if (islower(plaintext[i]))
        {
            // This formula makes sure that the letters will wrap around back to a from z depending
            // on the key
            plaintext[i] = ((plaintext[i] - 'a') + key) % LETTERS_IN_ALPHABET + 'a';
        }
        // If the char is uppercase, then it will preserve the case and stay uppercase
        else if (isupper(plaintext[i]))
        {
            // // This formula makes sure that the letters will wrap around back to A from Z
            // depending on the key
            plaintext[i] = ((plaintext[i] - 'A') + key) % LETTERS_IN_ALPHABET + 'A';
        }
    }
}
