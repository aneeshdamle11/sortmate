#include <stdio.h>
#include <string.h>
#include "sort.h"

int num = 0;
int success = 0;

// Helper function to print test results
void runTest(char str1[], char str2[], int expected) {
    printf("[TEST %d] ", num);

    int result = compare_lines(str1, LENGTH(str1), str2, LENGTH(str2));
    printf("Compare \"%s\" and \"%s\": ", str1, str2);
    if (result == expected) success++, printf("PASSED\n");
    else printf("FAILED (Expected: %d, Got: %d)\n", expected, result);

    num++;
    return;
}

int main() {
    printf("Script to test string comparison. Running tests...\n");

    // Test 1: Both strings are equal
    runTest("abc", "abc", 0);

    // Test 2: First string is smaller
    runTest("abc", "abcd", 0);

    // Test 3: First string is greater
    runTest("abcd", "abc", 1);

    // Test 4: Case-sensitive comparison
    runTest("abc", "ABC", 0);  // Lowercase smaller than uppercase

    // Test 5: Symbol comparison
    runTest("abc!", "abc#", 0);

    // Test string numeric size
    // Test 6: Symbol vs alphabet
    runTest("abc!", "abcA", 0);  // Symbol smaller than alphabet (ASCII order)

    // Test 7: Numeric comparison
    runTest("123", "124", 0);     // Numeric characters compared as ASCII
    runTest("124", "123", 1);     // Greater numeric value

    // Test 8: Mixed letters and numbers
    runTest("abc123", "abc122", 1);  // Last numeric character decides
    runTest("abc123", "abc124", 0);

    // Test 9: Length mismatch with equal prefix
    runTest("abc", "abcd", 0);     // First string is smaller
    runTest("abcd", "abc", 1);     // First string is greater

    // Test 10: Complex mix of symbols, numbers, and letters
    runTest("a1!c", "a1#c", 0);   // Symbol '!' vs '#'
    runTest("a1C", "a1c", 1);      // 'C' (uppercase) is greater than 'c' (lowercase)
    runTest("a1c", "a1C", 0);     // Lowercase smaller than uppercase

    // Test 11: Empty strings
    runTest("", "", 0);            // Both empty
    runTest("", "abc", 0);         // Empty string smaller
    runTest("abc", "", 1);         // Non-empty string greater

    printf("\n[TEST SUMMARY]:\nTOTAL: %d\tSUCCESS: %d\tFAILED: %d\n", num, success, num-success);
    return 0;
}
