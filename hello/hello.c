#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompts user for his name
    string username = get_string("Please type in your name:");
  
    // Printing out user input
    printf("hello, %s\n", username);
}