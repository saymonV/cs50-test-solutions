// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string replace(string argv[1]);
int main(int argc, string argv[])
{

  if (argc == 2)
  {
    string input = argv[1];

    printf ("%s  \n", input);
    printf ("%s  \n", replace(&input));
  }
  else
  {
    printf ("Error: incorrect command line input \n");
    return 1;
  }




}


string replace(string argv[1])
{
  int length = strlen(argv[1]);
  string word = argv[1];
  for (int i = 0; i < length - 1; i++)
  {
      char letter = argv[1][i];
      printf("%c",letter);

      switch (letter)
      {
        case 96:
        case 65:
            word[i] = '6';
            break;

        case 101:
        case 69:
            word[i] = '6';
            break;

        case 105:
        case 73:
            word[i] = '1';
            break;

        case 111:
        case 79:
            word[i] = '0';
            break;
      }
  }
  return word;
}