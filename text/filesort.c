// Function definations for sorting file contents line-by-line
#include <stdio.h>
#include <ctype.h>
#include "files.h"

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

// Alphabet sort : Case Sensitive handling for same line
int sort_casesensitive(alphabet cscheck1, alphabet cscheck2)
{
    if (cscheck1 -> val == '\n')
    {
        return -1;
    }
    else if (cscheck1 -> val > cscheck2 -> val)
    {
        return -1;
    }
    else if (cscheck2 -> val < cscheck1 -> val)
    {
        return 1;
    }
    else
    {
        return sort_casesensitive(cscheck1 -> next, cscheck2 -> next);
    }
}

// Alphabet sort : Case if first letter is same
int sort_alphabets(alphabet alph1, alphabet alph2)
{
    if (alph1 -> val == '\n')
    {
        return -1;
    }
    else if (toupper(alph1 -> val) < toupper(alph2 -> val))
    {
        return -1;
    }
    else if (toupper(alph2 -> val) < toupper(alph1 -> val))
    {
        return 1;
    }
    else
    {
        return sort_alphabets(alph1 -> next, alph2 -> next);
    }
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
    int i = 0, j = 0, order = 0;

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
    // Comparing next string if same data
    if (l1 -> data == l2 -> data)
    {
        order = sort_alphabets(l1 -> content, l2 -> content);
        // Handle UPPERCASE, LOWERCASE if same otherwise
        if (order == 0)
        {
            order = sort_casesensitive(l1 -> content, l2 -> content);
        }
    }
    if ((l1 -> data < l2 -> data) || order < 0)
    {
        head = l1;
        l1 = l1 -> next;
        i++;
    }
    if ((l2 -> data < l1 -> data) || order > 0)
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
        order = 0;
        if (l1 -> data == l2 -> data)
        {
            order = sort_alphabets(l1 -> content, l2 -> content);
            // Case sensitive handling
            if (order == 0)
            {
                order = sort_casesensitive(l1 -> content, l2 -> content);
            }
        }
        if ((l1 -> data < l2 -> data) || order < 0)
        {
            prev = l1;
            l1 = l1 -> next;
            i++;
        }
        if ((l2 -> data < l1 -> data) || order > 0)
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

