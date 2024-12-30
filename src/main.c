#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "io.h"

void init_sortmate(int argc, char *argv[], char ***buf) {
    init_sortmate_io(argc, argv);

    *buf = (char **)malloc(MAX_LINES * sizeof(char*));
    for (int i = 0; i < MAX_LINES; i++) {
        (*buf)[i] = NULL;
    }
    return;
}

void cleanup(char ***buf) {
    close_infile();

    for (int i = 0; i < MAX_LINES; i++) {
        if ((*buf)[i]) free((*buf)[i]);
        (*buf)[i] = NULL;
    }
    if (*buf) free(*buf);
    *buf = NULL;

    return;
}

/*
main:
    get_flags
    while (input)
        buffer = get_line
        sort_buffer
        write buffer
*/
int main(int argc, char *argv[]) {
    // initialize flags, input and buffer space
    char **buffer = NULL;
    init_sortmate(argc, argv, &buffer);

    // while (more input)
    int nlines = 0;
    size_t len = 0;
    ssize_t ch_read = 0;
    while ((ch_read = getline(&buffer[nlines], &len, infile) != -1)) {
        if (ch_read == -1) {
            perror("getline error");
            return 2;
        }
        buffer[nlines][strcspn(buffer[nlines], "\n")] = '\0';
        nlines++;
        if (nlines >= MAX_LINES) break;
    }

    // sort
    bubblesort(buffer, nlines);

    // output
    print_array(buffer, nlines);

    cleanup(&buffer);

    return 0;
}
