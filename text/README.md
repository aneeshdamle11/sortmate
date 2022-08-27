# sortmate
## Sorting textfiles!

Sorts **crazy** large files of numbers or text!

## Usage:
> 
> cd text
>
> make
>
> ./txt filename

Implementation is done using a linked-list structure.
The idea is to store arbitrarily long lines in terms of length and number, in a linked-list data structure.
The stored list is sorted using merge sort.

## Further improvements:
1. Options like column sort, reverse sort, ASCII representational-sort could be added.
2. Corner case handling can improve.
3. Concept of external sorting could be merged from numbers implementation. 
