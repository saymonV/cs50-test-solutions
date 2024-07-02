#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Prototypes of functions
int count_letters(string text, int length);
int count_words(string text, int length);
int count_sentences(string text, int length);

int main(void)
{
    // Getting input from the user
    string userInput = get_string("Text: ");

    // Determening the length of an input.
    int length = strlen(userInput);

    // Storing the results of functions
    int letters = count_letters(userInput, length);
    int words = count_words(userInput, length);
    int sentences = count_sentences(userInput, length);

    // Avrage Letters and Sentences calculation
    float avrgLetters = (float)letters / (float)words * 100.0;
    float avrgSentences = (float)sentences / (float)words * 100.0;
    // Using Coleman-Liau formula we calculate readability index
    float index = round(0.0588 * avrgLetters - 0.296 * avrgSentences - 15.8);


    // Logic  prints out the results
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index > 1 && index < 16)
    {
        printf("Grade %i\n", (int)index);
    }

}

// Function for counting letters in a given text
int count_letters(string text, int length)
{
    int letters = 0;
    for (int i = 0; i < length; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
    }
    return letters;
}

// Function for counting words in a given text
int count_words(string text, int length)
{
    int words = 1;
    for (int i = 0; i < length; i++)
    {
        // Excludes spaces on the begining or at end
        if (text[i] == 32 && (i > 0 && i != length - 1))
        {
            words++;
        }
    }
    return words;
}

// Function for counting sentences in a given text
int count_sentences(string text, int length)
{

    int sentences = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }

    return sentences;
}