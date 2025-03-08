#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "sort.h"
#include "io.h"

#define TRIM_NEWLINE(s) (s[strcspn(s, "\n")] = '\0')

char **buffer = NULL;

int init_buffer(void) {
    buffer = (char**)malloc(sizeof(char*) * MAXLINES);
    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < MAXLINES; i++) {
        buffer[i] = NULL;
    }
    return 0;
}

void init_sortmate(int argc, char *argv[]) {
    // initialize io (options and files)
    init_sortmate_io(argc, argv);
    // initialize buffer space
    if (init_buffer() != 0) {
        cleanup();
        exit(EXIT_FAILURE);
    }
    return;
}

void create_chunk(char **buffer, int index, int nlines) {
    char tmpfilename[256];
    snprintf(tmpfilename, sizeof(tmpfilename), "tmp0%d", index);
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

int isbufferempty(void) {
    for (int i = 0; i < MAXLINES; i++) if (buffer[i] != NULL) return 0;
    return 1;
}

void merge_chunks(int nchunks, int layer, int offset, int isend) {
    FILE **chunkfp = (FILE **)malloc(sizeof(FILE *) * nchunks);
    for (int i = 0; i < nchunks; i++) {
        char tmpfilename[256];
        snprintf(tmpfilename, sizeof(tmpfilename), "tmp%d%d", layer, offset*MAXLINES+i);
        chunkfp[i] = fopen(tmpfilename, "r");
        if (chunkfp[i] == NULL) {
            perror("fopen");
            cleanup();
            exit(EXIT_FAILURE);
        }
        size_t size;
        getline(&buffer[i], &size, chunkfp[i]);
        TRIM_NEWLINE(buffer[i]);
    }
    while (!isbufferempty()) {
        // get smallest line
        int sidx = 0;
        for (int i = 0; i < nchunks-1; i++) {
            if (compare_lines(buffer[i], buffer[i+1]) > 0) {
                sidx = i+1;
            }
        }
        // print smallest line
        if (isend == 1) {
            if (print_result(buffer[sidx]) == 1) {
                cleanup();
                exit(EXIT_FAILURE);
            }
        } else {
            FILE *fout = NULL;
            char outfilename[256];
            snprintf(outfilename, sizeof(outfilename), "tmp%d%d", layer+1, offset);
            fout = fopen(outfilename, "a");
            if (fout == NULL) {
                perror("fopen");
                cleanup();
                exit(EXIT_FAILURE);
            }
            fprintf(fout, "%s\n", buffer[sidx]);
            fclose(fout);
            fout = NULL;
        }
        // replace smallest line with the line after it in the respective file
        free(buffer[sidx]);
        buffer[sidx] = NULL;
        size_t size;
        if (getline(&buffer[sidx], &size, chunkfp[sidx]) == -1) {
            if (errno == EINVAL || errno == ENOMEM)
                perror("getline"), cleanup(), exit(EXIT_FAILURE);
            free(buffer[sidx]), buffer[sidx] = NULL;
        }
        if (buffer[sidx]) TRIM_NEWLINE(buffer[sidx]);
    }
    return;
}

void merge_ext(int nchunks) {
    int layer = 0;
    while (nchunks > MAXLINES) {
        int offsetidx = 0, chunks = nchunks;
        while (chunks > 0) {
            int chunksize = (chunks > MAXLINES)? MAXLINES : chunks;
            merge_chunks(chunksize, layer, offsetidx, 0);
            offsetidx++;
            chunks -= MAXLINES;
        }
        layer++;
        nchunks = offsetidx;
    }
    merge_chunks(nchunks, layer, 0, 1);
    return;
}

int main(int argc, char *argv[]) {
    // initialize options, input file and temporary space
    init_sortmate(argc, argv);

    int bufidx = 0, chunkidx = 0;

    size_t size;
    char *temp = NULL;
    while (getline(&temp, &size, infile) != -1) {
        if (bufidx == MAXLINES) {
            sortmate(buffer, bufidx);
            create_chunk(buffer, chunkidx++, bufidx);
            clear_buffer();
            bufidx = 0;
        }
        TRIM_NEWLINE(temp);
        buffer[bufidx++] = temp;
        temp = NULL;
    }
    // end of file reached
    if (errno == EINVAL || errno == ENOMEM)
        perror("getline"), cleanup(), exit(EXIT_FAILURE);
    // check if external sorting is required
    if (chunkidx == 0) {
        sortmate(buffer, bufidx);
        print_array(buffer, bufidx);
        clear_buffer();
    } else {
        create_chunk(buffer, chunkidx, bufidx);
        clear_buffer();
        merge_ext(chunkidx+1);
    }

    cleanup();
    return 0;
}
