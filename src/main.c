#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "sort.h"

int rflag = 0;

void help(void) {
    printf("Usage: ./sortmate [OPTIONS]... [FILE]...\n");
    printf("\nOptions:\n");
    printf("  -h\tdisplay this help message and exit.\n");
    printf("  -r\treverse the result of comparisons\n");
}

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) printf("%s\n", arr[i]);
}

int main(int argc, char *argv[]) {

    int c;
    char *ofile = NULL;
    while ((c = getopt(argc, argv, "hr")) != -1) {
        switch(c) {
            case 'h':
                help();
                return 0;
            case 'r':
                rflag = 1;
                break;
            /*
            case 'o':
                ofile = optarg;
                break;
            */
            case '?':
                printf("Try './sortmate -h' for more information\n");
                return 1;
        }
    }

    printf("rflag: %d\n", rflag);
    // take input
    char *lines[] = {
        "10Apple2",
        "10banana1",
        "50orange",
        "60Grape",
        "10pineapple",
    };

    // sort
    bubblesort(lines, sizeof(lines) / sizeof(lines[0]));

    // output
    print_array(lines, sizeof(lines) / sizeof(lines[0]));

    return 0;
}
