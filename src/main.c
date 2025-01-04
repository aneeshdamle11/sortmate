#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "io.h"

char **buffer = NULL;

int init_buffer(void) {
    buffer = (char**)malloc(sizeof(char*) * MAX_LINES);
    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < MAX_LINES; i++) {
        buffer[i] = NULL;
    }
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
    // cleanup io
    close_infile();
    // cleanup main temporary space
    for (int i = 0; i < MAX_LINES; i++)
        if (buffer[i] != NULL)
            free(buffer[i]), buffer[i] = NULL;
    free(buffer);
    buffer = NULL;
    return;
}

int main(int argc, char *argv[]) {
    // initialize flags, input file and temporary space
    init_sortmate(argc, argv);

    int i;
    for (i = 0; i < MAX_LINES; i++) {
        // allocate buffer
        buffer[i] = (char *)malloc(sizeof(char) * MAX_LEN);
        if (buffer[i] == NULL) {
            perror("buffer[i] malloc");
            cleanup();
            return 2;
        }
        if (!fgets(buffer[i], MAX_LEN, infile)) {
            free(buffer[i]);
            buffer[i] = NULL;
            break;
        }
        buffer[i][strcspn(buffer[i], "\n")] = '\0';
    }

    bubblesort(buffer, i);

    print_array(buffer, i);

    // merge chunks
    cleanup();

    return 0;
}
