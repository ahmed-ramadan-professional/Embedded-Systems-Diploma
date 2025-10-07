#include <stdio.h>

unsigned int getArithmeticSeriesNthTerm(unsigned int n) {
    return 1 + (n - 1) * 2;
}

int main(int argc, char const *argv[]) {
    int a = 0;

    while (1) {

        printf("For the arithmetic series 1,3,5,7,9 ... \n");
        printf("Enter the value of (n) to calculate the (nth) term or (0) to exit > ");

        scanf("%d", &a);

        if (!a) break;

        a < 0 ? printf("Invalid value!\n\n") : printf("The %dth term of arithmetic series is : %d\n\n", a, getArithmeticSeriesNthTerm(a));
    }
    return 0;
}
