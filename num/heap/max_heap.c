#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define LEFT_CHILD(X)   ((X << 1) + 1)
#define RIGHT_CHILD(X)  ((X << 1) + 2)


node *get_max(Heap h) {
    return &(h->A[0]);
}


/*! \brief Swap elements of an array
 *  \param[in] array reference, indices of elements to be swapped
 */
void swap_max(node *a, node *b) {

    node temp = *a;
    *a = *b;
    *b = temp;
    return;
}


/*! \brief max_heapify(): maintains the max-heap property
 * \param[in] heap array, index of node violating heap property
 * \retval: void
 */
void max_heapify(Heap h, int i) {

    int l;              /* index of left-subtree root */
    int r;              /* index of right-subtree root */
    int largest;        /* index of largest element among comparison */
    node *A = h->A;

    l = LEFT_CHILD(i);
    r = RIGHT_CHILD(i);

    if (l < h->heap_size && A[l].key > A[i].key)
        largest = l;
    else
        largest = i;

    if (r < h->heap_size && A[r].key > A[largest].key)
        largest = r;

    if (largest != i) {
        swap_max(&A[i], &A[largest]);
        max_heapify(h, largest);
    }

    return;
}


Heap build_max_heap(node *A, const int size) {

    Heap h = (Heap)malloc(sizeof(heap));
    if (!h) {
        printf("Could not malloc a maxheap :)\n");
        return NULL;
    }

    h->A = A;
    h->length = size;
    h->heap_size = size;

    for (int i = h->heap_size/2; i >= 0; --i)
        max_heapify(h, i);

    return h;
}

