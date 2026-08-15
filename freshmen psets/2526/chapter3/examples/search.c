/**
 * Search.c
 * Written by Zach Blick for CS1 @ Menlo School
 * Jan. 2022, updated Jan. 2023
 *
 * To run search, you will enter in three command line arguments:
 *
 * ./search [binary/linear] [size of list to search] [target number]
 *
 * For example, to run binary search to see if 19 is present
 * in a list of 1000 numbers, type:
 *
 * ./search binary 1000 19
 *
 * The numbers are randomly generated from 0 to MAX_ELEMENT - 1,
 * which is defined at 100.
 *
 * TODO: Your job is to compare the number of steps each
 * search algorithm uses. So, you should increment the
 * global int "steps" in the functions binary_search()
 * and linear_search().
 * */

#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <time.h>

#define MAX_SIZE 65536
#define MAX_ELEMENT 100

int steps = 0;
int size;
int target;
int values[MAX_SIZE];

bool binary_search(void);
bool linear_search(void);
void generate(void);
void sort(void);

int main(int argc, string argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./search [binary/linear] "
                "[size of list to search] [target number]\n");
        return 1;
    }

    size = atoi(argv[2]);
    target = atoi(argv[3]);

    // Generate and sort size random numbers from 0 to MAX_ELEMENT.
    generate();

    // If selected, run binary search, then print results.
    if (strcmp(argv[1], "binary") == 0)
    {
        if(binary_search())
        {
            printf("Binary search found %i in a list of %i "
            "numbers in %i steps.\n", target, size, steps);
        }
        else
        {
            printf("Binary search determined that %i is not "
            "in a list of %i numbers in %i steps.\n", target, size, steps);
        }
    }

    // If selected, run linear search, then print results.
    else if (strcmp(argv[1], "linear") == 0)
    {
        if(linear_search())
        {
            printf("Linear search found %i in a list of %i "
            "numbers in %i steps.\n", target, size, steps);
        }
        else
        {
            printf("Linear search determined that %i is not "
            "in a list of %i numbers in %i steps.\n", target, size, steps);
        }
    }
    else
    {
        printf("Usage: ./search [binary/linear] "
        "[size of list to search] [target number]\n");
        return 1;
    }
}

bool binary_search(void)
{
    // First, sort the list.
    sort();

    steps+=2;
    int start = 0;
    int n = size;

    // while the start point is less than the end point
    while (n >= start)
    {
        steps+=2;
        printf("searching index %i...\n", (n + start) / 2);
        // if the value being searched for is at the middle, return true
        steps+=2;
        int mid = values[(n + start) / 2];
        if (mid == target)
        {
            return true;
        }
        // if the value is less than the middle, remove end half
        else if (mid > target)
        {
            steps+=2;
            n = (n + start) / 2 - 1;
        }
        // if the value is more than the middle, remove start half
        else if (mid < target)
        {
            steps+=3;
            start = (n + start) / 2 + 1;
        }
    }

    // if not found, return false
    return false;
}

bool linear_search(void)
{
    for (int i = 0; i < size; i++)
    {
        steps++;
        printf("searching index %i...\n", i);
        // if the value being searched for is at the middle, return true
        steps++;
        if (values[i] == target)
        {
            return true;
        }
    }
    // if not found, return false
    return false;
}

void generate(void)
{
    int max_element = size*size;
    srand48((long int) time(NULL));
    for (int i = 0; i < size; i++)
    {
        values[i] = drand48() * MAX_ELEMENT;
    }
}

// Sorts array of n values
void sort(void)
{
    for (int i = 0; i < size; i++)
    {
        // sets the smallest value as the first unsorted value
        // steps++; // for line 170
        int small = values[i];
        int coord;
        for (int j = i; j < size; j++)
        {
            // if the smallest value is greater than the current value
            // steps++; // for lines 176
            if (small > values[j])
            {
                // steps+=2; // for lines 180 & 181
                // set the new smallest as the current value
                small = values[j];
                coord = j;
            }
        }
        // if the smallest value has not been changed, break the loop
        // steps++; // for line 186
        if (small == values[i])
        {
            break;
        }
        // else, swap the smallest value to the ith position
        else
        {
            // steps+=2; // for lines 194-196
            values[coord] = values[i];
            values[i] = small;
        }
    }
}
