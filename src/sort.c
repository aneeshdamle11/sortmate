#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"
#include "io.h"

#define IS_DICTIONARY_CHAR(X) (isblank(X) || isalnum(X))
#define IS_PRINTABLE_CHAR(X) (X >= 32 && X <= 126)

/*
function to compare 2 strings - ASCII order: "LC_ALL=C"
ret: -ve if str1 < str2, 0 if str1 == str2, +ve if str1 > str2
*/
void trim_start(char **s) {
    while (*s && isblank(**s)) (*s)++;
}

int compare_fields(char s1[], char s2[], orderingoptions opts) {
    if (!s1 || !s2) return (s1 == NULL? (s2 == NULL? 0 : 1) : -1);
    if (opts.b) { trim_start(&s1), trim_start(&s2); }
    for (int i = 0, j = 0; !(s1[i] == '\0' && s2[j] == '\0'); i++, j++) {
        // handle dictionary order
        if (opts.d) {
            if (!(IS_DICTIONARY_CHAR(s1[i]))) i++;
            if (!(IS_DICTIONARY_CHAR(s2[j]))) j++;
        }
        // handle printable characters
        if (opts.i) {
            if (!(IS_PRINTABLE_CHAR(s1[i]))) i++;
            if (!(IS_PRINTABLE_CHAR(s2[j]))) j++;
        }
        // handle case folding
        int result = opts.f? toupper(s1[i]) - toupper(s2[j]) : s1[i] - s2[j];
        if (result) return result;
    }
    return 0;
}

/* wrapper function to checks flags before actual line comparison */
int is_swap_needed(char *l1, char *l2) {
    if (!l1 || !l2) return (l2 == NULL? 1 : 0);
    // TODO: check for keys
    // default to line comparison
    int result = COMPARE_GLOBAL_FIELDS(l1, l2);
    if (result != 0) return result > 0;
    else {
        if (global_options.s == 1) {
            return result;
        } else { // last resort comparison
            return COMPARE_EMPTY_FIELDS(l1, l2) > 0;
        }
    }
    return 0;
}

void swap(char **s1, char **s2) {
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
    return;
}

void bubblesort(char *arr[], int size) {
    // at the end of each 'i' round, the largest element bubbles at the end
    while (size-- > 0) {
        for (int j = 0; j < size; j++) {
            if (is_swap_needed(arr[j], arr[j+1])) {
                if (global_options.c == 1) {
                    printf("disorder: %s\n", arr[j+1]), cleanup(), exit(EXIT_SUCCESS);
                }
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
    return;
}

void selectionsort(char *arr[], int size) {
    // select the smallest element among the current, push it at the front
    for (int i = 0; i < size; i++) {
        int smallestidx = i;
        for (int j = i+1; j < size; j++) {
            if (is_swap_needed(arr[smallestidx], arr[j])) {
                if (global_options.c == 1) {
                    printf("disorder: %s\n", arr[j+1]), cleanup(), exit(EXIT_SUCCESS);
                }
                smallestidx = j;
            }
        }
        swap(&arr[i], &arr[smallestidx]);
    }
    return;
}

int is_qsort_swap_needed(const void* a, const void* b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    int res = is_swap_needed((char*)str1, (char*)str2);
    if (res == 1 && global_options.c == 1) {
        printf("disorder: %s\n", (char*)str2), cleanup(), exit(EXIT_SUCCESS);
    }
    return res;
}

void sortmate(char *arr[], int size) {
    switch (global_options.x) {
        case 'b':
            bubblesort(arr, size);
            break;
        case 'q':
            qsort(arr, size, sizeof(char*), is_qsort_swap_needed);
            break;
        case 's':
            selectionsort(arr, size);
            break;
        default:
            bubblesort(arr, size);
            break;
    }
    return;
}
