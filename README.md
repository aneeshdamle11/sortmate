# sortmate
Sorts **crazy** large files of numbers or text!

## Usage:
1. If file to be sorted is a text file
> 
> cd text
>
> make
>
> ./txt filename

2. If file to be sorted contains only numbers
> cd num
>
> make
>
> ./num filename

3. An additional option to generate a file of random numbers
> cd dat
>
> cc numbers.c
>
> ./a.out count
>
> File will be generated in numbers.txt

The underlying implementation uses various sorting techniques, and is fun to implement.

## Scope for improvement
1. Unique functionalities of both text and number implementations could be merged.
2. Underlying modifications could be automated.

### TODO: Add pthreading to improve on sorting
