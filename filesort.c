// Function definations for sorting file contents line-by-line

#include <stdio.h>
#include "filesort.h"

// Counts number of lines
int count_lines(line counter)
{
    int count;
    for(count = 0; counter != NULL; count++)
    {
        counter = counter -> next;
    }
    return count;
}
        
// Point to second line
line advance_lineptr(line L, int n)
{
    if (L != NULL)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            L = L -> next;
        }
    }
    return L;
}

// MergeSort linked line
line mergesort_line(line L, int n)
{
    // Base Case
    if (n == 1)
    {
        return L;
    }
    // Sort left half
    L = mergesort_line(L, n / 2);

    // Sort right half
    line L1 = advance_lineptr(L, n / 2);
    L1 = mergesort_line(L1, n - n / 2);

    // Merge both lines
    line head = merge2lines(L, L1, n / 2, n - n / 2);
    return head;
}

// Merging two linked lines
line merge2lines(line l1, line l2, int n1, int n2)
{
    // Keep one line to return, keep inserting elements from other line

    line head = NULL, prev = NULL;
    int i = 0, j = 0;

    // Null Cases
    if (l1 == NULL && l2 == NULL)
    {
        printf("Error, both lines null");
        return NULL;
    }
    else if(l1 == NULL)
    {
        return l2;
    }
    else if(l2 == NULL)
    {
        return l1;
    }

    // Head
    if (l1 -> data <= l2 -> data)
    {
        head = l1;
        l1 = l1 -> next;
        i++;
    }
    else if (l2 -> data < l1 -> data)
    {
        head = l2;
        l2 = l2 -> next;
        j++;
        head -> next = l1;
    }
    prev = head;

    // Insert smaller elemnt
    while (i < n1 && j < n2)
    {
        if (l1 -> data <= l2 -> data)
        {
            prev = l1;
            l1 = l1 -> next;
            i++;
        }
        else if (l2 -> data < l1 -> data)
        {
            prev -> next = l2;
            l2 = l2 -> next;
            prev = prev -> next;
            prev -> next = l1;
            j++;
        }
    }
    if (i == n1)
    {
        prev -> next = l2;
    }
    else if (j == n2)
    {
        while (i < n1)
        {
            prev = prev -> next;
            i++;
        }
        prev -> next = l2;
    }
    return head;
}

