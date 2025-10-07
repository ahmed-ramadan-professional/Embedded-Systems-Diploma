#include <stdio.h>

// resused from previous assignment Lec4Pb1
int isPrime(int a) {
    if (a <= 1)
        return 0;

    for (int i = a - 1; i > 1; i--) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}

void printPrimesBetweenTwoIntervals(int s, int e) {
    printf("Here is the prime numbers present between [%d,%d] : ", s, e);
    for (int i = s; i <= e; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int s = 0, e = 0;

    while (1) {
        printf("Enter an interval to display the prime numbers present between\n");
        printf("By entering the starting number followed by a space then the ending number : ");

        scanf("%d%d", &s, &e);

        printPrimesBetweenTwoIntervals(s, e);
    }
    return 0;
}
