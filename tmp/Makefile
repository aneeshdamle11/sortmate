make: main.o external_sort.o sort.o min_heap.o
	cc main.o external_sort.o sort.o min_heap.o -g -Wall -Werror -lm
main.o: main.c external_sort.h
	cc -c main.c
external_sort.o: external_sort.c external_sort.h sort.o min_heap.o
	cc -c external_sort.c
sort.o: sort.c sort.h
	cc -c sort.c
min_heap.o: min-heap/min_heap.c min-heap/min_heap.h
	cc -c min-heap/min_heap.c
clean:
	rm *.o
	rm *.out
	rm *.txt
	cp ../dat/numbers.txt .
