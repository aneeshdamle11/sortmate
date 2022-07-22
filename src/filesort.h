// Function prototypes to take file content as input and sort
#include <stdio.h>       
          
// Datastructures        
// Alphabet              
struct Alphabet          
{         
    char val;            
    struct Alphabet *next;   
};        
          
typedef struct Alphabet * alphabet;
          
// Line   
struct Line              
{         
    char data;           
    alphabet content;    
    struct Line *next;   
};        
          
typedef struct Line * line;  
          
// Input file contents   
line get_file(FILE *fileptr);
          
// Display
void Disp_contents(line);
          
// Free   
void Free_contents(line);
          
// SORTING
// Function prototypes for sorting contents of file line-by-line

// Sort struct line datastructure - Merge Sort
line mergesort_line(line L, int n);

line merge2lines(line l1, line l2, int n1, int n2);

// Counting lines in a file input
int count_lines(line counter);
