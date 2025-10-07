#include <stdio.h>

unsigned int getGeometricSeriesNthTerm(unsigned int n) {
    if (n == 1) return 1;
    return 3 * getGeometricSeriesNthTerm(n - 1);
}

int main(int argc, char const *argv[]) {
    int n = 0;

    while (1) {

        printf("For the geometric series 1,3,9,27, ... \n");
        printf("Enter the value of (n) to calculate the (nth) term or (0) to exit > ");

        scanf("%d", &n);

        if (!n) break;

        n < 0 ? printf("Invalid value!\n\n") : printf("The %dth term of geometric series is : %d\n\n", n, getGeometricSeriesNthTerm(n));
    }
    return 0;
}
