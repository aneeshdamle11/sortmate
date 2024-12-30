sortmate:
	gcc -o sortmate src/main.c src/sort.c -Iinclude

tests:
	gcc -o test_compare_lines tests/test_compare_lines.c src/sort.c -Iinclude

clean:
	rm -f sortmate test_compare_lines
