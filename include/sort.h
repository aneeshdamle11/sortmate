#ifndef SORT_H
#define SORT_H (1)

#define MAX_LEN (128)
#define MAX_LINES (1024)

#define DEFAULT_INPUT ("data/default.txt")

int compare_lines(char str1[], char str2[]);
void bubblesort(char *arr[], int size);

extern int rflag, nflag, kflag, kopt, cflag;

#endif /* ifndef SORT_H */
