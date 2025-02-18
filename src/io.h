#ifndef IO_H
#define IO_H (1)
#include <stdio.h>

extern int rflag, nflag, kflag, kopt, cflag;
extern char sopt;
extern FILE *infile;

void get_flags(int argc, char *argv[]);
void open_infile(int argc, char *argv[]);

void close_infile(void);

void print_array(char *arr[], int n);
int print_result(char *result);

#endif /* ifndef IO_H */
