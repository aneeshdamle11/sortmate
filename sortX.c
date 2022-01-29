// GNU/Linux Sort command attempted

#include <stdio.h>
#include "fileread.h"

int main(int argc, char *argv[])
{
    //TODO : Options
    if (argc < 2)
    {
        printf("./sortX [FILENAME ...]\n");
        return 1;
    }

    // File input
    FILE *fileptr = fopen(argv[1], "r");

    // Read file contents
    Line *head = get_file(fileptr);

    // TODO : Merge

    // Display contents
    Disp_contents(head);

    // Free contents
    Free_contents(head);
}

