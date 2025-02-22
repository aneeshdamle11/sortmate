#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"
#include "io.h"

#define LENGTH(str) (strnlen(str, MAXLEN))

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

int starts_with_num(char str[]) {
    if (LENGTH(str) > 0) return isdigit(str[0]);
    else return 0;
}

int get_starting_num(char str[]) {
    int n = LENGTH(str);
    int num = 0;
    int i = 0;
    while (i < n && isdigit(str[i])) {
        num = num * 10;
        num += str[i] - '0';
        i++;
    }
    return num;
}

int howmanyspaces(char *s) {
    int count = 0;
    while (*s) {
        if (isblank(*s)) {
            count++;
            while (*s && isblank(*s)) s++;
        } else s++;
    }
    return count;
}

void trim_start(char **s) {
    while (*s && isblank(**s)) (*s)++;
}

/* wrapper function to checks flags before actual line comparison */
int is_swap_needed(char *l1, char *l2) {
    if (!l1 || !l2) return (l2 == NULL? 1 : 0);
    if (nflag == 1) {
        if (starts_with_num(l1) && starts_with_num(l2)) {
                int res1 = get_starting_num(l1), res2 = get_starting_num(l2);
                return res1 > res2;
            }
        else if (starts_with_num(l1)) return 1;
        else if (starts_with_num(l2)) return 0;

    }
    return rflag ^ (compare_lines(l1, l2) > 0);
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
    return res;
}

void sortmate(char *arr[], int size) {
    switch (sopt) {
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
