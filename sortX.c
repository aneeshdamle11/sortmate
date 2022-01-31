// GNU/Linux Sort command attempted
#include <stdio.h>
#include <stdlib.h>
#include "filesort.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("./sortX [FILENAME ...]\n");
        return 1;
    }

    // File input
    FILE *fileptr = fopen(argv[1], "r");

    // Read and copy file contents
    line head = get_file(fileptr);

    // Sort file contents
    head = mergesort_line(head, count_lines(head));

    // Display contents
    Disp_contents(head);

    // Free contents
    Free_contents(head);
    free(fileptr);
}

