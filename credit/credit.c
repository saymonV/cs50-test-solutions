#include <cs50.h>
#include <stdio.h>

// Function declarations
int cardLength(long cardNumber);
int firstTwoDigits(long cardNumber, int digitCounter);
bool checksum(long cardNumber, int digitCounter);

int main(void)
{
    // Variable declarations
    long userInput = get_long("Number: ");
    int digitCounter = cardLength(userInput);
    int twoDigits = firstTwoDigits(userInput, digitCounter);

    // Logic calls checksum function and prints respected category if they are valid
    if (checksum(userInput, digitCounter) == true)
    {
        if (digitCounter == 15 && (twoDigits == 34 || twoDigits == 37))
        {
            printf("AMEX\n");

        }
        else if (digitCounter == 16 && (twoDigits > 50 && twoDigits < 56))
        {
            printf("MASTERCARD\n");
        }
        else if ((digitCounter == 13 || digitCounter == 16) && twoDigits / 10 == 4)
        {
            printf("VISA\n");
        }
        // Any other case is invalid
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function accepts cardNumber as argument and checks card length

int cardLength(long cardNumber)
{
    // Storing card number in new variable and declaring counter
    long cn = cardNumber;
    int counter = 0;
    // Dividing with 10 removes last digit and increments counter
    while (cn != 0)
    {
        cn /= 10;
        counter++;
    }
    return counter;
}

// Store first 2 digits of the card

int firstTwoDigits(long cardNumber, int digitCounter)
{
    int twoDigits = 0;
    if (digitCounter == 16)
    {
        // Dividing card numbers depending on their size gives us first 2 digits
        twoDigits = cardNumber / 100000000000000;
    }
    else if (digitCounter == 15)
    {
        twoDigits = cardNumber / 10000000000000;
    }
    else if (digitCounter == 13)
    {
        twoDigits = cardNumber / 100000000000;
    }
    else
    {
        twoDigits = 0;
    }

    return twoDigits;
}

// Function checks if card is valid using 2 arguments long and int but returns boolian

bool checksum(long cardNumber, int digitCounter)
{

    long cn = cardNumber;
    int currentNumber;
    int sum = 0;
    // With  For loop we are summing up numbers using given formula
    for (int i = 0; i < digitCounter; i++)
    {
        // Summing up current number
        currentNumber = cn % 10;
        cn /= 10;
        if (i % 2 == 0)
        {
            sum += currentNumber;
        }
        else
        {
            // Every other numbver is multiplied by 2
            int doubleNumber = currentNumber * 2;
            // Number is added to the sum if a one digit
            if (doubleNumber < 10)
            {
                sum += doubleNumber;
            }
            // If not its broken into two separate numbers and added separatly to the sum
            else
            {
                sum += 1 + (doubleNumber % 10);
            }
        }
    }
    // If sum is valid returns true
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
