/* 
 * hashtabletest.c - test program for CS50 hashtable module
 *
 * usage: read names from stdin, each on one line
 *
 * Sajjad C Kareem  September October 2nd, 2023
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "../lib/file.h"

static void keyitemprint(FILE* fp, const char* key, void* item);
static void itemdelete(void* item);
void iterate_print(void* arg, const char* key, void* item);

int main()
{
    char* name;
    hashtable_t* ht = hashtable_new(10);
    if (ht == NULL)
    {
        fprintf(stderr, "hashtable_new failed\n");
        return 1;
    }

    printf("\nTest with null hashtable, good key/item...\n");
    hashtable_insert(NULL, "Key", "Item");

    printf("Test with good hashtable, null key...\n");
    hashtable_insert(ht, NULL, "Item");

    printf("Test with good hashtable, null item...\n");
    hashtable_insert(ht, "Key", NULL);

    printf("Test with null hashtable, null key, null item...\n");
    hashtable_insert(NULL, NULL, NULL);

    // Inserting items from input
    printf("\nInserting items from input...\n");
    while (!feof(stdin)) 
    {
        name = file_readLine(stdin);
        if (name != NULL) 
        {
            hashtable_insert(ht, name, name);
            free(name);
        }
    }
    
    printf("\nIterating over the hashtable...\n");
    hashtable_iterate(ht, NULL, iterate_print);

    // Printing the set
    printf("\nThe hashtable:\n");
    hashtable_print(ht, stdout, keyitemprint);

    // Cleanup
    printf("\nDeleting the hashtable...\n");
    hashtable_delete(ht, itemdelete);

    return 0;
}

void keyitemprint(FILE* fp, const char* key, void* item)
{
    printf("%s=%s", key, (char*)item);
}

void itemdelete(void* item)
{
    if (item != NULL) 
    {
        free(item);
    }
}

void iterate_print(void* arg, const char* key, void* item) 
{
    printf("Iterate: %s = %s\n", key, (char*)item);
}