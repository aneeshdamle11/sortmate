#include <ctype.h>
#include <string.h>
#include "sort.h"

#define LENGTH(str) strnlen(str, MAX_LINE_LENGTH)

// ret: equal=0, smaller=-ve, greater=+ve
int compare_char(char a, char b) {
    if ((isalpha(a) && isalpha(b)) && (a != b) && (tolower(a) == tolower(b)))
        return b - a;
    else
        return tolower(a) - tolower(b);
}

/*
function to compare 2 strings, with the comparison in the following manner:
there are 3 types of characters: numbers, alphabets and symbols
Only for comparison of smallcase and largecase alphabets, small are smaller
Else ASCII order
ret: -ve if str1 < str2, 0 if str1 == str2, +ve if str1 > str2
*/
int compare_lines(char str1[], char str2[]) {
    // check options
    int size1 = LENGTH(str1), size2 = LENGTH(str2);
    for (int i = 0; i < ((size1 < size2) ? size1 : size2); i++) {
        int res = compare_char(str1[i], str2[i]);
        if (res != 0) return res;
    }
    return size1 - size2;
}

/* wrapper function to checks flags before actual line comparison */
int is_swap_needed(char l1[], char l2[]) {
    return (rflag == 0 ? compare_lines(l1, l2) : compare_lines(l2, l1)) > 0;
}

void swap(char **s1, char **s2) {
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
    return;
}

void bubblesort(char *arr[], int size) {
    // at the end of each 'i' round, the largest element bubbles at the end
    while (size-- > 0)
        for (int j = 0; j < size; j++)
            if (is_swap_needed(arr[j], arr[j+1])) swap(&arr[j], &arr[j+1]);
    return;
}
