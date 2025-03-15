## sortmate 2.0

A utility to sort unlimited number of endless lines, using the external sorting technique.

### Installation
```bash
$ autoreconf --install
$ ./configure
$ make # builds an executable in src/
$ make install # builds an executable like a shell command - sortmate
$ make dist # builds a distributable package
```

### Usage
```bash
$ sortmate [space separated options] [input file]
```

### Cleanup
```bash
$ make uninstall # opposite of make install
$ make clean # opposite of make
$ make distclean # erase anything that ./configure created
```

### Options provided
| OPTION | ARGUMENTS                          | DESCRIPTION                                      |
|--------|------------------------------------|--------------------------------------------------|
| -b     |                                    | Ignore leading blanks                           |
| -c     |                                    | Check for sorted input; do not sort             |
| -d     |                                    | Consider only blanks and alphanumeric characters |
| -f     |                                    | Fold lowercase to uppercase characters          |
| -h     |                                    | Display help                                    |
| -i     |                                    | Consider only printable characters (32 - 126)   |
| -k     | [STARTCOL][ORDERING OPTIONS...]    | Sort by column or field                         |
| -n     |                                    | Sort by numerical value                         |
| -o     | [FILE]                             | Write result to specified file (default: stdout) |
| -r     |                                    | Reverse the order                              |
| -S     | [INTEGER]                          | Change main memory buffer space                |
| -s     |                                    | Disable last resort comparison                 |
| -x     | [b=bubble\|s=selection\|q=quick]  | Select sorting algorithm                       |

References:
1. https://en.wikipedia.org/wiki/Sort_(Unix)
2. `man sort` (or) https://www.man7.org/linux/man-pages/man1/sort.1.html
3. https://en.wikipedia.org/wiki/External_sorting

## Diving a bit deep
0. OPTIONS.md: More depth about how the options work.
1. COMPARE.md: The thought behind the actual sorting.
2. DESIGN.md: Design need and working of external sort + time complexity.
3. PORTABILITY.md: What's this `configure.ac` all about?
4. FUTURE.md: Documented some ideas and future tasks that would be interesting
to implement, and explained why haven't been done so far - fn pointers and
parallelization.


