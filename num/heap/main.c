#include <stdio.h>
#include "min_heap.h"

int main(void) {
    int arr[6] = {3, 56, 7, 10, -9, 0};
    minheapsort(arr, 6);
    for (int i = 0 ; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return 0;
}
