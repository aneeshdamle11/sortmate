CC = gcc
CFLAGS = -g
sortmate:
	$(CC) $(CFLAGS) -o sortmate src/main.c src/io.c src/sort.c -Iinclude

tests:
	$(CC) $(CFLAGS) -o test_comparelines test/test_compare_lines.c src/sort.c -Iinclude

clean:
	rm -rf sortmate test_compare_lines temp
