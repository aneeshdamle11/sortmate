#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "io.h"

int rflag = 0, nflag = 0, kflag = 0, kopt = 0, cflag = 0;
FILE *infile = NULL;

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

void get_flags(int argc, char *argv[]) {
    int c;
    while ((c = getopt(argc, argv, "hrnk:c")) != -1) {
        switch(c) {
            case 'h':
                help();
                exit(EXIT_SUCCESS);
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
                exit(EXIT_FAILURE);
        }
    }
    return;
}

void open_infile(int argc, char *argv[]) {
    if (optind < argc) infile = fopen(argv[optind], "r");
    else infile = fopen(DEFAULT_INPUT, "r");
    if (!infile) {
        perror("invalid input");
        exit(EXIT_FAILURE);
    }
    return;
}

void close_infile(void) {
    fclose(infile);
    infile = NULL;
    return;
}

void init_sortmate_io(int argc, char *argv[]) {
    get_flags(argc, argv);
    open_infile(argc, argv);
    return;
}
