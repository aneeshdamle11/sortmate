make: main.o fileread.o filesort.o
	cc main.o fileread.o filesort.o -g -Wall -Werror -lm -o txt
main.o: main.c files.h
	cc -c main.c
filesort.o: filesort.c files.h
	cc -c filesort.c
fileread.o: fileread.c files.h
	cc -c fileread.c
clean:
	rm *.o
	rm txt
