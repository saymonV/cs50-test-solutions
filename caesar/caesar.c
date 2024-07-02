#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function declarations
bool check_key(string key);
char rotate(char c, int n);
int cipher_text(int numericKey, string text);

int main(int argc, string argv[])
{

    // Program needs to run with one command-line argument
    if (argc != 2)
    {
        printf("One command-line required \n");
        return 1;
    }
    // Argument needs to be numeric
    else if (check_key(argv[1]) == false)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    else
    {
        // Getting user input
        string text = get_string("plaintex:  ");
        // Calling a function with explicit conversion using atoi
        cipher_text(atoi(argv[1]), text);
        return 0;

    }
}

// Function is making sure every character in key is a digit
bool check_key(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // isdigit returns 0 if input is not a decimal digit
        if (isdigit(key[i]) == 0)
        {
            return false;
        }

    }
    return true;
}

// Function rotates a character 'c' using formula and key 'n'
char rotate(char c, int n)
{
    char cripted = '\0';
    // If character is not alphabetical it's not changed
    if (isalpha(c) == 0)
    {
        cripted = c;
    }
    // Checking if character is upper case
    else if (isupper(c) > 0)
    {
        cripted = (c - 65 + n) % 26 + 65;
    }
    // Or lower case
    else if (islower(c) > 0)
    {
        cripted = (c - 97 + n) % 26 + 97;
    }

    return cripted;
}

// Function takes valid key and text and cipher it calling rotate function
int cipher_text(int numericKey, string text)
{
    int textLength = strlen(text);
    string ciphered = text;

    for (int i = 0; i < textLength; i++)
    {
        ciphered[i] = rotate(text[i], numericKey);
    }

    printf("ciphertext: %s\n", ciphered);

    return 0;

}