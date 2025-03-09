#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"
#include "io.h"

#define IS_DICTIONARY_CHAR(X) (isblank(X) || isalnum(X))
#define IS_PRINTABLE_CHAR(X) (X >= 32 && X <= 126)

void trim_start(char **s) {
    while (*s && isblank(**s)) (*s)++;
}

/*
function to compare 2 strings - ASCII order: "LC_ALL=C"
ret: -ve if str1 < str2, 0 if str1 == str2, +ve if str1 > str2
*/
int compare_fields(char s1[], char s2[], orderingoptions opts) {
    if (!s1 || !s2) return (s1 == NULL? (s2 == NULL? 0 : 1) : -1);
    int result = 0;
    if (opts.b) { trim_start(&s1), trim_start(&s2); }
    if (opts.n)
        result = atoi(s1) - atoi(s2);
    else {
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
            result = opts.f? toupper(s1[i]) - toupper(s2[j]) : s1[i] - s2[j];
            if (result) break;
        }
    }
    return opts.r ? result * -1 : result;
}

/* wrapper function to checks flags before actual line comparison */
int is_swap_needed(char *l1, char *l2) {
    if (!l1 || !l2) return (l2 == NULL? 1 : 0);
    int result = 0;
    if (global_options.k) {
        key *k = global_options.k;
        while (k) {
            // get fields
            char *field1 = l1, *field2 = l2;
            for (int i = 1; i < k->nfield; i++) {
                if (field1) field1 = strchr(field1, ' ');
                if (field2) field2 = strchr(field2, ' ');
            }
            // compare fields
            if (IS_ORDERING_OPTIONS_EMPTY(k->ordering_options)) {
                result = COMPARE_GLOBAL_FIELDS(field1, field2);
            } else {
                result = compare_fields(field1, field2, k->ordering_options);
            }
            // next key if needed
            if (result == 0) k = k->next;
            else break;
        }
    } else { // default to line comparison
        result = COMPARE_GLOBAL_FIELDS(l1, l2);
    }
    if (result == 0 && global_options.s == 0) { // last resort comparison
            result = COMPARE_EMPTY_FIELDS(l1, l2);
    }
    return result > 0;
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
