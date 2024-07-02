#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// User-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{


    // Making sure we accept only one line argument
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize \n");
        return 1;
    }
    // Wordsize must be 5, 6, 7 or 8
    else if (atoi(argv[1]) < 5 || atoi(argv[1]) > 8)
    {
        printf("Error: wordsize must be either 5, 6, 7 or 8 \n");
        return 1;
    }
    // If input is valid we assing wordsize and proceed
    int wordsize = atoi(argv[1]);

    // Open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // Load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // Pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // Allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // Print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // Main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // Obtain user's guess
        string guess = get_guess(wordsize);

        // Array to hold guess status, initially set to zero
        int status[wordsize];

        // Set all elements of status array initially to 0, aka WRONG
        // TODO #4
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = WRONG;
        }
        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);
        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // If they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7

    if (won == true)
    {
        printf("You won!");
    }
    else
    {
        printf("Word you were looking for was: %s \n", choice);
    }

    // That's all folks!
    return 0;
}
// Function takes guess input from user

string get_guess(int wordsize)
{
    string guess = "";

    // Ensure users actually provide a guess that is the correct length
    // TODO #3
    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
    }
    while (wordsize != strlen(guess));



    return guess;
}
// Checks the guess input and scores it

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    //Looping over each word and checking if it matches
    for (int i = 0; i < wordsize; i++)
    {
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] == choice[j] && i == j)
            {
                score += EXACT;
                status[i] = EXACT;
                break;
            }
            else if (guess[i] == choice[j])
            {
                score += CLOSE;
                status[i] = CLOSE;
            }
            else
            {
                score += WRONG;
                status[i] = WRONG;
            }
        }
    }

    return score;
}

// Prints colored guess
void print_word(string guess, int wordsize, int status[])
{
    // Using loop we print each character separatly and marking it with correct color

    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN"%c"RESET, guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW"%c"RESET, guess[i]);
        }
        else if (status[i] == 0)
        {
            printf(RED"%c"RESET, guess[i]);
        }
    }
    printf("\n");
    return;
}

