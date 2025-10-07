#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "BIT_MATH.h"

#define STR_EXPLODE_BUFFER_SIZE 50

uint16_t char_count(char *str, char c) {
    uint16_t count = 0;
    while (*str != '\0') {
        if (*str++ == c)
            count++;
    }
    return count;
}

void str_clean(char *str, char c) {
    uint8_t f = 0;
    char *ptr = str;
    while (*ptr != '\0') {
        while (*ptr != '\0' && *ptr == c) {
            if (*(ptr + 1) != '\0' && *(ptr + 1) != c && f)
                break;
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
    char **output =
             (char **)malloc((char_count(str, separator) + 2) * sizeof(char *)),
         **ptr = output;

    while (*str != '\0') {
        while (*str != separator && *str != '\0') {
            if (count < STR_EXPLODE_BUFFER_SIZE)
                buffer[count++] = *str;
            str++;
        }
        buffer[count] = '\0';

        *ptr = (char *)malloc(++count * sizeof(char));
        str_cpy(buffer, *ptr++, count);

        if (*str != '\0')
            str++;
        count = 0;
    }
    *ptr = NULL;

    return output;
}

uint8_t is_number(char *str) {
    while (*str != '\0') {
        if ((*str < '0' || *str > '9') && *str != '-')
            return 0;
        str++;
    }
    return 1;
}

uint8_t is_positive_number(char *str) {
    while (*str != '\0') {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

int multiplierValueRecursiveLookUp(char *str) {
    if (*(str + 1) == '\0' || *(str + 1) == ' ')
        return 1;
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

    if (negative_flag)
        output *= -1;

    return output;
}

void flush_stdin() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

uint8_t input_validator(char **inputs) {
    char *allowed_chars = "SsCcTtGg";
    char **ptr = inputs;
    int inputs_count = 0;

    inputs_count = 0;
    while (*ptr != NULL) {
        inputs_count++;
        ptr++;
    }

    if (inputs_count != 3) return 0;
    if (!is_number(inputs[0]) || !is_positive_number(inputs[2])) return 0;
    if (eval_int(inputs[2]) > 31) return 0;

    char *str = inputs[1];
    uint8_t counter = 0, equal_flag = 0;
    while (*str != '\0') {
        while (*allowed_chars != '\0') {
            if (*str == *allowed_chars++) equal_flag = 1;
        }
        if (!equal_flag) return 0;
        str++;
        counter++;
    }
    if (counter != 1) return 0;

    return 1;
}

void print_32binary(uint32_t value) {
    for (int i = 0; i < 32; i++) {
        printf("%d ", GET_BIT(value, 31 - i));
    }
}

void print_32binary_highlight(uint32_t value, uint8_t marker, uint8_t offset) {
    for (int i = 0; i < 32; i++) {
        printf("%d ", GET_BIT(value, 31 - i));
    }
    printf("\n");
    for (int i = 0; i < (31 - marker - 1) * 2 + offset; i++) {
        printf(" ");
    }
    printf("^");
}

void bit_manipulator(uint32_t *value, char op, uint16_t bit) {
    switch (op) {
        case 's':
        case 'S':
            SET_BIT(*value, bit);
            return;
        case 'c':
        case 'C':
            CLEAR_BIT(*value, bit);
            return;
        case 't':
        case 'T':
            TOGGLE_BIT(*value, bit);
            return;
    }
}

char *get_operation_name(char op) {
    char *operation_string[] = {"Set Bit", "Clear Bit", "Toggle Bit", "Get Bit"};
    switch (op) {
        case 's':
        case 'S':
            return operation_string[0];
        case 'c':
        case 'C':
            return operation_string[1];
        case 't':
        case 'T':
            return operation_string[2];
        case 'g':
        case 'G':
            return operation_string[3];
    }
}

void printer(uint32_t value, char op, uint16_t bit) {
    printf("\n===[ Value Given : %d <> Operation Selected : \"%s\" <> Bit Number Given : %d ]===\n",
           value, get_operation_name(op), bit);

    if (op == 'g' || op == 'G') {
        printf("\nDecimal Representation : %d", value);
        printf("\nBinary  Representation : ");
        print_32binary_highlight(value, bit, 27);
        printf("\nRetrieved Bit          : %d\n", GET_BIT(value, bit));
        return;
    }

    printf("\nBefore Operation :-");
    printf("\n\n  Decimal Representation : %d",value);
    printf("\n  Binary  Representation : ");
    print_32binary_highlight(value, bit, 29);
    
    bit_manipulator(&value, op, bit);
    
    printf("\n\nAfter Operation :-");
    printf("\n\n  Decimal Representation : %d",value);
    printf("\n  Binary  Representation : ");
    print_32binary_highlight(value, bit, 29);
}

int main(int argc, char const *argv[]) {
    char input_str[101], **inputs = NULL;

    while (1) {
        printf("This program allows you to manipulate bits in any decimal value you enter\n");
        printf("Simply Enter the decimal value followed by operation first letter and the bit number\n");
        printf("Each separated by a space and inorder i.e (15 g 2)\n");
        printf("Allowed operations : (s -> set, c -> clear,t -> toggle, g -> get)\n");
        printf("(notes : max value : 32 bit integer and bit value range : [0-31])\n");
        printf("type (e) to exit \n");
        printf("> ");

        scanf(" %100[^\n]", input_str);
        if (input_str[0] == 'e' || input_str[0] == 'E') break;
        flush_stdin();

        inputs = str_explode(input_str, ' ');
        if (!input_validator(inputs)) {
            printf("\nInvalid Input!\n\n");
            continue;
        }

        uint32_t value = eval_int(inputs[0]);
        uint16_t bit = eval_int(inputs[2]);
        char op = *inputs[1];

        printer(value, op, bit);
        printf("\n");

        char c;
        printf("type (e) to exit or hit enter to start over > ");
        scanf("%c", &c);
        if (c == 'e' || c == 'E')
            break;
        if (c != '\n')
            flush_stdin();
        system("cls");
    }

    return 0;
}
