#ifndef IO_H
#define IO_H (1)
#include <stdio.h>

#define RAMSPACE (512)
#define OFILE_SIZE (32)

#define MAXLINES (global_options.S)

#define LENGTH(str) (strnlen(str, MAXLEN))
#define IS_ORDERING_OPTIONS_EMPTY(X) (X.b == 0 && X.d == 0 && X.f == 0 && \
        X.i == 0 && X.n == 0 && X.r == 0)

extern FILE *infile;

typedef struct {
    int b, d, f, i, n, r;
} orderingoptions;

#define ORDERING_OPTIONS ("bdfinrs")

typedef struct key {
    int nfield;
    orderingoptions ordering_options;
    struct key *next;
} key;

typedef struct {
    int c, s, S;
    orderingoptions global_ordering_options;
    key *k;
    char *o;
    char x;
} options ;

extern options global_options;
extern char **buffer;

orderingoptions get_empty_ordering_options(void);
void init_sortmate_io(int argc, char *argv[]);

void clear_buffer();
void cleanup(void);

void print_array(char *arr[], int n);
int print_result(char *result);

#endif /* ifndef IO_H */
