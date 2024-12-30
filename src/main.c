#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "sort.h"
#include "io.h"

void init_sortmate(int argc, char *argv[]) {
    // get flags and open input file
    init_sortmate_io(argc, argv);

    // make a temporary space
    if (mkdir(TEMPSPACE_DIR, 0755) != 0) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
    return;
}

char ** init_buffer(void) {
    char **buffer = (char**)malloc(sizeof(char*) * MAX_LINES);
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_LINES; i++) {
        buffer[i] = NULL;
    }
    return buffer;
}

void cleanup(void) {
    close_infile();
    // TODO: remove temporary space
    return;
}

// transfer contents of buffer into outfile, and cleanup the buffer
void clear_buffer(char **buffer, int size, char *outfilename) {
    FILE *outfile = fopen(outfilename, "w");
    if (!outfile) {
        printf("Could not open %s for writing\n", outfilename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        if (buffer[i])
            fprintf(outfile, "%s\n", buffer[i]);
        free(buffer[i]);
        buffer[i] = NULL;
    }
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
    // initialize flags, input file and temporary space
    init_sortmate(argc, argv);

    // while (more input)
    int i = 0;
    while(!feof(infile)) {
        char **buffer = init_buffer();
        int nlines = 0;
        size_t len = 0;
        ssize_t ch_read = 0;
        while ((ch_read = getline(&buffer[nlines], &len, infile) != -1)) {
            if (ch_read == -1) {
                free(buffer[nlines]);
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
        printf("Buffer batch: %d\n", i++);
        char fname[256];
        snprintf(fname, sizeof(fname), "%s/tmp%d", TEMPSPACE_DIR, i);
        //print_array(buffer, nlines);
        clear_buffer(buffer, nlines, fname);
        free(buffer);
        buffer = NULL;
    }

    cleanup();

    return 0;
}
