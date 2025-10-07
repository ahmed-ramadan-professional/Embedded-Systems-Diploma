#include <stdio.h>

// Ahmed Ramadan ;)
// maybe it's easier implementing it using strings but why not make it harder for the sack of a challenge ¯\(°_o)/¯
// also recursion would have saved us a headache but u probably wanted loops for this lecture exercise (︶︹︶)
void reverse(int a) {

    for (int i = 10; a * 10 / i != 0; i *= 10) {

        printf("%d", (a % i) / (i / 10));
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int a = 0;

    while (1) {

        printf("Enter an integer with any number of digits ;) to be displayed in reverse : ");

        scanf("%d", &a);

        printf("Reversed Result : ");
        reverse(a);
    }
    return 0;
}
