#ifndef IO_H
#define IO_H (1)
#include <stdio.h>

#define MAX_LINES (5)
#define MAX_LEN (1024)
#define TEMPSPACE_DIR ("temp")
#define DEFAULT_INPUT ("data/default.txt")

extern int rflag, nflag, kflag, kopt, cflag;
extern FILE *infile;

void init_sortmate_io(int argc, char *argv[]);

void close_infile(void);

void print_array(char *arr[], int n);

#endif /* ifndef IO_H */
