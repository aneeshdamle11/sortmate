// Function definations to take file content as input
#include <stdio.h>

// Datastructures

// Alphabet
typedef struct alphabet
{
    char val;
    struct alphabet *next;
}
alphabet;

// Line
typedef struct Line
{
    char firstword;
    alphabet *content;
    struct Line *next;
}
Line;

// Input file contents
Line * get_file(FILE *fileptr);

// Display
void Disp_contents(Line *);

// Free
void Free_contents(Line *);

