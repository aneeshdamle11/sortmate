#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "external_sort.h"
#include "sort.h"
#include "heap/heap.h"


int get_temporary_files_count(int count, int size) {
    // Get count of temporary files
    int num;
    num = count / size;
    if (count % size)
        num++;

    return num;
}


/*! \brief Comparator function
 * Provides flexibility to qsort function for sorting an array
 */
int compar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compar_rev(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int sort_in_chunks(char *input, int chunk_size, char option) {
    // Open the file to be sorted
    FILE *infile = fopen(input, "r");
    if (!infile) {
        printf("Cannot open file :(\n");
        exit(0);
    }

    // Get total numbers in file
    long long count = 0;
    while (!feof(infile)) {
        int temp;
        fscanf(infile, "%d\n", &temp);
        count++;
    }
    printf("%lld\n", count);
    rewind(infile);

    // Get count of temporary files
    int num = get_temporary_files_count(count, chunk_size);
    printf("Temporary files: %d.\n", num);

    FILE *tmp[num];
    // Create temporary chunks
    char filename[8];

    for (int i = 0; i < num; i++) {
        // Name temporary files
        snprintf(filename, sizeof(filename), "%03i.txt", i);
        // Open temporary files
        tmp[i] = fopen(filename, "w");
        if (!tmp[i]) {
            printf("Could not create %03i.txt for writing tmp chunk :(\n", i);
            return 0;
        }
    }
    printf("Temporary files created.\n");

    // Mallocate an array to fit a chunk of data
    int *chunk = (int*)malloc(sizeof(int) * chunk_size);
    if (!chunk) {
        printf("Could not allocate chunk-sized array :(\n");
        return 0;
    }

    // Get the contents of each chunk from input file
    printf("Count: %lld\n CS: %d\n", count, chunk_size);
    int i;
    for (i = 0; i < count / chunk_size; i++) {
        for (int j = 0; j < chunk_size; j++) {
            fscanf(infile, "%d\n", chunk + j);
        }
        //printf("Before:\t");
        //display_array(chunk, chunk_size);

        // Sort the chunk of data in-place
        switch (option) {
            case ('n'):
                qsort(chunk, chunk_size, sizeof(int), compar);
                break;
            case ('r'):
                qsort(chunk, chunk_size, sizeof(int), compar_rev);
                break;
            default:
                qsort(chunk, chunk_size, sizeof(int), compar);
                break;
        }

        // Write the data in respective file
        for (int k = 0; k < chunk_size; k++) {
            fprintf(tmp[i], "%d\n", chunk[k]);
        }
    }

    // Sort and write any remaining data less than size allotted for chunk
    for (int i = 0; i < chunk_size; ++i) {
        chunk[i] = 0;
    }

    //printf("%lld\n", count % chunk_size);
    int j = 0;
    while (j < count % chunk_size) {
        fscanf(infile, "%d\n", chunk + j);
        j++;
    }

    if (j) {
        switch (option) {
            case ('n'):
                qsort(chunk, chunk_size, sizeof(int), compar);
                break;
            case ('r'):
                qsort(chunk, chunk_size, sizeof(int), compar_rev);
                break;
            default:
                qsort(chunk, chunk_size, sizeof(int), compar);
                break;
        }

        for (int k = 0; k < chunk_size; k++) {
            if (chunk[k])
                fprintf(tmp[i], "%d\n", chunk[k]);
        }
    }

    // Free temporary array
    free(chunk);

    // Close all temporary files
    for (int i = 0; i < num; ++i) {
        fclose(tmp[i]);
    }

    fclose(infile);
    return num;
}


/* NOTE: num = number of temporary files created */
void merge_sorted_chunks(char *output, int chunk_size, int num, char option) {
    // Open all the temporary chunk files
    FILE *tmp[num];
    char filename[8];

    for (int i = 0; i < num; i++)
    {
        // Name temporary files
        snprintf(filename, sizeof(filename), "%03i.txt", i);
        // Open temporary files
        tmp[i] = fopen(filename, "r");
        if (!tmp[i]) {
            printf("Could not open %03i.txt for writing tmp chunk :(\n", i);
            return;
        }
    }

    // Open final output file
    FILE *outfile = fopen(output, "w");
    if (!outfile) {
        printf("Could not open final output file :(\n");
        return;
    }

    // Sorting mate!
    
    // Create an array of minheap nodes
    node *heaparray = (node *)malloc(sizeof(node) * num);
    if (!heaparray) {
        printf("Could not malloc heaparray :(\n");
        return;
    }

    int i;
    for (i = 0; i < num; ++i) {

        // Check if any file is empty
        if (fscanf(tmp[i], "%d\n", &(heaparray[i].key)) != 1)
            break;

        // Write index of temporary chunk in the index of corresponding node
        heaparray[i].index = i;
    }
    printf("Number of files equals total tmp?%i\n", (i == num));

    // Create a minheap
    Heap h = NULL;
    switch (option) {
        case ('n'):
            h = build_min_heap(heaparray, i);
            break;
        case ('r'):
            h = build_max_heap(heaparray, i);
            break;
        default:
            h = build_min_heap(heaparray, i);
            break;
    }

    int count = 0;

    // Behold a very beautiful algorithm!
    while (count != i) {

        // Get node with minimum key and store it in output file
        node *res = NULL;

        switch (option) {
            case ('n'):
                res = get_min(h);
                break;
            case ('r'):
                res = get_max(h);
                break;
            default:
                res = get_min(h);
                break;
        }

        fprintf(outfile, "%d\n", res->key);

        // Replace minimum element with next
        if (fscanf(tmp[res->index], "%d\n", &(res->key)) != 1) {
            res->key = INT_MAX;
            count++;
        }

        switch (option) {
            case ('n'):
                min_heapify(h, 0);
                break;
            case ('r'):
                max_heapify(h, 0);
                break;
            default:
                min_heapify(h, 0);
                break;
        }

        res = NULL;
    }

    // Free the heap and array of heapnodes
    free(heaparray);
    heaparray = h->A = NULL;
    free(h);
    h = NULL;

    // close all files
    for (int i = 0; i < num; ++i) {
        fclose(tmp[i]);
    }

    fclose(outfile);

    return;
}

