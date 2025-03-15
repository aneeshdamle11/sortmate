### Design of sortmate
It would be help to clear up a confusing point early on -
```
The RAM would be defined in terms of number of lines for simplicity.
This will avoid the issue of scaling horizontally as handling this would 
involve complexity that won't add anything new to the scope of the project.
```

Initially thought-out pseudocode:
```
START
sortmate()
	buffer = get_input
	sort(buffer)
	output buffer contents
STOP
```

With this pseudocode, the system stumbles upon some practicalities: the RAM, and hence the `buffer` space is limited; we can only sort those many lines that can fit in the RAM.

How do we compare the lines that have already been sorted in the RAM, the lines that are being sorted and the lines that are still in the secondary storage, waiting to be read?

### External Sorting
The idea here is to only sort the lines that can fit in a RAM at a time and then merge the already sorted files.

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


