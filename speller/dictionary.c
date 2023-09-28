// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Counts number of words copied from dictionary
unsigned int count = 0;

// Hash value to be used as index
unsigned int hashnum = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prime number for number of buckets in hash table
const unsigned int N = 5039;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word and find in dictionary
    hashnum = hash(word);
    // Initialize cursor then traverse linked list
    node *cursor = table[hashnum];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Reference: Walkthrough video for Speller
    // Reference: shorturl.at/bf567
    // Math using all the letters
    long key = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        key += tolower(word[i]); // Sum of all characters each word
    }
    return key % N; // Modulo to ensure index is within hash table bounds
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file to read and check for null
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        // Read file into this string
        char dict[LENGTH + 1];
        // Read until EOF
        while (fscanf(file, "%s", dict) == 1)
        {
            // Allocate space for each word and check for NULL
            node *new = malloc(sizeof(node));
            if (new != NULL)
            {
                // Copy dictionary word to new and insert to linked list
                strcpy(new->word, dict);
                hashnum = hash(new->word);
                new->next = table[hashnum];
                table[hashnum] = new;

                // Count words read
                count++;
            }
        }
        fclose(file);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (count > 0)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Declare cursor and tmp then go through linked list
    node *cursor, *tmp;
    for (int i = 0; i < N; i++)
    {
        cursor = tmp = table[i];
        while (cursor != NULL)
        {
            // Move to next node
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    // Ensures there is no memory leak
    if (cursor == NULL)
    {
        return true;
    }
    return false;
}
