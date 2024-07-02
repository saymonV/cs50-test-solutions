#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Alphabet, indexes of letters correspond to POINTS array indexes
string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    // Logics that checks and print the winner or a tie situation
    if (score1 > score2)
    {
        printf("Player 1 wins! \n");
    }
    if (score1 < score2)
    {
        printf("Player 2 wins! \n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

// Returns a score for a give string as argument
int compute_score(string word)
{

    // Declarations of inside variables and Word length check.
    int length = strlen(word);
    int score = 0;
    // First loop goes through a word and grab each letter
    for (int i = 0; i < length; i++)
    {
        char letter = word[i];
        // Second loop checks given letter with each letter in alphabet array(string)
        for (int j = 0; j < 26; j++)
        {
            // Alphabet is all capital letters so we are making sure both cases are checked before scoring
            if (letter == alphabet[j] || toupper(letter) == alphabet[j])
            {
                score += POINTS[j];
            }
            // Any other character is scored 0
            else
            {
                score += 0;
            }

        }
    }

    // TODO: Compute and return score for string
    return score;


}
