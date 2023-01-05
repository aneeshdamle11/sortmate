#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "external_sort.h"


/* Program sorts large files of numbers */
int main(int argc, char *argv[]) {

    // Define allowable flags
    char *flags = "nr";

    // Get flag and check validity
    char flag = getopt(argc, argv, flags);

    if (flag == '?')
    {
        printf("Invalid flag.\n");
        return 1;
    }

    // Only one filter at a time!
    if (getopt(argc, argv, flags) != -1)
    {
        printf("Only one flag allowed.\n");
        return 2;
    }

    if (argc != optind + 2)
    {
        printf("Usage: ./a.out [option] infile outfile\n");
        printf("Sorts the unsorted infile and stores it in outfile.\n");
        printf("-n : normal sort\n");
        printf("-r : reverse sort\n");
        return 3;
    }

    // Read the data from a file, and sort it in chunks
    // File I/O
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Get number of temporary files created
    int temporary_file_count = sort_in_chunks(infile, CHUNK_SIZE, flag);

    // Merge each temporary sorted file, and write the data in final output
    // file.
    merge_sorted_chunks(outfile, CHUNK_SIZE, temporary_file_count, flag);

    return 0;
}

