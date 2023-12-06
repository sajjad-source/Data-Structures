/* 
 * hashtabletest.c - test program for hashtable module
 *
 * usage: read names from stdin, each on one line
 *
 * Sajjad C Kareem  September October 2nd, 2023
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

static void print_sets(FILE *fp, const char *key, void *item);
static void item_func(void *arg, const char *key, void *item);
static void item_delete(void *item);

int main()
{
    hashtable_t *ht;

    // Test: Create a new hashtable
    ht = hashtable_new(5);
    printf("Creating an empty hashtable of size 5...\n");
    printf("Expected: \n{}\n{}\n{}\n{}\n{}\n");
    printf("Got:\n");
    hashtable_print(ht, stdout, print_sets);
    printf("---------------------------------------------\n");

    // Test: Insert items
    printf("Inserting key-value pairs...\n");
    hashtable_insert(ht, "Dartmouth", "College");
    hashtable_insert(ht, "Hanover", "Town");
    hashtable_insert(ht, "CS50", "Software Design");
    hashtable_insert(ht, "CS10", "Object-Oriented Programming");
    hashtable_insert(ht, "CS1", "Introduction to Computer Science");
    printf("Expected: \n... (arrangement of Dartmouth, Hanover, CS50, CS10, CS1)\n");
    printf("Got:\n");
    hashtable_print(ht, stdout, print_sets);
    printf("---------------------------------------------\n");

    // Test: Attempt to insert a duplicate key
    printf("Inserting duplicate key 'CS50'...\n");
    hashtable_insert(ht, "CS50", "Duplicate Course");
    printf("Expected: \n... (should still only have one 'CS50')\n");
    printf("Got:\n");
    hashtable_print(ht, stdout, print_sets);
    printf("---------------------------------------------\n");

    // Test: Find an item
    printf("Finding item with key 'Dartmouth'...\n");
    printf("Expected: College\n");
    printf("Got: %s\n", (char *)hashtable_find(ht, "Dartmouth"));
    printf("---------------------------------------------\n");

    // Test: Attempt to find an item with a non-existing key
    printf("Finding item with non-existing key 'Harvard'...\n");
    printf("Expected: (null)\n");
    printf("Got: %s\n", (char *)hashtable_find(ht, "Harvard"));
    printf("---------------------------------------------\n");

    // Test: Count items in hashtable
    int item_count = 0;
    hashtable_iterate(ht, &item_count, item_func);
    printf("Expected: 5 items in the hashtable.\n");
    printf("Got: %d items in the hashtable.\n", item_count);
    printf("---------------------------------------------\n");

    // Test: Delete the hashtable
    printf("Deleting the hashtable...\n");
    hashtable_delete(ht, item_delete);
    printf("Hashtable deleted.\n");
    printf("---------------------------------------------\n");

    return 0;
}

static void print_sets(FILE *fp, const char *key, void *item)
{
    char *value = item;
    if (value == NULL)
    {
        fprintf(fp, "(null)");
    } else {
        fprintf(fp, "(%s, %s)", key, value);
    }
}

static void item_func(void *arg, const char *key, void *item)
{
    int *nkeys = arg;
    if (nkeys != NULL && key != NULL && item != NULL)
    {
        (*nkeys)++;
    }
}

static void item_delete(void *item)
{
    if (item != NULL)
    {
        item = NULL;
    }
}