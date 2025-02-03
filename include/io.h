#ifndef IO_H
#define IO_H (1)
#include <stdio.h>

/* TODO: data/mini.txt --> flag testing
 * Change this later to data/default.txt
 */
#define DEFAULT_INPUT ("data/default.txt")

extern int rflag, nflag, kflag, kopt, cflag;
extern char sopt;
extern FILE *infile;

void get_flags(int argc, char *argv[]);
void open_infile(int argc, char *argv[]);
void close_infile(void);

void print_array(char *arr[], int n);

#endif /* ifndef IO_H */
