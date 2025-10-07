#include <stdio.h>
#include <stdlib.h>

// assignment solution
// ==========================================================

void arrayReverse(int arr[], int size) {
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

// extra functions to make it harder for myself for no reason
// ==========================================================

int countPossibleArrayElementsFromInputString(char *input) {
    int count = 0;
    while (*input != '\0') {
        if (*input == ' ' && (*(input + 1) != ' ' && *(input + 1) != '\0')) count++;
        input++;
    }
    return count + 1;
}

// to determine the appropriate multiplier value for decimal conversion
int multiplierValueRecursiveLookUp(char *str) {
    if (*(str + 1) == '\0' || *(str + 1) == ' ') return 1;
    return 10 * multiplierValueRecursiveLookUp(str + 1);
}

int populateArrayOfIntElementsFromStringInput(char *input, int *arr, int size) {
    int index = 0;
    while (*input != '\0' && index < size) {
        arr[index] = 0;
        while (*input != ' ' && *input != '\0') {
            if (!(*input >= '0' && *input <= '9')) return -1;
            arr[index] += multiplierValueRecursiveLookUp(input) * (*input - '0');
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

int numberOfDigits(int num) {
    if (num / 10 == 0) return 1;
    return 1 + numberOfDigits(num / 10);
}

void arrayPrint(int arr[], int size) {
    printf("Array Given : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main(int argc, char const *argv[]) {
    char input[101];
    int *arr, size;

    while (1) {

        printf("This program will try to reverse the values of an array you will provide.\n");
        printf("First enter array elements on the same line, each separated by a space \n");
        printf("You have [100] character input buffer for each array (use it wisely) \n");
        printf("type (e) to exit \n");
        printf("> ");

        scanf(" %100[^\n]", input);

        if (input[0] == 'e' || input[0] == 'E') break;
        size = countPossibleArrayElementsFromInputString(input);
        arr = (int *)malloc(size * sizeof(int));
        flush_input_buffer();

        if (populateArrayOfIntElementsFromStringInput(input, arr, size) == -1) {
            printf("\nInvalid Input, Please enter values correctly\n\n");
            continue;
        }

        printf("\n");
        printf("Before Swap :- \n");
        arrayPrint(arr, size);
        printf("\n");

        arrayReverse(arr, size);

        printf("After Swap :- \n");
        arrayPrint(arr, size);
        printf("\n\n");
    }
    return 0;
}
