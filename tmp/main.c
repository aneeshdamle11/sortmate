#include <stdio.h>
#include <stdlib.h>
#include "external_sort.h"


/* Program sorts large files of numbers */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./a.out infile outfile\n");
        printf("Sorts the unsorted infile and stores it in outfile.\n");
        return 1;
    }

    // Read the data from a file, and sort it in chunks
    // Get number of temporary files created
    int temporary_file_count = sort_in_chunks(argv[1], CHUNK_SIZE);


    // Merge each temporary sorted file, and write the data in final output
    // file.
    merge_sorted_chunks(argv[2], CHUNK_SIZE, temporary_file_count);

    return 0;
}

