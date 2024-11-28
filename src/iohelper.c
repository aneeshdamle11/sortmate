#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "iohelper.h"

int f_reverse = 0;

void display_help(void) {
    printf("Usage: ./sortmate [OPTIONS]... [FILE]...\n");
    printf("\nOptions:\n");
    printf("  --help\t\tdisplay this help message and exit.\n");
    printf("  -o, --output=FILE\twrite result to specified file instead of standard output.\n");
    printf("  -r, --reverse\t\treverse the result of comparisons\n");
    return;
}

void get_flags(int argc, char *argv[]) {
    while (1) {
        int c, option_index = 0;
        static struct option long_options[] = {
          {"help", no_argument, NULL, 0},
          {"reverse", no_argument, &f_reverse, 1},
          {NULL, 0, NULL, 0}
        };

        c = getopt_long(argc, argv, "-:r", long_options, &option_index);
        if (c == -1) break;

        switch(c) {
            case 0:
                if (strcmp(long_options[option_index].name, "help") == 0) {
                    display_help();
                    exit(EXIT_SUCCESS);
                }
                break;
            case 'r':
                f_reverse = 1;
                break;
            case '?':
                printf("./sortmate: invalid option -- '%c'\n", optopt);
                printf("Try './sortmate --help' for more information.\n");
                exit(EXIT_FAILURE);
            case ':':
                printf("Missing option for %c\n", optopt);
                break;
            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
    return;
}

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
}
