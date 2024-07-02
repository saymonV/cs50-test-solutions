// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 991;

// Hash table
node *table[N];

// Keeps count of added words
int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //Hashing the word the get a bucket number.
    node *ptr = table[hash(word)];
    // Checking linked list
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    // We sum up characters ASCII values
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += toupper(word[i]);
    }
    // Modulo N makes sure we stay in range of buckets
    unsigned int h = sum % N;
    return h;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open up a file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Failed to load dictionary\n");
        return false;
    }
    // Create a buffer
    char buffer[LENGTH + 1];
    // Reading from a file
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *ptr = NULL;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            printf("Faild to load a word\n");
            return false;
        }

        // Hashing
        int h = hash(buffer);
        // Copy
        strcpy(n->word, buffer);
        // Creating a linked list
        if (table[h] == NULL)
        {
            table[h] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[h];
            table[h] = n;
        }
        // Counting loaded words
        num_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Counted in load
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Temporary pointers
    node *ptr = NULL;
    node *temp = NULL;
    // Releasing all nodes
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}
