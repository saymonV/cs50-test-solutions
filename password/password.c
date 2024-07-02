// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int n = strlen(password);
    bool lowerCase = false;
    bool upperCase = false;
    bool numeric = false;
    bool punct = false;
    for (int i = 0; i < n ; i++)
    {
        if (islower(password[i]))
        {
            lowerCase = true;
        }
        if (isupper(password[i]))
        {
            upperCase = true;
        }
        if (password[i] >= '0' && password[i] <= '9')
        {
            numeric = true;
        }
        if (ispunct(password[i]))
        {
            punct = true;
        }
    }

    if (lowerCase == true && upperCase == true && numeric == true && punct == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
