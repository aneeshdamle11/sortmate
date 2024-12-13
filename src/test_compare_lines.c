#include <stdio.h>
#include "sort.h"

int num = 0;
int success = 0;

// Helper function to print test results
void run_test(char str1[], char str2[], int expected) {
    printf("[TEST %d] ", num);

    int res = compare_lines(str1, str2);
    printf("Compare \"%s\" and \"%s\": ", str1, str2);
    if ((res < 0 && expected < 0) || (res > 0 && expected > 0) || (res == expected)) {
        success++;
        printf("PASSED\n");
    } else {
        printf("FAILED (Expected: %d, Got: %d)\n", expected, res);
    }

    num++;
    return;
}

int rflag = 0;

int main() {
    printf("Script to test string comparison. Running tests...\n");

    run_test("abc", "abc", 0);
    run_test("abc", "abcd", -1);
    run_test("abcd", "abc", 1);
    run_test("abc", "ABC", -1); // Lowercase smaller than uppercase
    run_test("abc!", "abc#", -1);
    run_test("abc!", "abcA", -1); // ASCII order
    run_test("abc123", "abc122", 1); // Last numeric character decides
    run_test("abc123", "abc124", -1);
    run_test("a1!c", "a1#c", -1); // Symbol '!' vs '#'
    run_test("", "", 0); // Both empty
    run_test("", "abc", -1); // Empty string smaller
    run_test("abc", "", 1); // Non-empty string greater

    printf("\n[TEST SUMMARY] TOTAL: %d\tSUCCESS: %d\tFAILED: %d\n", num, success, num-success);
    return 0;
}
