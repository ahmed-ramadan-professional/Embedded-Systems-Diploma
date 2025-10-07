#include <stdio.h>

int main(int argc, char const *argv[]) {
    for (int i = 0; i < 9; i += 2) {
        for (int j = 0; j < (9 - i) / 2; j++) {
            printf(" ");
        }
        for (int j = 0; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
