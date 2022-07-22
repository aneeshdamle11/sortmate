#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Generates random numbers provided as command-line input */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out count\n");
        return 1;
    }

    FILE *fp = fopen("numbers.txt", "w");
    if (!fp) {
        printf("Could not create numbers.txt");
        return 2;
    }

    printf("Random numbers from 0-10000 will be generated in number.txt\nGenerating...");
    int n = atoi(argv[1]);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", rand() % 10000);
    }
    printf("Done.\n");

    fclose(fp);

    return 0;
}
