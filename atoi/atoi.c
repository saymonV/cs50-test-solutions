#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    string str = input;
    int numeric = 0;
    int length = strlen(input);
    //Base case
    if (str == "\0")
        break;

    for (int i = length - 1; i > 0; i--)
    {
        numeric = input[i];
        input[i] = "\0";
    }


    printf("%i and length %i \n", numeric, length);
    return 0;
}