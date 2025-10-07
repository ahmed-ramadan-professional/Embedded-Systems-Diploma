#include <stdio.h>

void int32ToBinaryString(unsigned int a, char *binary_string) {
    for (int i = 0; i < sizeof(int) * 8; i++) {
        binary_string[31 - i] = ((a & (1 << i)) >> i) + '0';
    }
    binary_string[32] = '\0';
}

int countOnes(unsigned int a) {
    int count=0;

    for (int i = 0; i < sizeof(int) * 8; i++) {
        count += (a & (1 << i)) >> i;
    }
    return count;
}

int main(int argc, char const *argv[]) {
    unsigned int a = 0;
    char binary_string[33];

    while (1) {

        printf("Enter a positive int to calculate the number of ones in its binary form : ");

        scanf("%d", &a);

        int32ToBinaryString(a, binary_string);

        printf("The number of ones in its binary %s form is : %d\n\n", binary_string, countOnes(a));
    }
    return 0;
}
