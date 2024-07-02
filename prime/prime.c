#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO

    //Checking if number is 1 or less
    if (number > 1)
    {
        for (int j = 2; j <= number / 2; j++)
        {
            //Reminder check
            if (number % j == 0)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
