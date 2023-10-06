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
    if (!set_insert(NULL, "Key", "Item"))
    {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    printf("\nTest with good set, null key...\n");
    if (!set_insert(set, NULL, "Item"))
    {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    printf("\nTest with good set, null item...\n");
    if (!set_insert(set, "Key", NULL))
    {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    printf("\nTest with null set, null key, null item...\n");
    if (!set_insert(NULL, NULL, NULL))
    {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    // Inserting items from input
    printf("\nInserting items from input...\n");
    while (!feof(stdin)) 
    {
        name = file_readLine(stdin);
        if (name != NULL) 
        {
            if (set_insert(set, name, name))
            {
                continue;
            } else {
                free(name);
            }
        }
    }

    // Inserting duplicate
    printf("\nTesting inserting a duplicate...\n");
    if (!set_insert(set, "John", "Duplicate"))
    {
        printf("Test succeeded: Duplicate was not inserted\n");
    } else {
        printf("Test failed: Duplicate was inserted\n");
    }

    // Testing find
    printf("\nTesting set find on an existing key...\n");
    if (set_find(set, "John") != NULL)
    {
        void* item = set_find(set, "John");
        printf("Key 'John' was found. The item is: %s\n", (char*) item);
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