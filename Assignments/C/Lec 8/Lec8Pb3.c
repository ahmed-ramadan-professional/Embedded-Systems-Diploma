#include <stdio.h>
#include <stdlib.h>

// assignment solution
// ==========================================================

void swapTwoArrays(int arr_1[], int arr_2[], int size) {
    int temp;
    for (int i = 0; i < size; i++) {
        temp = arr_1[i];
        arr_1[i] = arr_2[i];
        arr_2[i] = temp;
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

void doubleArrayPrint(int arr_1[], int arr_2[], int size) {
    printf("First Array Given : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr_1[i]);
    }

    printf("\n");

    printf("Second Array Given : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr_2[i]);
    }

    printf("\n");
}

int main(int argc, char const *argv[]) {
    char input[101];
    int *arr_1, *arr_2, size_1, size_2;

    while (1) {

        printf("This program will try to swap the values of two arrays (of the same length) you will provide.\n");
        printf("You have [100] character input buffer for each array (use it wisely) \n");
        printf("type (e) to exit \n\n");

        printf("Enter the first array elements on the same line, each separated by a space \n");
        printf("> ");

        scanf(" %100[^\n]", input);

        if (input[0] == 'e' || input[0] == 'E') break;
        size_1 = countPossibleArrayElementsFromInputString(input);
        arr_1 = (int *)malloc(size_1 * sizeof(int));
        flush_input_buffer();

        if (populateArrayOfIntElementsFromStringInput(input, arr_1, size_1) == -1) {
            printf("Invalid Input, Please enter values correctly\n\n");
            continue;
        }

        printf("Enter the second array elements on the same line, each separated by a space \n");
        printf("> ");

        scanf(" %100[^\n]", input);

        if (input[0] == 'e' || input[0] == 'E') break;
        size_2 = countPossibleArrayElementsFromInputString(input);
        arr_2 = (int *)malloc(size_2 * sizeof(int));
        flush_input_buffer();

        if (populateArrayOfIntElementsFromStringInput(input, arr_2, size_2) == -1) {
            printf("\nInvalid Input, Please enter values correctly\n\n");
            continue;
        }

        if (size_1 != size_2) { 
            printf("\nInvalid Input, Two arrays are of different sizes\n\n");
            continue;
        }

        printf("\n");
        printf("Before Swap :- \n");
        doubleArrayPrint(arr_1, arr_2, size_1);
        printf("\n");

        swapTwoArrays(arr_1,arr_2,size_1);

        printf("After Swap :- \n");
        doubleArrayPrint(arr_1, arr_2, size_1);
        printf("\n\n");
    }
    return 0;
}
