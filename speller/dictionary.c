// Implements a dictionary's functionality

#define  _GNU_SOURCE
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// number of word in dictionary
double wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // position on hashtable
    int pos = hash(word);

    for (node *tmp = table[pos]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int number;
    if(strlen(word) == 1)
    {
        number = toupper(word[0]) - 'A';
    }
    else // create something like address 0 = a, 26 = aa, 27 = ab...
    {
        number = 26 * (1 + toupper(word[0]) - 'A') + (toupper(word[1]) - 'A');
    }

    return number;
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }

    char word[LENGTH + 1];
    // reads each line of the dictionary and create a new word in the hashtable
    while (fscanf(file, "%s", word) != EOF)
    {
        wordCount++;
        // allocate space for the new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        int pos = hash(word);
        // put the new node at the start of the address
        strcpy(n->word, word);
        n->next = table[pos];
        table[pos] = n;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // loop to all the addresses in the array
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            // free the linked lists from each address
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
