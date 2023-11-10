// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int newHash= hash(word);
    node *newNode = table[newHash];
    while (newNode){
        if (strcasecmp(word,newNode->word)==0){
            return true;
        }
        newNode=newNode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    for (int i = 0; word[i] != '\0' && i<=4; i+=1) {
        char c = toupper(word[i]);
        if (c >= 'A' && c <= 'Z') {
            hash = (hash * 1000000) + (c - 'A');
        }
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
int dict_size =0;
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary,"r");
    if (file==NULL){
        printf("Dictionary not found");
        return false;
    }
    char wordArr[LENGTH+1];
    while (fscanf(file,"%s",wordArr)!=EOF){
        node *newNode = malloc(sizeof(node));

        if (newNode==NULL){
            return false;
        }
        newNode->next=NULL;
        strcpy((*newNode).word,wordArr);
        int newHash = hash(newNode->word);
        newNode->next=table[newHash];
        table[newHash]=newNode;
        dict_size++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i =0;i<N;i++){
        node *newNode =table[i];
        while (newNode!=NULL){
            node *tmp = newNode;
            newNode=newNode->next;
            free(tmp);
        }
    }
    return true; //when will it ever return false?
    }
