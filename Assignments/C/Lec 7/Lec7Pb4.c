#include <stdio.h>

unsigned int getFibonacciSeriesNthTermUsingLoops(unsigned int n) {
    unsigned int first_term = 1, second_term = 1, nth_term = 1;
    for (int i = 3; i <= n; i++) {
        nth_term = first_term + second_term;
        first_term = second_term;
        second_term = nth_term;
    }
    return nth_term;
}

unsigned int getFibonacciSeriesNthTermRecursively(unsigned int n) {
    if (n == 1 || n == 2) return 1;
    return getFibonacciSeriesNthTermRecursively(n - 1) + getFibonacciSeriesNthTermRecursively(n - 2);
}

int main(int argc, char const *argv[]) {
    int n = 0;

    while (1) {

        printf("For the fibonacci series 1,1,2,3,5,8,13, ... \n");
        printf("Enter the value of (n) to calculate the (nth) term or (0) to exit > ");

        scanf("%d", &n);

        if (!n) break;

        if (n < 0) {
            printf("Invalid value!\n\n");
            continue;
        }

        printf("The %dth term of fibonacci series (using recursion) is : %d\n", n, getFibonacciSeriesNthTermRecursively(n));
        printf("The %dth term of fibonacci series (using loops) is : %d\n\n", n, getFibonacciSeriesNthTermUsingLoops(n));
    }
    return 0;
}
