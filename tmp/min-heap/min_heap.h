#ifndef MIN_HEAP_H
#define MIN_HEAP_H (1)


typedef struct node {
    int key, index;
} node;

typedef struct min_heap {
    node *A;                /* array of nodes */
    int length, heap_size;  /* length(array), size(heap) */
} min_heap;

typedef min_heap* Min_Heap;

/* Function prototypes */

/*! \brief Get the minimum node from minheap of nodes
 * \param[in] minheap ref
 * \retval node containing minimum key
 */
node *get_min(Min_Heap h);


/*! \brief min_heapify(): maintains the min-heap property
 * \param[in] heap array, index of node violating heap property
 * \retval void
 */
void min_heapify(Min_Heap h, int i);

/*! \brief build_min_heap(): builds min heap from any integer array
 * \param[in] integer array, size of array
 * \retval heap ref
 */
Min_Heap build_min_heap(node *A, const int size);


/*! \brief minheapsort(): sorts an integer array using a heap
 * \param[in] integer array, size of array
 * \retval void
 */
void minheapsort(int *A, const int size);

#endif  /*MIN_HEAP_H*/
