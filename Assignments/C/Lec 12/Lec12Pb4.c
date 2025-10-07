#include <stdio.h>
#include <stdlib.h>

// assignment solution
int findSmallestValueInArrayUsingPointers(int *arr, int size) {
    int min = *arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) < min) min = *(arr + i);
    }
    return min;
}

// array parcing and printing functions
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

char isExitSequencePressentAtStart(char *str) {
    char exit[5] = "exit";
    for (int i = 0; i < 4; i++) {
        if (str[i] == '\0' || str[i] != exit[i]) return 0;
    }
    return 1;
}

void arrayPrint(int arr[], int size) {
    printf("Array Given    : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main(int argc, char const *argv[]) {
    char input[101];
    int *arr, size;

    while (1) {

        printf("This program will try to find the smallest value of an array\n");
        printf("Enter array elements on the same line, each separated by a space \n");
        printf("You have [100] character input buffer (use it wisely) \n");
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
        arrayPrint(arr, size);
        printf("Smallest Value : %d\n\n", findSmallestValueInArrayUsingPointers(arr, size));
    }
    return 0;
}
