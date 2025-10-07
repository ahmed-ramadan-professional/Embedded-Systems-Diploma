#include <stdio.h>

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

int main(int argc, char const *argv[]) {
    int a = 0;

    while (1) {

        printf("Enter an integer to check if it's a prime number or not : ");

        scanf("%d", &a);

        printf("This Number is%s a Prime Number\n", isPrime(a) ? "" : " not");
    }
    return 0;
}
