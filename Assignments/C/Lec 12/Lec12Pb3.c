#include <stdio.h>
#include <stdlib.h>

// modified function previously submitted in Lec8Pb4 assignment
void arrayReverse(int *arr, int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = *(arr + i);
        *(arr + i) = *(arr + size - i - 1);
        *(arr + size - i - 1) = temp;
    }
}

// didn't expect these functions to become part of the assignment one day (˵ ͡° ͜ʖ ͡°˵)
// this part was adjusted to follow assignment instructions
// to determine the appropriate multiplier value for decimal conversion
int multiplierValueRecursiveLookUp(char *str) {
    if (*(str + 1) == '\0' || *(str + 1) == ' ') return 1;
    return 10 * multiplierValueRecursiveLookUp(str + 1);
}

int populateArrayOfIntElementsFromStringInput(char *input, int *arr, int size) {
    int index = 0;
    while (*input != '\0' && index < size) {
        *(arr + index) = 0;
        while (*input != ' ' && *input != '\0') {
            if (!(*input >= '0' && *input <= '9')) return -1;
            *(arr + index) += multiplierValueRecursiveLookUp(input) * (*input - '0');
            input++;
        }
        if (*(input - 1) != ' ') index++;
        input++;
    }
    return 1;
}

void flush_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

char isExitSequencePressentAtStart(char *str) {
    char exit[5] = "exit";
    for (int i = 0; i < 4; i++) {
        if (str[i] == '\0' || str[i] != exit[i]) return 0;
    }
    return 1;
}

void arrayPrint(int arr[], int size) {
    printf("Result : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main(int argc, char const *argv[]) {
    char input[101];
    int *arr, size = 10;

    while (1) {

        printf("This program will try to read 10 array values from your input\n");
        printf("and echoing them back to you in reverse\n");
        printf("Enter 10 array elements on the same line, each separated by a space \n");
        printf("(note : additional values will be ignored) \n");
        printf("type (e) to exit \n");
        printf("> ");

        scanf(" %100[^\n]", input);
        if (input[0] == 'e' || input[0] == 'E') break;
        arr = (int *)malloc(size * sizeof(int));
        flush_input_buffer();

        if (size < 10 || populateArrayOfIntElementsFromStringInput(input, arr, size) == -1) {
            printf("\nInvalid Input, Please enter values correctly\n\n");
            continue;
        }

        printf("\n");
        arrayReverse(arr, size);
        arrayPrint(arr, size);
        printf("\n");
    }
    return 0;
}
