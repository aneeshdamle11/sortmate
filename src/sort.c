#include <stdio.h>
#include <stdlib.h>
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

int howmanychars(char str[], char c) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) if (str[i] == c) count++;
    return count;
}

/* wrapper function to checks flags before actual line comparison */
int is_swap_needed(char l1[], char l2[]) {
    // TODO: Simplify this snippet
    if (kflag == 1) {
        int spaces1 = howmanychars(l1, ' '), spaces2 = howmanychars(l2, ' ');
        if (kopt > (spaces1 + 1) && kopt > (spaces2 + 1)) {
            return rflag ^ (compare_lines(l1, l2) > 0);
        } else if (kopt > spaces1 + 1) {
            return rflag ^ 0;
        } else if (kopt > spaces2 + 1) {
            return rflag ^ 1;
        }
        char *kstr1 = l1, *kstr2 = l2;
        for (int i = 1; i < kopt; i++) {
            kstr1 = strchr(kstr1, ' ');
            kstr1++;
            kstr2 = strchr(kstr2, ' ');
            kstr2++;
        }
        int kres = compare_lines(kstr1, kstr2);
        if (kres != 0) {
            return rflag ^ (kres > 0);
        }
    }

    // TODO: Simplify this snippet
    if (nflag == 1) {
        if (starts_with_num(l1) && starts_with_num(l2)) {
            int res1 = get_starting_num(l1);
            int res2 = get_starting_num(l2);
            if (res1 != res2) {
                return rflag ^ (res1 > res2);
            }
        } else if (starts_with_num(l1)) {
            return rflag ^ 1;
        } else if (starts_with_num(l2)) {
            return rflag ^ 0;
        }
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
                if (cflag == 1)
                    printf("disorder: %s\n", arr[j+1]), exit(EXIT_SUCCESS);
                else
                    swap(&arr[j], &arr[j+1]);
            }
        }
    }
    if (cflag == 1) return exit(EXIT_SUCCESS);
    return;
}
