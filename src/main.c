#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "io.h"

char **buffer = NULL;

int init_buffer(void) {
    //printf("Initializing buffer...\n");
    buffer = (char**)malloc(sizeof(char*) * MAX_LINES);
    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < MAX_LINES; i++) {
        buffer[i] = NULL;
    }
    //printf("Buffer space malloc'd\n");
    return 0;
}

void init_sortmate(int argc, char *argv[]) {
    // initialize io (flags and files)
    get_flags(argc, argv);
    open_infile(argc, argv);
    // initialize main temporary space
    if (init_buffer() != 0) {
        close_infile();
        exit(EXIT_FAILURE);
    }
}

void cleanup(void) {
    //printf("Cleaning up...\n");
    // cleanup io
    close_infile();
    // cleanup main temporary space
    for (int i = 0; i < MAX_LINES; i++)
        if (buffer[i] != NULL)
            free(buffer[i]), buffer[i] = NULL;
    free(buffer);
    buffer = NULL;
    //printf("Cleaning done. Ciao!\n");
    return;
}

int main(int argc, char *argv[]) {
    // initialize flags, input file and temporary space
    init_sortmate(argc, argv);

    int i;
    for (i = 0; i < MAX_LINES; i++) {
        size_t size;
        if (getline(&buffer[i], &size, infile) != -1) {
            //printf("Buffer %d received: size %lu bytes\n", i, size);
            buffer[i][strcspn(buffer[i], "\n")] = '\0';
        } else {
            perror("getline");
            cleanup();
            exit(EXIT_FAILURE);
        }
    }

    sort(buffer, i);

    print_array(buffer, i);

    // merge chunks
    cleanup();

    return 0;
}
