# sortmate
Designed to be a shell command to sort unlimited number of endless lines, as a 
part of semester 3 DSA courseware.

# Installation
```
$ autoreconf --install
$ # installs Makefile.in, src/Makefile.in config.h.in and configure scripts
$ # from configure.ac, Makefile.am, src/Makefile.am
$ ./configure
$ make # build the program code, executable src/sortmate
```

If you are a bit adventurous:
```
$ make check # run the portability test suite
$ make install # enables running the executable like a shell command `sortmate`
$ make installcheck # check the installed programs
$ make dist # builds the package
```

# Run

> $ sortmate # if installed in /usr/local/bin
> $ src/sortmate # if built with make, irrespective of make install

# Cleanup

```
$ make uninstall # opposite of make install
$ make clean # opposite of make
$ make distclean # erase anything ./configure created too
```
