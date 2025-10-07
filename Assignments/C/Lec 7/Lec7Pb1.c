#include <stdio.h>
#include <stdlib.h>

// assignment solution
// ==========================================================

int arraySearch(int haystack[], int size, int needle) {
    for (int i = 0; i < size; i++) {
        if (haystack[i] == needle) return i;
    }
    return -1;
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

void arrayPrintWithHighlight(int arr[], int size, int marker) {
    int marker_index = marker;
    printf("Array Given : ");
    for (int i = 0; i < size; i++) {
        if (i < marker) marker_index += numberOfDigits(arr[i]);
        printf("%d ", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < marker_index + 14; i++) {
        printf(" ");
    }
    printf("^\n");

    printf("Value [%d] was found at index <%d> or position <%d>\n", arr[marker], marker, marker + 1);
}

int main(int argc, char const *argv[]) {
    char input[101];
    int *haystack, needle, size, result;

    while (1) {

        printf("This program will try to find the index of a value you entre in an array you will provide.\n");
        printf("First enter array elements on the same line, each separated by a space \n");
        printf("You have [100] character input buffer (use it wisely) \n");
        printf("type (e) to exit \n");
        printf("> ");

        scanf(" %100[^\n]", input);
        if (input[0] == 'e' || input[0] == 'E') break;
        size = countPossibleArrayElementsFromInputString(input);
        haystack = (int *)malloc(size * sizeof(int));
        flush_input_buffer();

        if (populateArrayOfIntElementsFromStringInput(input, haystack, size) == -1) {
            printf("\nInvalid Input, Please enter values correctly\n\n");
            continue;
        }

        printf("Now enter the value you want to search for in the array you have provided : ");
        scanf("%d", &needle);

        printf("\n");

        result = arraySearch(haystack, size, needle);

        result == -1 ? printf("The value you entered is not pressent in the array given!\n")
                     : arrayPrintWithHighlight(haystack, size, result);

        printf("\n");
    }
    return 0;
}
