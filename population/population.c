#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startPop;
    int endPop;
    int years = 0;
    // TODO: Prompt for start size
    do
    {
        startPop = get_int("Start population size: \n");
    }
    while (startPop < 9);


    // TODO: Prompt for end size
    do
    {
        endPop = get_int("End population size: \n");
    }
    while (endPop < startPop);
    // TODO: Calculate number of years until we reach threshold
    while (startPop < endPop)
    {
        startPop = startPop + (startPop / 3) - (startPop / 4);
        years ++;
    }



    // TODO: Print number of years
    printf("Years: %i\n", years);
}
