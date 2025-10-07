#include <stdio.h>

// there were no clear instructions given of what to return when encountering the number "1" as an input
// as the number "1" is the only number that is both a power of two and a power of three simultaneously
// the function at its current implementation will return "1" when the input is "1"
// as if the number "1" is only a power of two number and not a power of three
int isPowerOfTwoOrPowerOfThree(int a) {
    //if (a == 1) return 2; // suggested enhancement
    if ((a & (a - 1)) == 0) return 1;

    while (a % 3 == 0) {
        a /= 3;
    }

    return a == 1 ? 0 : -1;
}

int main(int argc, char const *argv[]) {
    int a = 0;

    while (1) {

        printf("Enter a number to check if it's a power of two or a power of three or neither : ");

        scanf("%d", &a);

        printf("The number given (%d) is ", a);

        switch (isPowerOfTwoOrPowerOfThree(a)) {
            case 1:
                printf("a power of two\n");
                break;

            case 0:
                printf("a power of three\n");
                break;

            case -1:
                printf("neither a power of two nor a power of three\n");
                break;

            // case 2: //suggested enhancement
            //     printf("both a power of two and a power of three\n");
            //     break;
        }

        printf("\n");
    }
    return 0;
}
