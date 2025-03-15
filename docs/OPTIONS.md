The options provided by sortmate are explained here.

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
$ sortmate -k3n phonebook
Fogarty, Suzie   555231
Doe, John        5551234
Doe, Jane        5553214
Avery, Cory      5554132
Smith, Brett     5554321
```

TODO: Keys, ordering options, corresponding examples


