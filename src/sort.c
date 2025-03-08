#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"
#include "io.h"

// ret: equal=0, smaller=-ve, greater=+ve
int compare_char(char a, char b) {
    return a - b;
}

/*
function to compare 2 strings, with the comparison in the following manner:
there are 3 types of characters: numbers, alphabets and symbols
Always ASCII order: "LC_ALL=C"
ret: -ve if str1 < str2, 0 if str1 == str2, +ve if str1 > str2
*/
int compare_lines(char str1[], char str2[]) {
    if (!str1 || !str2) return (str1 == NULL? (str2 == NULL? 0 : 1) : -1);
    // check options
    int size1 = LENGTH(str1), size2 = LENGTH(str2);
    for (int i = 0; i < ((size1 < size2) ? size1 : size2); i++) {
        int res = compare_char(str1[i], str2[i]);
        if (res != 0) return res;
    }
    return 0;
}

void trim_start(char **s) {
    while (*s && isblank(**s)) (*s)++;
}

/* wrapper function to checks flags before actual line comparison */
int is_swap_needed(char *l1, char *l2) {
    if (!l1 || !l2) return (l2 == NULL? 1 : 0);
    // TODO: check for keys
    // TODO: default to line comparison
    return compare_lines(l1, l2);
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
                    printf("disorder: %s", arr[j+1]), cleanup(), exit(EXIT_SUCCESS);
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
                    printf("disorder: %s", arr[j+1]), cleanup(), exit(EXIT_SUCCESS);
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
        printf("disorder: %s", (char*)str2), cleanup(), exit(EXIT_SUCCESS);
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
