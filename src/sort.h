#ifndef SORT_H
#define SORT_H (1)
#include "io.h"

#define MAXLEN (1024)
#define COMPARE_GLOBAL_FIELDS(A, B) (compare_fields(A, B, global_options.global_order_options))
#define COMPARE_EMPTY_FIELDS(A, B) (compare_fields(A, B, get_empty_ordering_options()))

int compare_fields(char str1[], char str2[], orderingoptions opts);
void sortmate(char *arr[], int size);

#endif /* ifndef SORT_H */
