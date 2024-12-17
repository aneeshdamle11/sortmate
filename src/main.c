#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "sort.h"

int rflag = 0, nflag = 0, kflag = 0, kopt = 0;

void help(void) {
    printf("Usage: ./sortmate [OPTIONS]... [FILE]...\n");
    printf("\nOptions:\n");
    printf("  -h\tdisplay this help message and exit.\n");
    printf("  -r\treverse the result of comparisons\n");
    printf("  -n\tcompare strings with their numeric value\n");
    printf("  -k COL\tsort via the column number\n");
}

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) printf("%s\n", arr[i]);
}

int main(int argc, char *argv[]) {

    // TODO: OPTION-combinations
    int c;
    while ((c = getopt(argc, argv, "hrnk:")) != -1) {
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
            case '?':
                printf("Try './sortmate -h' for more information\n");
                return 1;
        }
    }

    // get input
    char *lines[] = {
        "abc Abc x",
        "Abc abc w",
        "20Apple2 xyz v",
        "10Apple2 xyz f",
        "100banana1 wxy g",
        "50orange Orange e",
        "60Grape grape b ",
        "10pineapple def a",
    };

    // sort
    bubblesort(lines, sizeof(lines) / sizeof(lines[0]));

    // output
    print_array(lines, sizeof(lines) / sizeof(lines[0]));

    return 0;
}
