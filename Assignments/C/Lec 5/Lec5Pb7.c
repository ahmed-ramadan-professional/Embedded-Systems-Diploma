#include <stdio.h>

void int32ToBinaryString(unsigned int a, char *binary_string) {
    for (int i = 0; i < sizeof(int) * 8; i++) {
        binary_string[31-i] = ((a & (1 << i)) >> i) + '0';
    }
    binary_string[32]='\0';
}

int countConsecutiveZerosBetweenTwoOnes(unsigned int a) {
    int max = 0, count = 0, first_one_encountered_flag = 0;

    for (int i = 0; i < sizeof(int) * 8; i++) {
        if ((a & (1 << i)) >> i) {
            if (first_one_encountered_flag) {
                if (count > max) max = count;
            } else {
                first_one_encountered_flag = 1;
            }
            count = 0;
            continue;
        }
        count++;
    }
    return max;
}

int main(int argc, char const *argv[]) {
    unsigned int a = 0;
    char binary_string[33];

    while (1) {

        printf("Enter a positive int to calculate the number of consecutive zeros between two ones in its binary form : ");

        scanf("%d", &a);

        int32ToBinaryString(a, binary_string);

        printf("The number of consecutive zeros between two ones in its binary form %s is : %d\n\n", binary_string, countConsecutiveZerosBetweenTwoOnes(a));
    }
    return 0;
}
