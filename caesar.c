#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encipher(string plaintext, int key);
int test_arguments(int arguments, string key[]);

int main(int argc, string argv[])
{
    int test = test_arguments(argc, argv);
    if (test)
    {
        return test;
    }
    else
    {
        string plaintext = get_string("plaintext: ");
        int key = atoi(argv[1]);
        return encipher(plaintext, key);
    }
}

int test_arguments(int arguments, string key[])
{
    if (arguments != 2)
    {
        printf("Usage: ./caesar key.\n");
        return 1;
    }
    for (int i = 0, n = strlen(key[1]); i < n; i++)
    {
        if (!isdigit(key[1][i])) // Change to check if key is not a digit
        {
            printf("Usage: ./caesar key.\n");
            return 1;
        }
    }
    return 0;
}

int encipher(string plaintext, int key)
{
    printf("ciphertext: ");
    int n = strlen(plaintext);
    char ciphertext[n + 1]; // Make room for the null terminator
    for (int i = 0; i < n; i++)
    {
        char c = plaintext[i];

        if (isalpha(c))
        {
            // Handle rotation for uppercase letters
            if (isupper(c))
            {
                ciphertext[i] = (c - 'A' + key) % 26 + 'A';
            }
            // Handle rotation for lowercase letters
            else if (islower(c))
            {
                ciphertext[i] = (c - 'a' + key) % 26 + 'a';
            }
        }
        else
        {
            // Non-alphabet characters stay the same
            ciphertext[i] = c;
        }
    }
    ciphertext[n] = '\0'; // Null-terminate the ciphertext string
    printf("%s\n", ciphertext);
    return 0;
}