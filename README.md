# sortmate
> v2.0

A system to sort unlimited number of endless lines. Yes, really.

## Installation
```bash
$ make
```

## Usage
```
$ ./sortmate [OPTIONS] filename
```

## Cleanup
```
$ make clean
```

## How does the system work?
TL DR; The system does exactly what it says. Give it the input content and it will return the same input sorted. It refers to the ASCII nomenclature.
> sort [space separated options] [input file]

### Options Provided
TODO: Explain all the options with a single example
- : basic sort
- -r: reverse the order of the sort
- -n: sort by numerical value
- -k: sort by column or field
- -c: check for sorted input; do not sort

References:
1. https://en.wikipedia.org/wiki/Sort_(Unix)
2. `man sort` (or) https://www.man7.org/linux/man-pages/man1/sort.1.html

## Diving a bit deep

The base of any sort algorithm is how its 2 *elements* are compared. In `sortmate`, this translates to how 2 *lines* are compared. This doc explains the thinking behind designing this comparison function.

### Comparison
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

#### Implementing the comparison
Any sort algorithm works by answering a question of "whether the current 2 elements need to be swapped". The number of times this question is asked determines its time complexity.

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

This doc gives a basic idea of the design to be followed without diving into the various complex edge cases, which can be pored over in the code.

### Design of sortmate
It would be help to clear up a confusing point early on -
```
The RAM would be defined in terms of number of lines for simplicity.
This will avoid the issue of scaling horizontally as handling this would 
involve complexity that won't add anything new to the scope of the project.
```

Let's start with a very basic design and build up from there.

```
START
sortmate()
	buffer = get_input
	sort(buffer)
	output buffer contents
STOP
```
Since we discussed about the sorting algorithm build up, it would be safe to assume this would work. Here, the system stumbles upon some practicalities: the RAM, and hence the `buffer` space is limited :) We can only sort those many lines that can fit in the RAM. How do we compare the lines that have already been sorted in the RAM, the lines that are being sorted and the lines that are still in the secondary storage, waiting to be read?
Ans: External sort

Modified pseudocode to fit this case:
```
START
    get_flags
    while (more input)
        while (buffer not full)
            buffer += get_line
        sort(buffer)
        clear contents of buffer in a temporary space => a 'chunk'
    output = merge_chunks
    display_output
STOP
```

How merging the chunks would work:
```
Example 0*:
Suppose the available RAM space is 100 lines.
Suppose input file has 1000 lines.
<============ We will need 1000 / 100 = 10 tmp files ===========>
We take first 100 lines, sort them in RAM, and store them in tmp1
We take next  100 lines, sort them in RAM, and store them in tmp2
...
We take last 100 lines, sort them in RAM, and store them in tmp10

Now, take first line from each tmp file (so 10 lines), sort them in RAM.
<============ Ensure this buffer (10 lines) fits in RAM ==========>
We output the smallest line and swap it with the "next line".
"next line": line from tmp file from where the smallest line was picked
We do this process till the RAM is empty again.
```

Since the system RAM is still finite, `merge_chunks` would also be required to fit in in the same RAM:
```
Example 1*:
Suppose available RAM space is 100 lines.
Suppose input file has 100000 (1L) lines.
Tmp files: 1000
We sort the input file in 1000 files (tmp0, tmp1, ..., tmp1000)

But this time, we can only take first lines of the first 100 files in RAM.
How to tackle this issue?
We sort the first 100 files -> tmptmp1
We sort the next  100 files -> tmptmp2
...
We sort the next 100 files -> tmptmp100
Now again we have 100 files -> this fits in RAM.
```

The newly modified pseudo-code would look something like this:
```
START
    RAM: Number of lines that fit in
    get_flags
    while (more input)
        while (buffer not full)
            buffer += get_line
        sort(buffer)
        tmp_output_space or chunk = clear buffer
    while (number of chunks > RAM)
        tmp_output_space or chunk = merge_chunks(first RAM lines)
    output = merge_chunks
    display_output
STOP
```

### Calculating the time complexity

Referring to the latest pseudocode, suppose the system has to read N lines.
1. The system inputs RAM lines each time, sort them, and push them in a chunk written to secondary storage.
So, the time complexity for reading, sorting and creating chunks is **O(n)**,
since the sorting occurs on a fixed number of lines each time.
2. For merging the chunks, the number of iterations on an average would lie somewhere around log (total input lines) base (RAM space).
So the time complexity would be **O(log(N))**.
How to verify this time complexity? Ahh, this is left to the reader.
3. For writing the lines as output would again be **O(n)**

So the total time complexity comes out as **O(n)**.

### Building a portable code
About the code written so far, all a person can confidently say is it works on the system where this code is written. This ought to change if it is to be used as an open source utility.

How to guage whether the code we've written will run the same way on other Linux systems as well?

Solution: **GNU Build Tools - Autoconf, Automake and autoreconf.**

```
Suppose we have a code spanning across multiple files. For example
.
├── include
│   ├── io.h
│   └── sort.h
├── src
│   ├── io.c
│   ├── main.c
│   └── sort.c

Suppose we compile an executable out of this code structure with the following
command:
$ gcc -o sortmate main.c io.c sort.c -Iinclude

Or better still, we could write a Makefile that handles this with a simple
$ make
$ cat Makefile
make:
  gcc -o sortmate main.c io.c sort.c -Iinclude

But, the issue with portability is we don't know:
1. which compiler the other system has
2. the C constructs supported in the other system
3. C functions or headers with different names
4. any other libraries if required

It's pertinent to write a code that checks the system before compiling a program
according to the system specifications. Here's where GNU Build Tools come in.
The docs/autotools.pdf is a great reference to learn autotools.
For the sake of brevity:
- *configure, config.h.in, Makefile.in and src/Makefile.in* are the files used to
  produce *Makefile, src/Makefile, config.h*
- config* has to do with portability, and *.in files with the code compilation.
- Things are made simpler by autoreconf: We write a file named configure.ac
  And it is converted to configure and config.h.in
  Alongwith conversion of *.in files to respective Makefiles.
- This is later built into an executable with a `make` and
  installed in a system with `make install` as a command-line utility.
```


### What's next?
Documented some ideas and future tasks that would be interesting to implement, and explained why haven't been done so far:

1. Function pointers

This section explains a very useful idea in C - function pointers. Why they weren't included in the code is explained below in parts.

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

- Thus, by separating the compar function from the sorting algorithm, the solution can be scaled to fit in any number of algorithms, and
- Using function pointers makes handling the algorithm selection easier.

Why weren't they included?
- The main purpose behind including function pointers was learning how to use them. Since the prose was read while creating a documentation, the learning part was already done.
- Function pointers would work great for scaling the sorting algorithms.
- This project plans to include a finite amount of algorithms initially, and hard coding the solution was more readable.

2. Parallelization

Explanation of why this idea could be fruitful:
```
Suppose it takes 1 sec to sort 2 lines.
For 10 lines, it will involve say 100 comparisons -> 100 seconds
For n lines, it takes n^2 seconds.

Suppose RAM can fit in 20 lines.
Suppose input file is 1000 lines.
<============================== NORMAL ==================================>
Take first 20 lines, sort them, and store them in tmp1 == 400s
...
Take last 20 lines, sort them, and store them in tmp50 == 400s
================================================ TOTAL == 20000s
Time: 20000s, files: 50
Then, we create a heap and do the rest of the operations.
Estimated time: 
<============================= PARALLEL1 ================================>
Suppose we have 2 parallel threads.
Thread 1:
RAM = 10 lines. Input = 500 lines
Take first 10 lines, sort them, and store them in tmp1_1 == 100s
...
Take last 10 lines, sort them, and store them in tmp1_50 == 100s
-------------------------------------------------- TOTAL == 5000s
Thread 2:
RAM = 10 lines. Input = 500 lines
Take first 10 lines, sort them, and store them in tmp1_1 == 100s
...
Take last 10 lines, sort them, and store them in tmp1_50 == 100s
-------------------------------------------------- TOTAL == 5000s
Time: 5000s, files: 100
<============================= PARALLEL2 ================================>
Suppose we have 4 parallel threads.
Thread 1:
RAM = 5 lines. Input = 250 lines
Take first 5 lines, sort them, and store them in tmp1_1 == 25s
...
Take last 5 lines, sort them, and store them in tmp1_50 == 25s
-------------------------------------------------- TOTAL == 1250s
Time: 1250s,files:50x4=200
<========================================================================>
For n parallel threads, time=O/n^2, space=S*n
--------------------------------------------------------------------------
heapsort time increases in log(n), but sort time decreases O(1/n^2).
Thus, parallelization consumes more space, but compensates in speed.
```

In our case, we are sorting only lines within our RAM, and the RAM space is finite. So the sorting is going to remain O(1) as the total numbers to be sorted are limited. Thus, though it tends to be tempting, parallelism here won't be of much help. But this solution can be used if the design is twirked or on the I/O.

3. More sorting algorithms!

This would always help :)