#include <stdio.h>
#include "sort.h"

int num = 0;
int success = 0;

// Helper function to print test results
void run_test(char str1[], char str2[], int expected) {
    printf("[TEST %d] ", num);

    printf("\"%s\" VS \"%s\": ", str1, str2);
    int result = compare_lines(str1, str2);
    if ((expected == 0) ? (result == 0) : (result * expected > 0))
        success++, printf("PASSED\n");
    else
        printf("FAILED (Expected: %d, Got: %d)\n", expected, result);

    num++;
    return;
}

int rflag = 0, nflag = 0, kflag = 0, kopt = 0, cflag = 0;
char sopt = 'x';

int main() {
    printf("Script to test string comparison. Running tests...\n");

    run_test("abc", "abc", 0);
    run_test("abc!", "abcA", -1);
    run_test("a1!c", "a1#c", -1);
    run_test("abc", "abcd", -1);
    run_test("abcd", "abc", 1);
    run_test("abc", "ABC", -1);
    run_test("abc123", "abc121", 1);
    run_test("", "", 0); // Both empty
    run_test("", "abc", -1); // Empty string smaller
    run_test("abc", "", 1); // Non-empty string greater

    printf("\n[SUMMARY] TOTAL: %d (SUCCESS: %d FAILED: %d)\n", num, success, num-success);
    return 0;
}
