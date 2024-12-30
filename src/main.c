#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int rflag = 0, nflag = 0, kflag = 0, kopt = 0, cflag = 0;

void help(void) {
    printf("Usage: ./sortmate [OPTIONS]... [FILE]\n");
    printf("\nOptions:\n");
    printf("  -h\tdisplay this help message and exit.\n");
    printf("  -r\treverse the result of comparisons\n");
    printf("  -n\tcompare strings with their numeric value\n");
    printf("  -k COL\tsort via the column number\n");
    printf("NOTE: input a single file, multicolumnar sort is not supported.\n");
}

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) printf("%s\n", arr[i]);
}

int main(int argc, char *argv[]) {

    int c;
    while ((c = getopt(argc, argv, "hrnk:c")) != -1) {
        switch(c) {
            case 'h':
                help();
                return 0;
            case 'r':
                rflag = 1;
                break;
            case 'n':
                nflag = 1;
                break;
            case 'k':
                kflag = 1;
                kopt = atoi(optarg);
                break;
            case 'c':
                cflag = 1;
                break;
            case '?':
                printf("Try './sortmate -h' for more information\n");
                return 2;
        }
    }

    // get input
    char **buffer = (char **)malloc(MAX_LINES * sizeof(char*));
    for (int i = 0; i < MAX_LINES; i++) {
        buffer[i] = NULL;
    }

    FILE *infile = NULL;
    if (optind < argc) infile = fopen(argv[optind], "r");
    else infile = fopen(DEFAULT_INPUT, "r");
    if (!infile) {
        perror("invalid input");
        return 2;
    }

    // fill buffer
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

    /* clean up */
    fclose(infile);
    infile = NULL;

    // sort
    bubblesort(buffer, nlines);

    // output
    print_array(buffer, nlines);

    /* cleanup */
    for (int i = 0; i < MAX_LINES; i++) {
        if (buffer[i]) free(buffer[i]);
        buffer[i] = NULL;
    }
    if (buffer) free(buffer);
    buffer = NULL;

    return 0;
}

/*
main:
    get_flags
    while (input)
        buffer = get_line
        sort_buffer
        write buffer
*/
