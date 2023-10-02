/* 
 * settest.c - test program for CS50 set module
 *
 * usage: read names from stdin, each on one line
 *
 * Sajjad C Kareem  September 30, 2023
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "../lib/file.h"

static void keyitemprint(FILE* fp, const char* key, void* item);
static void itemdelete(void* item);
void iterate_print(void* arg, const char* key, void* item);

int main() 
{
    char* name;
    set_t* set = set_new();
    if (set == NULL) 
    {
        fprintf(stderr, "set_new failed\n");
        return 1;
    }

    printf("\nTest with null set, good key/item...\n");
    set_insert(NULL, "Key", "Item");

    printf("Test with good set, null key...\n");
    set_insert(set, NULL, "Item");

    printf("Test with good set, null item...\n");
    set_insert(set, "Key", NULL);

    printf("Test with null set, null key, null item...\n");
    set_insert(NULL, NULL, NULL);

    // Inserting items from input
    printf("\nInserting items from input...\n");
    while (!feof(stdin)) 
    {
        name = file_readLine(stdin);
        if (name != NULL) 
        {
            set_insert(set, name, name);
            free(name);
        }
    }

    // Printing the set
    printf("\nIterating over the set...\n");
    set_iterate(set, NULL, iterate_print);
    printf("\nThe set:\n");
    set_print(set, stdout, keyitemprint);

    // Cleanup
    printf("\nDeleting the set...\n");
    set_delete(set, itemdelete);

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