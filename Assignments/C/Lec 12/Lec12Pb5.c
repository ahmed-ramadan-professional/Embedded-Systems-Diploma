#include <stdio.h>
#include <stdlib.h>

// assignment solution
void arrayCopy(int *arr_1, int *arr_2, int size) {
    for (int i = 0; i < size; i++) {
        *(arr_2 + i) = *(arr_1 + i);
    }
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
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main(int argc, char const *argv[]) {
    char input[101];
    int *arr_1, *arr_2, size;

    while (1) {

        printf("This program will try to copy the values of an array you provide into another\n");
        printf("Enter array elements on the same line, each separated by a space \n");
        printf("You have [100] character input buffer (use it wisely) \n");
        printf("type (e) to exit \n");
        printf("> ");

        scanf(" %100[^\n]", input);
        if (input[0] == 'e' || input[0] == 'E') break;
        size = countPossibleArrayElementsFromInputString(input);
        arr_1 = (int *)malloc(size * sizeof(int));
        flush_input_buffer();

        if (populateArrayOfIntElementsFromStringInput(input, arr_1, size) == -1) {
            printf("\nInvalid Input, Please enter values correctly\n\n");
            continue;
        }

        arr_2 = (int *)malloc(size * sizeof(int));
        arrayCopy(arr_1,arr_2,size);

        printf("\nArray Given  : ");
        arrayPrint(arr_1, size);
        printf("Array Copied : ");
        arrayPrint(arr_2, size);
        printf("\n");
    }
    return 0;
}
