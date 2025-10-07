#include <stdio.h>

int isPerfectSquare(int a) {
    for (int i = 1; i <= a; i++) {
        if (a % i == 0) {
            if (i * i == a) {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    int a = 0;

    while (1) {

        printf("Enter an integer to check if it's a perfect square or not : ");

        scanf("%d", &a);

        printf("This Number is%s a Perfect Square\n", isPerfectSquare(a) ? "" : " not");
    }
    return 0;
}
