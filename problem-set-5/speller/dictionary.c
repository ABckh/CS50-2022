// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

unsigned int dictionary_size = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
   struct node *next;
}
node;

bool check_next(node *list, const char *word);
void free_node(node *list);

const unsigned int N = 4051;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *p = table[index];
    if (p == NULL)
    {
        return false;
    }
    return check_next(p, word);
}

bool check_next(node *list, const char *word)
{
    if (list == NULL)
    {
        return false;
    }
    if (strcasecmp(list->word, word) == 0)
    {
        return true;
    }
    return check_next(list->next, word);
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
            total += toupper(word[i]);
    }
    return total;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s ", word) != EOF)
    {
        node *p = malloc(sizeof(node));
        if (p == NULL)
        {
            return false;
        }
        unsigned int index = hash(word);
        p->next = NULL;
        strcpy(p->word, word);

        if (table[index] == NULL)
        {
            table[index] = p;
        }
        else
        {
            p->next = table[index];
            table[index] = p;
        }
        dictionary_size++;
    }
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < LENGTH + 1; i++)
    {
        free_node(table[i]);
    }
    return true;
}

void free_node(node *list)
{
    if (list == NULL)
    {
        return;
    }
    free_node(list->next);
    free(list);
}
