#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define LEFT_CHILD(X)   ((X << 1) + 1)
#define RIGHT_CHILD(X)  ((X << 1) + 2)


node *get_min(Heap h) {
    return &(h->A[0]);
}


/*! \brief Swap elements of an array
 *  \param[in] array reference, indices of elements to be swapped
 */
void swap_min(node *a, node *b) {

    node temp = *a;
    *a = *b;
    *b = temp;
    return;
}


/*! \brief min_heapify(): maintains the min-heap property
 * \param[in] heap array, index of node violating heap property
 * \retval: void
 */
void min_heapify(Heap h, int i) {

    int l;              /* index of left-subtree root */
    int r;              /* index of right-subtree root */
    int smallest;        /* index of smallest element among comparison */
    node *A = h->A;

    l = LEFT_CHILD(i);
    r = RIGHT_CHILD(i);

    if (l < h->heap_size && A[l].key < A[i].key)
        smallest = l;
    else
        smallest = i;

    if (r < h->heap_size && A[r].key < A[smallest].key)
        smallest = r;

    if (smallest != i) {
        swap_min(&A[i], &A[smallest]);
        min_heapify(h, smallest);
    }

    return;
}


Heap build_min_heap(node *A, const int size) {

    Heap h = (Heap)malloc(sizeof(heap));
    if (!h) {
        printf("Could not malloc a minheap :)\n");
        return NULL;
    }

    h->A = A;
    h->length = size;
    h->heap_size = size;

    for (int i = h->heap_size/2; i >= 0; --i)
        min_heapify(h, i);

    return h;
}

