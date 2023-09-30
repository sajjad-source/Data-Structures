#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

static void keyitemprint(FILE* fp, const char* key, void* item);
static void itemdelete(void* item);
void iterate_print(void* arg, const char* key, void* item);

int main() 
{
    set_t* set = set_new();
    if (set == NULL) 
    {
        fprintf(stderr, "set_new failed\n");
        return 1;
    }

    // Test inserting
    char *item1 = malloc(strlen("Dartmouth") + 1);
    strcpy(item1, "Dartmouth");

    char *item2 = malloc(strlen("CS50") + 1);
    strcpy(item2, "CS50");

    char *item3 = malloc(strlen("Hanover") + 1);
    strcpy(item3, "Hanover");

    printf("Inserting items...\n");
    set_insert(set, "one", item1);
    set_insert(set, "two", item2);
    set_insert(set, "three", item3);

    // Test finding
    printf("\nFinding items...\n");
    char* item = set_find(set, "two");
    printf("Key 'two' -> Item '%s'\n", item);

    item = set_find(set, "five");
    if (item == NULL) 
    {
        printf("Key 'five' not found as expected.\n");
    }

    // Test null inputs
    printf("\nTest with null set and good key/item...\n");
    if (!set_insert(NULL, "key", "item")) 
    {
        printf("Null set insertion failed as expected.\n");
    }

    printf("Test with good set, null key...\n");
    if (!set_insert(set, NULL, "item")) 
    {
        printf("Null key insertion failed as expected.\n");
    }

    printf("Test with good set, null item...\n");
    if (!set_insert(set, "key", NULL)) 
    {
        printf("Null item insertion failed as expected.\n");
    }

    printf("Test find with null set...\n");
    if (set_find(NULL, "key") == NULL) 
    {
        printf("Null set find failed as expected.\n");
    }

    printf("Test find with null key...\n");
    if (set_find(set, NULL) == NULL) 
    {
        printf("Null key find failed as expected.\n");
    }

    // Test inserting duplicate keys
    printf("\nInserting duplicate key...\n");
    if (!set_insert(set, "one", "Duplicate")) 
    {
        printf("Duplicate key insertion failed as expected.\n");
    }

    printf("\nIterating over the set...\n");
    set_iterate(set, NULL, iterate_print);

    // Print the set
    printf("\nThe set:\n");
    set_print(set, stdout, keyitemprint);
    printf("\n");

    // Clean up
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
