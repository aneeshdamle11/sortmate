The base of any sort algorithm is how its 2 *elements* are compared. In `sortmate`, this translates to how 2 *lines* are compared. This doc explains the thinking behind designing this comparison function.

## The Comparison
```
$ sort sample
(
-
1
44
5
abc
Abc
ABC
def
```

Realising where `sort` can significantly change its behavior, there are 3 types
of characters:

1. **Alphabets**:
- Capital letters come after small, and the alphabetical order is maintained in
  capital-small comparisons
- *IMP: Letters are case-insensitively compared first*

2. **Numbers**
- For -n option, numerical values are sorted in after alphabets and symbols
  (non-numerical)

3. **Symbols (non alphanumeric)**
- Symbols are sorted according to ASCII values, and no option changes this
  behavior.

## The Implementation
Any sort algorithm works by answering a question of "whether the current 2 elements need to be swapped". The number of times this question is asked is what determines its time complexity.

This notion gives us a basic design of the solution:

```
is_swap_needed(line1, line2):
	res = compar(line1, line2)
	if res > 0, return true
	else return false
```

The compar function would be a black box:
```
compar(l1, l2)
compare tolower(l1[i]) and tolower(l2[i])
ret:
  -ve | if str1 < str2
  0   | if str1 == str2
  +ve | if str1 > str2
```

This doc gives a basic idea of the design to be followed without diving into the various complex edge cases, which are handled in the code.

## Function pointers
The compar idea is generic for any sorting algorithm, and thus would be used to scale the algorithms.
Each such algorithm should use the same compar function - bubblesort, selection sort, qsort, merge sort.
Since we provide an option to choose the sorting algorithm, each such algorithm has an option number attached to it.

If the parameters of each sorting algorithm are the same, it would be easier to call them by keeping a helper function:
```
sort_switcher(opt):
	if (opt == 1)
		bubblesort(arg1, arg2, arg3)
	else if (opt == 2)
		mergesort(arg1, arg2, arg3)
	...
```

The C Programming Language provides an interesting functionality where we can *refer* to custom functions like we *refer* variables.
This has 2 advantages:
1. qsort demands that a compar function pointer be passed.
2. We would be able to call the function more easily:

```
sorting_algo = [bubblesort, mergesort, ...]
sorting_algo[opt](arg1, arg2, &compar)
```

## Conclusion
- By separating the compar function from the sorting algorithm, the solution can be scaled to fit in any number of algorithms.
- Using function pointers makes handling the algorithm selection easier.

