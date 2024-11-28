#include "sort.h"
#include "iohelper.h"

int main(int argc, char *argv[]) {
    // TODO: Update the usage after every option
    if (argc > 2) {
        display_help();
        return 0;
    }
    get_flags(argc, argv);

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
