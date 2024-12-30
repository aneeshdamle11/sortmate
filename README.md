# sortmate
> v2.0: A system to sort unlimited number of endless lines.

## Installation and usage
```bash
$ make
$ ./sortmate [OPTIONS] filename
$ # cleanup after use
$ make clean
```

## Options
> ./sortmate -h

- : basic sort
- -h: display help
- -r: reverse the order
- -n: sort by numerical value
- -k: sort by column or field
- -c: check for sorted input; do not sort

## Documentation

The `docs` folder includes a detailed documentation on the features:
how 2 lines are compared
- sorting algorithm's function pointers
- flags and some useful examples
- how does the system log
- implementation of external sorting
- explanation on parallelization

