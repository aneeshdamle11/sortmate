#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <config.h>
#include "io.h"
#include "sort.h"

options global_options;

FILE *infile = NULL;

void help() {
    const char *options[][3] = {
        {"-b", "", "Ignore leading blanks"},
        {"-c", "", "Check for sorted input; do not sort"},
        {"-d", "", "Consider only blanks and alphanumeric characters"},
        {"-f", "", "Fold lowercase to uppercase characters"},
        {"-h", "", "Display help"},
        {"-i", "", "Consider only printable characters (32 - 126)"},
        {"-k", "[STARTCOL][ORDERING OPTIONS...]","Sort by column or field"},
        {"-n", "", "Sort by numerical value"},
        {"-o", "[FILE]", "Write result to specified file (default: stdout)"},
        {"-r", "", "Reverse the order"},
        {"-S", "[INTEGER]", "Change main memory buffer space"},
        {"-s", "", "Disable last resort comparison"},
        {"-x","[b=bubble|s=selection|q=quick]","Select sorting algorithm"},
    };
    printf("Hello! This is " PACKAGE_STRING ".\n");
    printf("Sort uncountably endless lines with no extra RAM.\n\n");
    printf("Usage: sortmate [OPTIONS] [FILE]\n\n");
    printf("%-8s %-34s %s\n", "OPTION", "ARGUMENTS", "DESCRIPTION");
    printf("%s\n", "--------------------------------------------------------------------------------");
    
    for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
        printf("%-8s %-34s %s\n", options[i][0], options[i][1], options[i][2]);
    }
    printf("%s\n", "--------------------------------------------------------------------------------");
}

void print_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) print_result(arr[i]);
}

orderingoptions get_empty_ordering_options(void) {
    orderingoptions opts;
    opts.b = 0;
    opts.d = 0;
    opts.f = 0;
    opts.i = 0;
    opts.n = 0;
    opts.r = 0;
    return opts;
}

void init_global_options(void) {
    global_options.c = 0;
    global_options.s = 0;
    global_options.S = RAMSPACE;
    global_options.global_ordering_options = get_empty_ordering_options();
    global_options.k = NULL;
    global_options.o = NULL;
    global_options.x = 'b';
}

void cleanup_options(void) {
    FREE(global_options.o);
    // cleanup keys
    if (global_options.k) {
        key *cleaner = global_options.k;
        key *tracker = cleaner;
        while (tracker) {
            cleaner = tracker;
            tracker = tracker->next;
            FREE(cleaner);
        }
        global_options.k = NULL;
    } else {
        FREE(global_options.k);
    }
    return;
}

void print_ordering_options(orderingoptions o) {
    printf("b: %d, d: %d, f: %d, i: %d, n: %d, r: %d\n", o.b,o.d,o.f,o.i,o.n,o.r);
}

void create_new_key(key k) {
    // create space for a new key
    key *newkey = (key *)malloc(sizeof(key));
    if (!newkey) {
        perror("create_new_key malloc");
        cleanup();
        exit(EXIT_FAILURE);
    }
    // populate the key
    *newkey = k;
    // attach it to the global options
    if (global_options.k == NULL) {
        global_options.k = newkey;
    } else {
        key *tracker = global_options.k;
        while (tracker->next) tracker = tracker->next;
        tracker->next = newkey;
    }
    return;
}

// Support single column sort
void handle_key_input(char *kin) {
    key ktemp;
    ktemp.nfield = 0;
    ktemp.ordering_options = get_empty_ordering_options();
    ktemp.next = NULL;
    if (isdigit(kin[0])) {
        ktemp.nfield = atoi(kin);
        if (ktemp.nfield == 0) {
            printf("field number is zero: invalid field specification\n");
            cleanup();
            exit(EXIT_SUCCESS);
        }
        char *s = kin + strspn(kin, "0123456789");
        while (s && s[0] != '\0') {
            switch(s[0]) {
                case 'b':
                    ktemp.ordering_options.b = 1;
                    break;
                case 'd':
                    ktemp.ordering_options.d = 1;
                    break;
                case 'f':
                    ktemp.ordering_options.f = 1;
                    break;
                case 'i':
                    ktemp.ordering_options.i = 1;
                    break;
                case 'n':
                    ktemp.ordering_options.n = 1;
                    break;
                case 'r':
                    ktemp.ordering_options.r = 1;
                    break;
                default:
                    printf("invalid ordering option %c in key %s.\n", s[0], kin);
                    exit(EXIT_SUCCESS);
            }
            s++;
        }
    } else {
        printf("invalid number at start of the key: %s\n", kin);
        cleanup();
        exit(EXIT_SUCCESS);
    }
    create_new_key(ktemp);
    return;
}

void get_options(int argc, char *argv[]) {
    init_global_options();
    int c;
    while ((c = getopt(argc, argv, "bcdfhik:no:rsS:x:")) != -1) {
        switch(c) {
            case 'b':
                global_options.global_ordering_options.b = 1;
                break;
            case 'c':
                global_options.c = 1;
                break;
            case 'd':
                global_options.global_ordering_options.d = 1;
                break;
            case 'f':
                global_options.global_ordering_options.f = 1;
                break;
            case 'h':
                help();
                exit(EXIT_SUCCESS);
            case 'i':
                global_options.global_ordering_options.i = 1;
                break;
            case 'k':
                handle_key_input(optarg);
                break;
            case 'n':
                global_options.global_ordering_options.n = 1;
                break;
            case 'o':
                global_options.o = (char *)malloc(sizeof(char) * strlen(optarg));
                if (!global_options.o) {
                    perror("get_options malloc");
                    cleanup();
                    exit(EXIT_FAILURE);
                }
                strcpy(global_options.o, optarg);
                // clear file contents
                FILE *fp = fopen(global_options.o, "w");
                if (!fp) perror("fopen"), exit(EXIT_FAILURE);
                fclose(fp);
                break;
            case 'r':
                global_options.global_ordering_options.r = 1;
                break;
            case 'S':
                // TODO: Error handling: not a number
                global_options.S = atoi(optarg);
                break;
            case 's':
                global_options.s = 1;
                break;
            case 'x':
                global_options.x = optarg[0];
                break;
            case '?':
                printf("Try './sortmate -h' for more information\n");
                exit(EXIT_SUCCESS);
        }
    }
    return;
}

void open_infile(int argc, char *argv[]) {
    if (optind < argc) infile = fopen(argv[optind], "r");
    else infile = stdin;
    if (!infile) {
        perror("invalid input");
        exit(EXIT_FAILURE);
    }
    return;
}

void close_infile() {
    if (infile && infile != stdin) {
        if (fclose(infile) != 0) {
            perror("fclose");
            return;
        }
    }
    return;
}

// gets flags, opens input file
void init_sortmate_io(int argc, char *argv[]) {
    get_options(argc, argv);
    open_infile(argc, argv);
    return;
}

void cleanup_sortmate_io(void) {
    cleanup_options();
    close_infile();
    return;
}

void clear_buffer(void) {
    // clear contents of buffer space (not the whole data structure)
    if (buffer) {
        for (int i = 0; i < MAXLINES; i++) FREE(buffer[i]);
    }
    return;
}

void cleanup(void) {
    // cleanup io
    cleanup_sortmate_io();
    // cleanup main buffer
    clear_buffer();
    FREE(buffer);
    return;
}

int print_result(char *result) {
    if (global_options.o != NULL) {
        FILE *fp = fopen(global_options.o, "a");
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
