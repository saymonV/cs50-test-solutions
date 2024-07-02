#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    //Checking if input number is in allowed range
    do
    {
        h = get_int("Height: \n");
    }
    while (h >= 9 || h < 1);

    printf("\n");
    //First For loop prints columns (Height)
    for (int i = 0; i < h; i++)
    {
        //Prints spaces in each column
        for (int j = 0; j < h - i - 1; j++)
        {
            printf(" ");
        }
        //Left side
        for (int y = 0; y < i + 1; y++)
        {
            printf("#");
        }
        //Space in the middle
        printf("  ");
        //Right side
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        //Prints a new row after each iteration
        printf("\n");
    }


}