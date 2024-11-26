#include <stdio.h>
#include "sort.h"

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
}

int main(int argc, char *argv[]) {
    // TODO: Update the usage after every option
    if (argc > 1) {
        printf("Usage: ./sortmate [OPTION] ... [FILE] ...\n");
        return 0;
    }

    // take input
    char *lines[] = {
        "Apple",
        "banana",
        "orange",
        "Grape",
        "pomogranate",
    };

    // sort
    bubblesort(lines, sizeof(lines) / sizeof(lines[0]));

    // output
    print_array(lines, sizeof(lines) / sizeof(lines[0]));

    return 0;
}
