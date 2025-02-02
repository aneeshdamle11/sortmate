#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

void clear_buffer(void) {
    // clear contents of buffer space (not the whole data structure)
    for (int i = 0; i < MAX_LINES; i++)
        free(buffer[i]), buffer[i] = NULL;
    return;
}

void init_sortmate(int argc, char *argv[]) {
    //printf("Initializing input/output...\n");
    // initialize io (flags and files)
    get_flags(argc, argv);
    open_infile(argc, argv);
    // initialize buffer space
    if (init_buffer() != 0) {
        close_infile();
        exit(EXIT_FAILURE);
    }
    //printf("Input/output initialized\n");
    return;
}

void cleanup(void) {
    //printf("Cleaning up...\n");
    // cleanup io
    close_infile();
    // cleanup main buffer
    clear_buffer();
    free(buffer);
    buffer = NULL;
    //printf("Cleaning done. Ciao!\n");
    return;
}

void create_chunk(char **buffer, int index, int nlines) {
    char tmpfilename[256];
    snprintf(tmpfilename, sizeof(tmpfilename), "tmp%d", index);
    FILE *tmpfile = fopen(tmpfilename, "w");
    if (tmpfile == NULL) {
        perror("fopen");
        cleanup();
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nlines; i++) {
        fprintf(tmpfile, "%s\n", buffer[i]);
    }

    fclose(tmpfile);

    return;
}

int main(int argc, char *argv[]) {
    // initialize flags, input file and temporary space
    init_sortmate(argc, argv);

    int bufidx = 0, chunkidx = 0;

    size_t size;
    char *temp = NULL;
    while (getline(&temp, &size, infile) != -1) {
        if (bufidx == MAX_LINES) {
            sort(buffer, bufidx);
            create_chunk(buffer, chunkidx++, bufidx);
            clear_buffer();
            bufidx = 0;
        }
        temp[strcspn(temp, "\n")] = '\0';
        buffer[bufidx++] = temp;
        temp = NULL;
    }
    // end of file reached
    if (errno == EINVAL || errno == ENOMEM)
        perror("getline"), cleanup(), exit(EXIT_FAILURE);
    // check if external sorting is required
    if (chunkidx == 0) {
        sort(buffer, bufidx);
        print_array(buffer, bufidx);
    } else {
        create_chunk(buffer, chunkidx, bufidx);
        // merge chunks
    }

    cleanup();

    return 0;
}
