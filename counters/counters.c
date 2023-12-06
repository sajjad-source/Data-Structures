/* 
 * counters.c - 'counters' module
 *
 * see counters.h for more information.
 *
 * Sajjad C Kareem  September 29, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"

/**************** local types ****************/
typedef struct countersnode
{
    int key;                        // the key for this counter
    int count;                      // the count associated with the key
    struct countersnode* next;      // pointer to next counter node
} countersnode_t;

/**************** global types ****************/
typedef struct counters
{
    countersnode_t* head;           // head of the list of counters
} counters_t;

/**************** counters_new() ****************/
/* see counters.h for description */
counters_t* counters_new(void)
{
    counters_t* ctrs = malloc(sizeof(counters_t));  
    if (ctrs == NULL)
    {
        return NULL;        // Error allocating memory for the counter                
    }
    ctrs->head = NULL;      // Initialize the head of the counter to NULL
    return ctrs;
}

/**************** counters_add() ****************/
/* see counters.h for description */
int counters_add(counters_t* ctrs, const int key)
{
    if (ctrs == NULL || key < 0)            // Check for NULL counter or negative key
    {
        return 0;
    }

    countersnode_t* curr = ctrs->head;      // Pointer to keep track of current node
    while (curr)
    {
        if (curr->key == key)               // If key exists
        {
            curr->count += 1;               // Then just increment count by one and return it
            return curr->count;
        }
        curr = curr->next;
    }

    countersnode_t* new_node = malloc(sizeof(countersnode_t));
    if (new_node == NULL)
    {
        return 0;                           // Error allocating memory for new node
    }
    new_node->key = key;                    // Set new node's key
    new_node->count = 1;                    // Set count to 1
    new_node->next = ctrs->head;
    ctrs->head = new_node;                  // Insert new node at the head of the list

    return new_node->count;
}

/**************** counters_get() ****************/
/* see counters.h for description */
int counters_get(counters_t* ctrs, const int key)
{
    if (ctrs == NULL)                       // Check if counters is NULL
    {
        return 0;
    }

    countersnode_t* curr = ctrs->head;
    while (curr)                            // Traverse the list and find the item by key
    {
        if (curr->key == key)
        {
            return curr->count;             // If found then return count
        }
        curr = curr->next;
    }

    return 0;                               // Key not found
}

/**************** counters_set() ****************/
/* see counters.h for description */
bool counters_set(counters_t* ctrs, const int key, const int count)
{
    if (ctrs == NULL || key < 0 || count < 0)       // Check if counter is NULL or if key or count is negative
    {
        return false;
    }

    countersnode_t* curr = ctrs->head;
    while (curr)                                    // Traverse the list and find the item by key
    {
        if (curr->key == key)
        {
            curr->count = count;                    // If found, then update the count
            return true;
        }
        curr = curr->next;
    }

    // Key does not exist so create a new node
    countersnode_t* new_node = malloc(sizeof(countersnode_t));
    if (new_node == NULL)                           // Error allocating memory for new node
    {
        return false;
    }
    new_node->key = key;                            // Set the key
    new_node->count = count;                        // Set the  count
    new_node->next = ctrs->head;
    ctrs->head = new_node;                          // Insert new node at the head of the list
    
    return true;
}

/**************** counters_print() ****************/
/* Style and format inspired by bag_print in bag.c */
/* see counters.h for description */
void counters_print(counters_t* ctrs, FILE* fp)
{
    if (fp != NULL)
    {
        if (ctrs != NULL)
        {
            fputc('{', fp);

            // Print each key and its count
            for (countersnode_t* curr = ctrs->head; curr != NULL; curr = curr->next)
            {
                fprintf(fp, "%d=%d", curr->key, curr->count);
                fputc(',', fp);
            }
            fputc('}', fp); 
        } else {
            fputs("(null)", fp);
        }
    }

}

/**************** counters_iterate() ****************/
/* see counters.h for description */
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count))
{
    if (ctrs != NULL && itemfunc != NULL)
    {
        // call itemfunc with arg, on each item
        for (countersnode_t* curr = ctrs->head; curr != NULL; curr = curr->next)
        {
            (*itemfunc)(arg, curr->key, curr->count);
        }
    }
}

/**************** counters_delete() ****************/
/* see counters.h for description */
void counters_delete(counters_t* ctrs)
{
    if (ctrs != NULL)
    {
        countersnode_t* curr = ctrs->head;      
        while (curr != NULL)
        {
            countersnode_t* next = curr->next;  // Save pointer for next before freeing
            free(curr);
            curr = next;
        }
        free(ctrs);
    }
}