// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 200329

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[HASHTABLE_SIZE] = {NULL};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //change word to lowercase
    int n = strlen(word);
    char word_lower[n + 1];

    word_lower[n] = '\0';

    for (int i = 0; i < n; i++)
    {
        word_lower[i] = tolower(word[i]);
    }

    //Hash the word to obtain the hash value
    int index = hash(word_lower, strlen(word_lower), 0);

    //Go to that location in the hash table
    node *cursor = hashtable[index];

    //Loop through hash table if word is not at initial location
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
// sourced from https://github.com/aappleby/smhasher/blob/master/src/MurmurHash2.cpp
// MurmurHash2 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.
unsigned int hash(const char *word, int len, unsigned int seed)
{
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.

    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    unsigned int h = seed ^ len;

    // Mix 4 bytes at a time into the hash

    const unsigned char *data = (const unsigned char *)word;

    while (len >= 4)
    {
        unsigned int k = *(unsigned int *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    // Handle the last few bytes of the input array

    switch (len)
    {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h % HASHTABLE_SIZE;
}


// Loads dictionary into memory, returning true if successful else false
//Initialize word counter
int word_count = 0;

bool load(const char *dictionary)
{
    //Open dictionary file and check if null
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        printf("Dictionary file contains no words");
        return false;
    }

    //array for current word
    char word[LENGTH + 1];


    //Loop through dictionary file
    while (fscanf(dict, "%s", word) != EOF)
    {
        //Allocates memory for new node and checks if enough memory available
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            printf("Insufficient memory for new node");
            return false;
        }

        //Copies current word to new node, counts number of words loaded
        strcpy(new_node->word, word);
        new_node->next = NULL;
        word_count++;

        //Implement Hash Function to return index value
        int index = hash(word, strlen(word), 0);

        //Prepend value into hash table
        new_node->next = hashtable[index];
        hashtable[index] = new_node;

    }
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count == 0)
    {
        return 0;
    }
    else
    {
        return word_count;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    //Goes through each value of the hashtable and frees the associated linked list
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *cursor = hashtable[i];

        while (cursor != NULL)
        {

            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }


    return true;

}
