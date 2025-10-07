#include <stdio.h>

void flush_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

int countHoles(char *num_string) {
    int count = 0;
    while (*num_string != '\0') {
        switch (*num_string - '0') {
            case 0:
            case 4:
            case 6:
            case 9:
                count++;
                break;
            case 8:
                count += 2;
                break;
            default:
                break;
        }
        num_string++;
    }
    return count;
}

int main(int argc, char const *argv[]) {
    char num_string[11];

    while (1) {

        printf("Enter a number (max : 10 digits) to calculate the number of holes : ");

        scanf(" %10s", num_string);
        flush_input_buffer();

        printf("Number of Holes : %d\n", countHoles(num_string));
    }
    return 0;
}
