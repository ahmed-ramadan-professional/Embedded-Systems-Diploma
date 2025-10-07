#include <stdio.h>

int power(int a, int b) {
    int result = 1;
    for (int i = 1; i <= b; i++) {
        result *= a;
    }
    return result;
}

int main(int argc, char const *argv[]) {
    while (1) {
        int a = 0, b = 0;

        printf("Enter a number followed by a space then the power you want to raise that number to : ");
        scanf("%d%d", &a, &b);

        printf("Result = %d\n", power(a, b));
    }
    return 0;
}