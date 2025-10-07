#include <stdio.h>

int main(int argc, char const *argv[]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < i; j++) {
            printf(" ");
        }

        printf("*");

        for (int j = 10 - 2 * i; j > 0; j--) {
            printf(" ");
        }

        printf("*");

        printf("\n");
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 5 - i; j > 0; j--) {
            printf(" ");
        }

        printf("*");

        for (int j = 0; j < i * 2; j++) {
            printf(" ");
        }

        printf("*");

        printf("\n");
    }
    return 0;
}
