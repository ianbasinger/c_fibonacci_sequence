#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>


void fibonacci_iterative(mpz_t result, long n) {
    if (n == 0) {
        mpz_set_ui(result, 0); // F(0) = 0
        printf("F(0) = 0\n");
        return;
    }
    if (n == 1) {
        mpz_set_ui(result, 1); // F(1) = 1
        printf("F(1) = 1\n");
        return;
    }

    mpz_t a, b, temp;
    mpz_init_set_ui(a, 0); // F(0)
    mpz_init_set_ui(b, 1); // F(1)
    mpz_init(temp);

    printf("F(0) = 0\n");
    printf("F(1) = 1\n");

    for (long i = 2; i <= n; ++i) {
        mpz_add(temp, a, b); // temp = a + b
        mpz_set(a, b);       // a = b
        mpz_set(b, temp);    // b = temp

        // Print the current step
        gmp_printf("F(%ld) = %Zd\n", i, b);
    }

    mpz_set(result, b); // F(n)

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(temp);
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s NUM\n", argv[0]);
        return EXIT_FAILURE;
    }

    long count = strtol(argv[1], NULL, 10);
    if (count < 0) {
        fprintf(stderr, "Error: NUM must be non-negative.\n");
        return EXIT_FAILURE;
    }
    printf("Input received: %ld\n", count);

    mpz_t result;
    mpz_init(result);

    const clock_t start_time = clock();
    if (start_time == (clock_t)-1) {
        fprintf(stderr, "Error: start_time clock() failed.\n");
        return EXIT_FAILURE;
    }

    fibonacci_iterative(result, count);
    printf("Fibonacci computation completed.\n");

    const clock_t end_time = clock();
    if (end_time == (clock_t)-1) {
        fprintf(stderr, "Error: end_time clock() failed.\n");
        return EXIT_FAILURE;
    }

    gmp_printf("Computed Fibonacci: %Zd\n", result);

    const double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Calculation Time: %lf seconds\n", time_taken);

    mpz_clear(result);
    printf("Press Enter to exit...");
    getchar();

    return EXIT_SUCCESS;
}
