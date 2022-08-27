#ifndef HEAP_H
#define HEAP_H (1)


typedef struct {
    int key, index;
} node;

typedef struct {
    node *A;                /* array of nodes */
    int length, heap_size;  /* length(array), size(heap) */
} heap;

typedef heap* Heap;

/* Function prototypes */

/* 1 MIN-HEAP */

/*! \brief Get the minimum node from minheap of nodes
 * \param[in] minheap ref
 * \retval node containing minimum key
 */
node *get_min(Heap h);


/*! \brief min_heapify(): maintains the min-heap property
 * \param[in] heap array, index of node violating min-heap property
 * \retval void
 */
void min_heapify(Heap h, int i);


/*! \brief build_min_heap(): builds min heap from any integer array
 * \param[in] integer array, size of array
 * \retval heap ref
 */
Heap build_min_heap(node *A, const int size);


/* 2 MAX-HEAP */

/*! \brief Get the maximum node from max-heap of nodes
 * \param[in] maxheap ref
 * \retval node containing maximum key
 */
node *get_max(Heap h);


/*! \brief max_heapify(): maintains the max-heap property
 * \param[in] heap array, index of node violating max-heap property
 * \retval void
 */
void max_heapify(Heap h, int i);


/*! \brief build_max_heap(): builds max heap from integer array
 * \param[in] integer array, size of array
 * \retval heap ref
 */
Heap build_max_heap(node *A, const int size);

#endif  /* HEAP_H*/
