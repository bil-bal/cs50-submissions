// Implements a dictionary's functionality
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

//Size of dic;
unsigned int sizeD = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    int equal;

    if (table[index] == NULL)
    {
        return false;
    }

    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        equal = strcasecmp(word, tmp->word);
        if (equal == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index;

    index = tolower(word[0]);

    index = index - 97;
    return index;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Dictionary loading failed.\n");
        return false;
    }

    int index;
    char word[45];

    while (fscanf(dic, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory allocation failed.\n");
            return false;
        }

        strcpy(n->word, word);
        index = hash(word);

        if (table[index] == NULL)
        {
            printf("test\n");
            n->next = NULL;
            table[index] = n;
        }
        n->next = table[index];
        table[index]->next = n;
        n->next = NULL;
        sizeD++;
    }

    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return sizeD;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
