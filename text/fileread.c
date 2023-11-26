// Function definitions for reading from a file
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "files.h"

// states
#define FIRST 1
#define MID 2
#define NEWLINE 3

// Line linked list functions
line addLine(int ch)
{
    line line_ptr = (line)malloc(sizeof(struct Line));
    if (line_ptr == NULL)
    {
        printf("Unable to malloc line pointer from heap memory\n");
        return NULL;
    }
    line_ptr -> data = ch;
    line_ptr -> content = NULL;
    line_ptr -> next = NULL;

    return line_ptr;
}

// Alphabet linked list functions
alphabet addAlphabet(int ch)
{
    alphabet alpha_ptr = (alphabet)malloc(sizeof(struct Alphabet));
    if (alpha_ptr == NULL)
    {
        printf("Unable to malloc alphabet pointer from heap memory\n");
        return NULL;
    }
    alpha_ptr -> val = ch;
    alpha_ptr -> next = NULL;
    return alpha_ptr;
}

// File input
line get_file(FILE *fileptr)
{
    // If file DNE or empty
    if (fileptr == NULL)
    {
        printf("Unable to access file\n");
    }

    line head = NULL;
    line lineptr = NULL;
    alphabet alphaptr = NULL;

    // Start reading
    char ch;
    int state = FIRST;

    while((ch = fgetc(fileptr)) != EOF)
    {
        // Newline character
        if (ch == '\n')
        {
            state = NEWLINE;
        }

        // Start of line
        if (state == FIRST)
        {
            // Create line
            // Start of file
            if (head == NULL)
            {
                head = addLine(toupper(ch));
                lineptr = head;
            }
            else
            {
                lineptr -> next = addLine(toupper(ch));
                lineptr = lineptr -> next;
            }

            // TODO : state for 2nd column sorting
            
            // Create
            lineptr -> content = addAlphabet(ch);
            alphaptr = lineptr -> content;
            state = MID;
        }

        // Middle of line
        else if (state == MID || state == NEWLINE)
        {
            alphaptr -> next = addAlphabet(ch);
            alphaptr = alphaptr -> next;

            if (state == NEWLINE)
            {
                state = FIRST;
            }
        }
    }

    // TODO : Case for line ordering UPPERCASE LOWERCASE
    return head;
}

// Display structure contents
void Disp_contents(line read)
{
    //printf("Reading\n");
    alphabet alpharead = NULL;
    int count = 0;
    while (read != NULL)
    {
        alpharead = read -> content;
        while (alpharead != NULL)
        {
            printf("%c", alpharead -> val);
            alpharead = alpharead -> next;
        }
        read = read -> next;
        count++;
    }
    printf("Lines displayed: %d\n", count);
    return;
}

// Free structure contents
void Free_contents(line free_ptr)
{
    line free_ptr2 = NULL;
    alphabet alpha_ptr = NULL;
    alphabet alpha_ptr2 = NULL;

    int i = 0, j = 0;
    while (free_ptr != NULL)
    {
        i = 0;
        free_ptr2 = free_ptr;
        free_ptr = free_ptr -> next;
        alpha_ptr = free_ptr2 -> content;
        while (alpha_ptr != NULL)
        {
            alpha_ptr2 = alpha_ptr;
            alpha_ptr = alpha_ptr -> next;
            free(alpha_ptr2);
            i++;
        }
        //printf("Alphabets freed: %d\n", i);

        free(free_ptr2);
        j++;
    }
    // printf("Lines freed: %d\n", j);
    return;
}

