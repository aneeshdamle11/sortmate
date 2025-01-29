#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

int rflag = 0, nflag = 0, kflag = 0, kopt = 0, cflag = 0;
char sopt = 'x';

FILE *infile = NULL;

void help(void) {
    printf("Usage: ./sortmate [OPTIONS]... [FILE]\n");
    printf("\nOptions:\n");
    printf("  -h\tdisplay this help message and exit.\n");
    printf("  -r\treverse the result of comparisons\n");
    printf("  -n\tcompare strings with their numeric value\n");
    printf("  -k COL\tsort via the column number\n");
    printf("  -c\tsimply check if input is sorted\n");
    printf("  -s ALGO\tselect the sorting algorithm (b=bubblesort,q=quicksort)\n");
    printf("NOTE: input a single file. multicolumnar sort is not supported.\n");
}

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) printf("%s\n", arr[i]);
}

void get_flags(int argc, char *argv[]) {
    //printf("Reading flags...\n");
    int c;
    while ((c = getopt(argc, argv, "hrnk:cs:")) != -1) {
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
    printf("[kflag=%d,kopt=%d] ", kflag, kopt);
    printf("[cflag=%d] ", cflag);
    printf("[sopt=%c]\n", sopt);
    */

    return;
}

void open_infile(int argc, char *argv[]) {
    //printf("Opening input file(s)...\n");
    if (optind < argc)
        infile = fopen(argv[optind], "r");
    else
        infile = fopen(DEFAULT_INPUT, "r");

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
