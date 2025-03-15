### What's next?

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

