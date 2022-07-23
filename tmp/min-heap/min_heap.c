#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

#define LEFT_CHILD(X)   ((X << 1) + 1)
#define RIGHT_CHILD(X)  ((X << 1) + 2)


node *get_min(Min_Heap h) {

    return &(h->A[0]);
}


/*! \brief Swap elements of an array
 *  \param[in] array reference, indices of elements to be swapped
 */
void swap(node *a, node *b) {

    node temp = *a;
    *a = *b;
    *b = temp;
    return;
}


/*! \brief min_heapify(): maintains the max-heap property
 * \param[in] heap array, index of node violating heap property
 * \retval: void
 */
void min_heapify(Min_Heap h, int i) {

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
        swap(&A[i], &A[smallest]);
        min_heapify(h, smallest);
    }

    return;
}


Min_Heap build_min_heap(node *A, const int size) {

    Min_Heap h = (Min_Heap)malloc(sizeof(min_heap));
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

/*
void minheapsort(int *A, const int size) {

    min_heap h;

    h.A = A;
    h.length = size;
    h.heap_size = size;

    build_min_heap(&h);

    for (int i = h.length - 1; i >= 1; --i) {
        swap(h.A, 0, i);
        --h.heap_size;
        min_heapify(&h, 0);
    }

    return;
}
*/

