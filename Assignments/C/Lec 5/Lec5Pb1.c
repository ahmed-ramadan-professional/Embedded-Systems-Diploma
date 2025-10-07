#include <stdio.h>

int cube(int a) {
    return a * a * a;
}

int main(int argc, char const *argv[]) {
    int a = 0;

    while (1) {

        printf("Enter an integer to calculate its cube : ");

        scanf("%d", &a);

        printf("Result : %d\n", cube(a));
    }
    return 0;
}
