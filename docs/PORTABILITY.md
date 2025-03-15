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


