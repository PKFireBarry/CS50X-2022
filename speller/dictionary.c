// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//word counter
unsigned int word_counter;

//hash value
unsigned int hashes;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //obtain hash value
    hashes = hash(word);

    //cursor position
    node *cursor = table[hashes];

    //go though the linked list
    while (cursor!= NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {

            return true;
        }

        //move to next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    //initialize a sum to 0
    int sum = 0;

    //add all the words ascii values together
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    //return the sum
    return sum % N;


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    //open dictionary
    char buffer[LENGTH + 1];
    FILE *f = fopen(dictionary, "r");
    //error checking
    if (f == NULL)
    {
        printf("error opening dictionary file");
        return false;
    }

    //read string from file one by one till the end of dictionary
    while(fscanf(f, "%s", buffer) != EOF)
    {
        //memory for new node
        node *n=malloc(sizeof(node));

        //error checking memory allocation
        if (n == NULL)
            {
                fclose(f);
                return false;
            }

        //copy buffer to new node
        strcpy(n->word, buffer);

        hashes = hash(n->word);

        n->next = table[hashes];

        table[hashes] = n;

        word_counter++;
    }
    //close file

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    if(word_counter > 0)
    {
        return word_counter;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //loop over hash table
    for (int i = 0; i < N; i++)
    {
        //make a pointer to the start of the list
        node *cursor = table[i];

        //go though the linked list
        while (cursor!= NULL)
        {
            //tmp memory for keeping track of the current position in the linked list
            node *tmp = cursor;

            //move to next node
            cursor = cursor->next;

            //free memory
            free(tmp);
        }

        if(cursor == NULL)
        {
            free(cursor);
            return true;

        }
    }

    return false;
}
