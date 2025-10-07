#include <stdio.h>

// we were instructed in this assignment to return a value or an error
// conventionally we return errors by using the value -1
// but since the function returns arithmetic operations results
// we can't return -1 as an error code
// as -1 could conflict with an actual and valid arithmetic operation result
// there are a couple of work arounds to this issue
// we could return an array of (error,result)
// or we could convert each result to a string and return it
// then the error code at that case might be empty string or null character '\0'
// but i choose struct as it's an elegant, organized very reusable, readable and self-documented solution
// and the result value could be built upon in other functions in the code if needed
// in case of an array it might be ambiguous at first for other developers to work with
// and in case of strings they are not reusable and other developers will have to convert them back to their values

struct Result {
    int error;
    float value;
};

struct Result calc(char o, float a, float b) {
    struct Result result;

    result.value = 0;
    result.error = 0;

    switch (o) {
        case '+':
            result.value = a + b;
            break;
        case '-':
            result.value = a - b;
            break;
        case '*':
            result.value = a * b;
            break;
        case '/':
            if (b == 0) {
                result.error = 1;
                break;
            }
            result.value = a / b;
            break;

        default:
            result.error = 1;
            break;
    }

    return result;
}

int main(int argc, char const *argv[]) {
    char o;
    float a, b;

    printf("- This program let's you perform any of these arithmetic operations\n");
    printf("- ( ' + ' , ' - ' , ' * ' , ' / ' ) between any two numbers of your choosing\n");
    printf("- Simply enter the operation, the first number and the second number in order\n");
    printf("- Each separated by a space ( for example : + 2 5 )\n");

    while (1) {
        printf("- Please, enter your desired operation and values as explained above : ");

        scanf(" %c%f%f", &o, &a, &b);

        struct Result result = calc(o, a, b);

        result.error ? printf("- This arithmetic Operation is not allowed or invalid!\n") : printf("- Result : %.2f\n", result.value);
    }
    return 0;
}
