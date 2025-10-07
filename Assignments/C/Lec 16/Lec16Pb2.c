#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_EXPLODE_BUFFER_SIZE 50

typedef struct {
    int a;
    int b;

} Complex;

uint16_t char_count(char *str, char c) {
    uint16_t count = 0;
    while (*str != '\0') {
        if (*str++ == c) count++;
    }
    return count;
}

void str_clean(char *str, char c) {
    uint8_t f = 0;
    char *ptr = str;
    while (*ptr != '\0') {
        while (*ptr != '\0' && *ptr == c) {
            if (*(ptr + 1) != '\0' && *(ptr + 1) != c && f) break;
            ptr++;
        }
        f = 1;
        *str++ = *ptr++;
    }
    *str = '\0';
}

void str_cpy(char *str_1, char *str_2, uint16_t size) {
    uint16_t count = 0;
    while (*str_1 != '\0' && count < size - 1) {
        *(str_2++) = *(str_1++);
        count++;
    }
    *str_2 = '\0';
}

char **str_explode(char *str, char separator) {
    uint8_t count = 0;
    char buffer[STR_EXPLODE_BUFFER_SIZE];

    str_clean(str, separator);
    char **output = (char **)malloc((char_count(str, separator) + 2) * sizeof(char *)), **ptr = output;

    while (*str != '\0') {
        while (*str != separator && *str != '\0') {
            if (count < STR_EXPLODE_BUFFER_SIZE) buffer[count++] = *str;
            str++;
        }
        buffer[count] = '\0';

        *ptr = (char *)malloc(++count * sizeof(char));
        str_cpy(buffer, *ptr++, count);

        if (*str != '\0') str++;
        count = 0;
    }
    *ptr = NULL;

    return output;
}

uint8_t is_number(char *str) {
    while (*str != '\0') {
        if ((*str < '0' || *str > '9') && *str != '-') return 0;
        str++;
    }
    return 1;
}

int multiplierValueRecursiveLookUp(char *str) {
    if (*(str + 1) == '\0' || *(str + 1) == ' ') return 1;
    return 10 * multiplierValueRecursiveLookUp(str + 1);
}

int eval_int(char *str) {
    uint8_t negative_flag = 0;
    int output = 0;

    if (*str == '-') {
        negative_flag = 1;
        str++;
    }

    while (*str != '\0') {
        output += multiplierValueRecursiveLookUp(str) * (*str - '0');
        str++;
    }

    if (negative_flag) output *= -1;

    return output;
}

uint8_t complex_init(Complex *complex, char *input_str) {
    char **inputs = str_explode(input_str, ' '), **ptr = inputs;
    uint8_t inputs_count = 0;

    while (*ptr != NULL) {
        inputs_count++;
        ptr++;
    }

    if (inputs_count != 2) {
        return 0;
    }

    if (!is_number(inputs[0]) || !is_number(inputs[1])) {
        return 0;
    }

    complex->a = eval_int(inputs[0]);
    complex->b = eval_int(inputs[1]);

    return 1;
}

void complex_addition(Complex c_1, Complex c_2) {
    printf("\nFirst Complex Number Given  : %d%+di\n", c_1.a, c_1.b);
    printf("Second Complex Number Given : %d%+di\n\n", c_2.a, c_2.b);
    printf("Addition Result             : %d%+di\n\n", c_1.a + c_2.a, c_1.b + c_2.b);
}

int main(int argc, char const *argv[]) {
    char input_str[50], **inputs = NULL, **ptr = NULL;
    int inputs_count = 0;
    Complex c_1, c_2;

    while (1) {
        printf("This program will add two complex number provided by you and display the result\n");
        printf("Complex number represented using this form : a+bi \n");
        printf("For each complex number enter a and b on the same line separated by a space\n");
        printf("type (e) to exit \n\n");

        printf("First Complex Number  : ");

        scanf(" %50[^\n]", input_str);
        if (input_str[0] == 'e' || input_str[0] == 'E') break;

        if (!complex_init(&c_1, input_str)) {
            printf("\nInvalid Input!\n\n");
            continue;
        }
        printf("Second Complex Number : ");

        scanf(" %50[^\n]", input_str);
        if (input_str[0] == 'e' || input_str[0] == 'E') break;

        if (!complex_init(&c_2, input_str)) {
            printf("\nInvalid Input!\n\n");
            continue;
        }

        complex_addition(c_1, c_2);
    }

    return 0;
}
