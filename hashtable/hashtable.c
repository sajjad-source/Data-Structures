/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Sajjad C Kareem  October 1st, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "hash.h"
#include "../set/set.h"

/**************** global types ****************/
typedef struct hashtable
{
    set_t** arr;        // Array of pointers to sets
    int num_slots;      // Number of slots in the hashtable
} hashtable_t;

/**************** hashtable_new() ****************/
/* see hashtable.h for description */
hashtable_t* hashtable_new(const int num_slots)
{
    if (num_slots <= 0)
    {
        return NULL;
    }

    hashtable_t* ht = malloc(sizeof(hashtable_t));
    if (ht == NULL)
    {
        free(ht);
        return NULL;                                // Error allocating memory for the hashtable
    }

    ht->arr = malloc(num_slots * sizeof(set_t*));   // Allocating memory for the array of pinters to sets
    if (ht->arr == NULL)
    {
        return NULL;                                // Error allocaitng memory for arrays
    }

    for (int i = 0; i < num_slots; i++)             // Loop through all slots in hashtable
    {
        ht->arr[i] = set_new();                     // Initialize a set at that specific array index
        if (ht->arr[i] == NULL)                     // Error initializing a set
        {
            for (int i = 0; i < num_slots; i++)
            {
                if (ht->arr[i] != NULL)             // For each slot that has been allocated
                {
                    free(ht->arr[i]);               // Free it due to error allocation
                }     
            }
            free(ht->arr);                          // Free the array
            free(ht);                               // Free the hashtable
            return NULL;
        }
    }

    ht->num_slots = num_slots;                      // If everything was successful, then initialize the num of slots
    return ht;
}

/**************** hashtable_insert() ****************/
/* see hashtable.h for description */
bool hashtable_insert(hashtable_t* ht, const char* key, void* item)
{
    if (ht == NULL || key == NULL || item == NULL)  // Check for NULL pointers
    {
        return false;
    }

    int slot = hash_jenkins(key, ht->num_slots);    // hash the key

    if (set_find(ht->arr[slot], key) != NULL)       // If the key already exists
    {
        return false;
    }

    if (!set_insert(ht->arr[slot], key, item))      // Error inserting key, could be due to memory allocation
    {
        return false;
    }

    return true;
}

/**************** hashtable_find() ****************/
/* see hashtable.h for description */
void* hashtable_find(hashtable_t* ht, const char* key)
{
    if (ht == NULL || key == NULL)                  // Check for NULL pointers
    {
        return NULL;
    }

    int slot = hash_jenkins(key, ht->num_slots);    // hash the key

    return set_find(ht->arr[slot], key);            // Call set_find and return the key (could be NULL)
}

/**************** hashtable_print() ****************/
/* Style and format inspired by bag_print in bag.c */
/* see hashtable.h for description */
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item))
{
    if (fp != NULL)
    {
        if (ht != NULL)
        {
            for (int i = 0; i < ht->num_slots; i++)
            {
                set_print(ht->arr[i], fp, itemprint);       // Loop through every slot in hashtable, and print the set that it points to.
            }
        } else {
            fputs("(null)", fp);
        }
    }
}

/**************** hashtable_iterate() ****************/
/* see hashtable.h for description */
void hashtable_iterate(hashtable_t* ht, void* arg, void(*itemfunc)(void* arg, const char* key, void* item))
{
    if (ht != NULL && itemfunc != NULL)
    {
        for (int i = 0; i < ht->num_slots; i++)             // Loop through every slot in the hashtable
        {
            set_iterate(ht->arr[i], arg, itemfunc);         // Call set_iterate to the set the array points to
        }
    }
}

/**************** hashtable_delete() ****************/
/* see hashtable.h for description */
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item))
{
    if (ht != NULL)
    {
        if (itemdelete != NULL)
        {
            for (int i = 0; i < ht->num_slots; i++)
            {
                set_delete(ht->arr[i], itemdelete);         // Delete every set pointed to by array
            }
        }
        free(ht->arr);                                      // Free the array
        free(ht);                                           // Free the hashtable
    }
}