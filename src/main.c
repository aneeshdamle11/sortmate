#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "sort.h"

int f_reverse = 0;

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
}

void display_help(void) {
    printf("Usage: ./sortmate [OPTIONS]... [FILE]...\n");
    printf("\nOptions:\n");
    printf("  --help\t\tdisplay this help message and exit.\n");
    printf("  -o, --output=FILE\twrite result to specified file instead of standard output.\n");
    printf("  -r, --reverse\t\treverse the result of comparisons\n");
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
          {"reverse", no_argument, &f_reverse, 1},
          {NULL, 0, NULL, 0}
        };

        c = getopt_long(argc, argv, "-:r", long_options, &option_index);
        if (c == -1) break;

        switch(c) {
            case 0:
                if (strcmp(long_options[option_index].name, "help") == 0) {
                    display_help();
                    return 0;
                }
                printf("long option %s\n", long_options[option_index].name);
                break;
            case 'r':
                f_reverse = 1;
                break;
            case '?':
                printf("./sortmate: invalid option -- '%c'\n", optopt);
                printf("Try './sortmate --help' for more information.\n");
                return 1;
            case ':':
                printf("Missing option for %c\n", optopt);
                break;
            default:
                printf("?? getopt returned character code 0%o ??\n", c);
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
