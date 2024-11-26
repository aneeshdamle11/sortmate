#include <stdio.h>
#include <getopt.h>
#include "sort.h"

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
}

void display_help(void) {
    printf("Usage: ./sortmate [OPTIONS]... [FILE]...\n");
    printf("\nOptions:\n");
    printf("  --help\t\tDisplay this help message and exit.\n");
    printf("  -o, --output=FILE\tWrite result to specified file instead of standard output.\n");
    return;
}

int main(int argc, char *argv[]) {
    // TODO: Update the usage after every option
    if (argc > 2) {
        display_help();
        return 0;
    }

    while (1) {
        int c, option_index = 0;
        static struct option long_options[] = {
          {"help", no_argument, NULL, 0},
          {NULL, 0, NULL, 0}
        };

        c = getopt_long(argc, argv, "", long_options, &option_index);
        if (c == -1) break;

        switch(c) {
            case 0:
                display_help();
                return 0;
        }
    }

    // take input
    char *lines[] = {
        "Apple",
        "banana",
        "orange",
        "Grape",
        "pineapple",
    };

    // sort
    bubblesort(lines, sizeof(lines) / sizeof(lines[0]));

    // output
    print_array(lines, sizeof(lines) / sizeof(lines[0]));

    return 0;
}
