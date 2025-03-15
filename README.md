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

### Documentation
0. [OPTIONS.md](docs/OPTIONS.md): More depth about how the options work.
1. [COMPARE.md](docs/COMPARE.md): The thought behind the actual sorting.
2. [DESIGN.md](docs/DESIGN.md): Design need and working of external sort + time complexity.
3. [PORTABILITY.md](docs/PORTABILITY.md): What's this `configure.ac` all about?
4. [FUTURE.md](docs/FUTURE.md): Documented some ideas and future tasks that would be interesting to implement, and explained why they haven't been done so far - function pointers and parallelization.

### References
0. `info sort` - **Highly useful**
1. [Sort (Unix) - Wikipedia](https://en.wikipedia.org/wiki/Sort_(Unix))
2. [`man sort`](https://www.man7.org/linux/man-pages/man1/sort.1.html)
3. [External Sorting - Wikipedia](https://en.wikipedia.org/wiki/External_sorting)
4. [IBM sort command](https://www.ibm.com/docs/en/aix/7.3?topic=s-sort-command) - Explains fields and keys well

