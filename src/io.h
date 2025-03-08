#ifndef IO_H
#define IO_H (1)
#include <stdio.h>

#define RAMSPACE (512)
#define OFILE_SIZE (32)
#define MAXLINES (global_options.S)

#define LENGTH(str) (strnlen(str, MAXLEN))
extern FILE *infile;

typedef struct {
    int b, d, f, i, n, R, r, s;
} orderingoptions;

#define ORDERING_OPTIONS ("bdfinRrs")

typedef struct key {
    int nfield;
    orderingoptions order_options;
    struct key *next;
} key;

typedef struct {
    int c, S;
    orderingoptions global_order_options;
    key *k;
    char *o;
    char x;
} options ;

extern options global_options;
extern char **buffer;

void init_sortmate_io(int argc, char *argv[]);

void clear_buffer();
void cleanup(void);

void print_array(char *arr[], int n);
int print_result(char *result);

#endif /* ifndef IO_H */
