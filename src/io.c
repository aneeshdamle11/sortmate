#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>
#include "io.h"

int rflag = 0, nflag = 0, oflag = 0;
char *ofile = NULL;
char sopt = 'b';

FILE *infile = NULL;

void help(void) {
    printf("Hello! This is " PACKAGE_STRING ".\n");
    printf("Usage: ./sortmate [OPTIONS]... [FILE]\n");
    printf("\nOptions:\n");
    printf("  -h\tdisplay this help message and exit.\n");
    printf("  -r\treverse the result of comparisons\n");
    printf("  -n\tcompare strings with their numeric value\n");
    printf(" -oFILE\twrite result to specified file\n");
    printf(" -sALGO\tselect the sorting algorithm ");
    printf(" [OPTIONS: b=bubblesort, q=quicksort, s=selectionsort]\n");
    printf("NOTE: input a single file.\n");
    return;
}

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) print_result(arr[i]);
}

void get_flags(int argc, char *argv[]) {
    //printf("Reading flags...\n");
    int c;
    while ((c = getopt(argc, argv, "hrno:s:")) != -1) {
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
            case 'o':
                oflag = 1;
                ofile = optarg;
                break;
            case 's':
                sopt = optarg[0];
                break;
            case '?':
                printf("Try './sortmate -h' for more information\n");
                exit(EXIT_FAILURE);
        }
    }

    /*
    printf("[rflag=%d] ", rflag);
    printf("[nflag=%d] ", nflag);
    printf("[sopt=%c]\n", sopt);
    */

    return;
}

void open_infile(int argc, char *argv[]) {
    //printf("Opening input file(s)...\n");
    if (optind < argc) infile = fopen(argv[optind], "r");
    else infile = stdin;
    if (!infile) {
        perror("invalid input");
        exit(EXIT_FAILURE);
    }
    //printf("Initialized input file(s): %s\n", argv[optind]);
    return;
}

void close_infile() {
    //printf("Closing input(s)...\n");
    if (fclose(infile) != 0) {
        perror("fclose");
        return;
    }
    //printf("File closed\n");
    return;
}

// gets flags, opens input file
void init_sortmate_io(int argc, char *argv[]) {
    get_flags(argc, argv);
    open_infile(argc, argv);
    return;
}

int print_result(char *result) {
    if (oflag == 1) {
        FILE *fp = fopen(ofile, "a");
        if (fp == NULL) {
            perror("fopen");
            return 1;
        }
        fprintf(fp, "%s\n", result);
        fclose(fp);
    } else {
        printf("%s\n", result);
    }
    return 0;
}
