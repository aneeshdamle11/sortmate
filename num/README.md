# sortmate
Sorts **crazy** large files of numbers or text!

## Sorting numbers!

## Usage:

> cd num
>
> make
>
> ./num -r/s filename
>
> Options included: r (reverse sort), n (normal sort)

### FUN NOTE:
> In external.h, try:
> * Changing CHUNK_SIZE and
> * Corresponding file extensions while building temporary files
> 
> This implementation has been intentionally left changeable and not generalised to understand the concept of external sort by actually making simple changes!

The underlying implementation uses the external sorting algorithm to sort arbitrarily large number of numbers!
### Idea:
* Quicksort
* Heapsort
* External sorting with temporary files

## Scope for improvement
1. More options could be added
2. Arbitrarily long numbers could be stored by merging the concept of linked-lists.
