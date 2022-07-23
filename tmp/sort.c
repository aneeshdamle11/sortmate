#include <stdio.h>
#include "sort.h"


// Bubble Sort
void bubblesort(int arr[], int n)
{
    int i, j, temp;
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - 1 - i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return;
}


// Selection Sort
void selectionsort(int *arr, int n) {
    int j, min, temp;
    if (n == 1) {
        return;
    }
    // Find minimum value in remaining array
    for (j = 0, min = j; j < n; j++) {
        if (*(arr + j) < *(arr + min))
        {
            min = j;
        }
    }
    // Swap minimum value in place
    temp = *(arr);
    *(arr) = *(arr + min);
    *(arr + min) = temp;

    // Recursive case
    selectionsort(arr + 1, n - 1);
    return;
}


// Insertion Sort
void insertionsort(int arr[], int n) {
    int i, j, k;
    for (i = 1; i < n; i++)
    {
        k = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > k)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = k;
    }
    return;
}

// Merge two sorted arrays
void merge(int a[], int b[], int n1, int n2) {
    int c[n1 + n2]; 

    if (n1 == 0 && n2 == 0)
    {
        printf("Array absent\n");
        return;
    }

    int i = 0, j = 0, k = 0;
    while (1)
    {
        if (a[i] <= b[j])
        {
            c[k++] = a[i++];
        }
        else if (b[j] < a[i])
        {
            c[k++] = b[j++];
        }

        if (i == n1 || j == n2)
        {
            break;
        }
    }

    if (i == n1)
    {
        while (k < n1 + n2)
        {
            c[k++] = b[j++];
        }
    }
    else if (j == n2)
    {
        while (k < n1 + n2)
        {
            c[k++] = a[i++];
        }
    }
    // Update sub-arrays
    k = 0;
    for(i = 0; i < n1; i++)
    {
        a[i] = c[k++];
    }
    for(j = 0; j < n2; j++)
    {
        b[j] = c[k++];
    }
    return;
}


// Merge sort
void mergesort(int arr[], int len) {
    if (len == 1) {
        return;
    }
    // Sort the left half
    mergesort(arr, len / 2);
    // Sort the right half
    mergesort((arr + len / 2), len / 2);
    // Merge the sorted two halves
    merge(arr, (arr + len / 2), len / 2, len / 2);

    return;
}

// Display array contents
void display_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

