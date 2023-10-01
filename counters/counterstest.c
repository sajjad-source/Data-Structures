/* 
 * counterstest.c - test program for CS50 counters module
 *
 * usage: read integers from stdin, each on one line
 *
 * Sajjad C Kareem  September 30, 2023
 */

#include <stdio.h>
#include "counters.h"
#include "../lib/file.h"

int main() 
{
    counters_t* counters = counters_new();
    if (counters == NULL)
    {
        fprintf(stderr, "Memory allocation for counters_new failed\n");
        return 1;
    }

    // Test null inputs
    printf("\nTest with null counters, good key...\n");
    counters_add(NULL, 1);

    printf("\nTest counters_get with null counters...\n");
    int count = counters_get(NULL, 1);
    if (count == 0) 
    {
        printf("counters_get with null counters returned zero as expected.\n");
    }

    printf("\nTest counters_set with null counters...\n");
    counters_set(NULL, 1, 5);

    printf("\nInserting numbers from test.integers into the counters...\n");
    int key;
    while (fscanf(stdin, "%d", &key) != EOF)
    {
        counters_add(counters, key);
    }

    // Test counters_print function
    printf("\nCounters after insertion:\n");
    counters_print(counters, stdout);
    printf("\n");
    
    // Test counters_set function
    printf("\nSetting the count for key 5 to 20...\n");
    counters_set(counters, 5, 20);
    printf("Count for 5: %d\n", counters_get(counters, 5));

    // Test invalid keys
    printf("\nTesting invalid keys...\n");
    printf("Setting count for negtiave key -1...\n");
    counters_set(counters, -1, 10);
    printf("Count for -1: %d\n", counters_get(counters, -1));

    // Test counters_get function
    printf("\nTesting counters_get function...\n");
    for (int i = 1; i <= 10; i++)
    {
        printf("Count for %d: %d\n", i, counters_get(counters, i));
    }


    // Cleanup
    printf("\nDeleting the counters...\n");
    counters_delete(counters);

    return 0;
}