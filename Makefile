sortmate:
	gcc -o sortmate src/main.c src/io.c src/sort.c -Iinclude

tests:
	gcc -o test_compare_lines test/test_compare_lines.c src/sort.c -Iinclude

clean:
	rm -f sortmate test_compare_lines
