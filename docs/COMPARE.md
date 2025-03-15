The base of any sort algorithm is how its 2 *elements* are compared. In `sortmate`, this translates to how 2 *lines* are compared. This doc explains this comparison function.

### Comparison
```
$ sort sample
(
-
1
44
5
aBc
abc
def
```

#### Implementing the comparison
Any sort algorithm works by answering the question -
"Should the current 2 elements need to be swapped?".
The number of times this question is asked determines its time complexity.

This notion gives a basic design of the solution:

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

Note that a basic idea of the design is written out here, without diving into the various complex edge cases. These can be pored over in the code.

