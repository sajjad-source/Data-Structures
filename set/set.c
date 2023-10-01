/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
 *
 * Sajjad C Kareem  September 28, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

/**************** local types ****************/
typedef struct setnode
{
    char* key;                  // Key associated with the item
    void* item;                 // Pointer to the data item
    struct setnode* next;       // Pointer to the next node in the list
} setnode_t;

/**************** global types ****************/
typedef struct set
{
    setnode_t* head;
} set_t;

/**************** set_new() ****************/
/* see set.h for description */
set_t* set_new(void)
{
    set_t* set = malloc(sizeof(set_t));

    if (set == NULL)
    {
        return NULL;            // Error allocating memory for the set
    } else {
        set->head = NULL;       // Initialize the head of the set to NULL
        return set;
    }
}

/**************** set_insert() ****************/
/* see set.h for description */
bool set_insert(set_t* set, const char* key, void* item)
{
    // Check for NULL pointers
    if (set == NULL || key == NULL || item == NULL)
    {
        return false;
    }

    setnode_t* curr = set->head;                        // Pointer to keep track of current node
    while (curr)                
    {
        if (strcmp(curr->key, key) == 0)                // Check if key already exists in set
        {
            return false;
        }
        curr = curr->next;
    }

    setnode_t* new_node = malloc(sizeof(setnode_t));    // Allocate memory for new node
    if (new_node == NULL)
    {
        return false;                                   // Error allocating memory for new node
    }

    char* dup = malloc(strlen(key) + 1);                // Create a duplicate of key
    new_node->key = strcpy(dup, key);                   // Insert the duplicate key
    if (new_node->key == NULL)
    {
        free(new_node);
        return false;                                   // Error duplicating the key
    }

    char* item_dup = malloc(strlen(item) + 1);          // Duplicate the item
    new_node->item = strcpy(item_dup, item);            // Insert the duplicate item
    if (new_node->item == NULL)
    {
        free(new_node->key);
        free(new_node);
        return false;                                   // Error duplicating the item
    }
                        
    new_node->next = set->head;                         // Insert new node at the head of the list
    set->head = new_node;

    return true;
}

/**************** set_find() ****************/
/* see set.h for description */
void* set_find(set_t* set, const char* key)
{
    // Check for NULL
    if (set == NULL || key == NULL)
    {
        return NULL;
    }

    setnode_t* curr = set->head;
    while (curr)                            // Traverse the list and find the item by key
    {
        if (strcmp(curr->key, key) == 0)
        {
            return curr->item;              // Return the item if key matches
        }
        curr = curr->next;
    }

    return NULL;                            // Key not found
}

/**************** set_print() ****************/
/* Style and format inspired by bag_print in bag.c */
/* see set.h for description */
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item))
{
    if (fp != NULL)
    {
        if (set != NULL)
        {
            fputc('{', fp);
            for (setnode_t* curr = set->head; curr != NULL; curr = curr->next)
            {
                // Print each key-item pair using the provided itemprint function
                if (itemprint != NULL)
                {
                    (*itemprint)(fp, curr->key, curr->item);
                    fputc(',', fp);
                }
            }
            fputc('}', fp);
        } else {
            fputs("(null)", fp);
        }
    }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item))
{
    if (set != NULL && itemfunc != NULL)
    {
        // call itemfunc with arg, on each item
        for (setnode_t* curr = set->head; curr != NULL; curr = curr->next)
        {
            (*itemfunc)(arg, curr->key, curr->item);
        }
    }
}

/**************** set_delete() ****************/
/* see set.h for description */
void set_delete(set_t* set, void (*itemdelete)(void* item))
{
    if (set != NULL)
    {
        setnode_t* curr = set->head;
        while (curr != NULL)
        {
            setnode_t* next = curr->next;       // Save pointer for next before freeing
            
            
            if (itemdelete != NULL)
            {
                (*itemdelete)(curr->item);      // Delete each item using the provided itemdelete function
            }
            free(curr->key);
            free(curr);
            
            curr = next;            
        }
        free(set);
    }
}