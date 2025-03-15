## Basic options

NOTE: The examples below are taken from `data/` folder.
```
$ cat phonebook
Smith, Brett     5554321
Doe, John        5551234
Doe, Jane        5553214
Avery, Cory      5554132
Fogarty, Suzie   555231
```
1. basic sort
```
$ sortmate phonebook
Avery, Cory      5554132
Doe, Jane        5553214
Doe, John        5551234
Fogarty, Suzie   555231
Smith, Brett     5554321
```
2. -r: reverse the order of the sort
```
$ sortmate -r phonebook
Smith, Brett     5554321
Fogarty, Suzie   555231
Doe, John        5551234
Doe, Jane        5553214
Avery, Cory      5554132
```
3. -n: sort numerically
```
$ cat numeric
1234lMn
1234Lmf
789abc
034xyz

$ sortmate -n numeric
034xyz
789abc
1234Lmf
1234lMn
```
5. -c: check for sorted input; do not sort
```
$ sortmate -c phonebook
sortmate: disorder: Doe, John        5551234
```
4. -k [FIELD][OPTS]: sort by field
>  FIELD: column number, OPTS: string of ordering options
```
$ sortmate -k 2 phonebook
Smith, Brett     5554321
Avery, Cory      5554132
Doe, Jane        5553214
Doe, John        5551234
Fogarty, Suzie   555231

$ sortmate -k3 phonebook
Doe, John        5551234
Fogarty, Suzie   555231
Doe, Jane        5553214
Avery, Cory      5554132
Smith, Brett     5554321

$ # field sort also supports multiple options within the key
$ sortmate -k 3n phonebook
Fogarty, Suzie   555231
Doe, John        5551234
Doe, Jane        5553214
Avery, Cory      5554132
Smith, Brett     5554321
```

## How `sortmate` deals with options
`sortmate` internally doesn't compare lines, but "fields".

### Field
A field is a line or a subset of a line, defined according to a key.
> A key is an option of the format: -k[FIELD] with optional ordering options.

```
How are key options differentiated?
$ sortmate -n -f -k2fb -k3r -k1 phonebook
> First key: "-k2fb". Here, the field = 2 and ordering options are "f and b".
> Second key: "-k3r". Here, the field is 3 and ordering option is "r".
NOTE: When ordering options are not specified on a key, it inherits the global
options.
> Third key: "-k1". Here, the field is 1 and ordering options are "n and f".
```

### Comparing fields with keys
In `sortmate` a pair of fields is compared as follows:
```
- A field is subset from a line, and compared with ordering options available
  against the key specified.
- If the first key comparison marks a difference, the result is returned.
- Else, the second key is compared. And so on and so forth, till all the keys
  are tried out.
- If no key fields are specified, or all key fields compare equal, then a "last
  resort" comparison is made, where the whole line is compared without
  considering any keys or any options.
```

### The "-s" option
This option prevents the last resort comparison, and the line order is kept as
is.
```
$ cat keystable
xyZb lmn
def ghi
pqr abc
Xyza lmn
XYZc lmn

$ sortmate -k2 keystable
pqr abc
def ghi
XYZc lmn
Xyza lmn
xyZb lmn

$ # shows -f doesn't affect the last resort comparison ordering
$ LC_ALL=C sort -k2 -f keystable
pqr abc
def ghi
XYZc lmn
Xyza lmn
xyZb lmn

$ sortmate -k2 -s keystable # prevents "last-resort" comparison
pqr abc
def ghi
xyZb lmn
Xyza lmn
XYZc lmn
```

### References:
1. `info sort` - a very good explanation of how the UNIX sort works with options
