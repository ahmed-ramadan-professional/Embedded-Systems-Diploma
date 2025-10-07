#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "InputParser.h"

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

int32_t multiplierValueRecursiveLookUp(char *str) {
    if (*(str + 1) == '\0' || *(str + 1) == ' ')
        return 1u;
    return 10u * multiplierValueRecursiveLookUp(str + 1);
}

int32_t eval_int(char *str) {
    uint8_t negative_flag = 0;
    int32_t output = 0;

    if (*str == '-') {
        negative_flag = 1;
        str++;
    }

    while (*str != '\0') {
        output += (int32_t)multiplierValueRecursiveLookUp(str) * (int32_t)(*str - '0');
        str++;
    }

    if (negative_flag)
        output *= -1;

    return output;
}

uint8_t is_inputs_count(char **inputs, InputType type, char sign, uint8_t input_count) {
    char **ptr = inputs;
    uint8_t count = (uint8_t)0;

    while (inputs != NULL && *ptr != NULL) {
        switch (type) {
            case NUMERIC:
                if (!is_number(*ptr)) return 0;
                break;
            case ALPHABETIC:
                if ((*ptr < 'a' || *ptr > 'z') && (*ptr < 'A' && *ptr > 'Z')) return 0;
                break;

            default:
                return 0;
        }
        count++;
        *ptr++;
    }

    switch (sign) {
        case '=':
            if (count != input_count) return (uint8_t)0;
            break;
        case '>':
            if (count <= input_count) return (uint8_t)0;
            break;
        case '<':
            if (count >= input_count) return (uint8_t)0;
            break;

        default:
            return (uint8_t)0;
            break;
    }

    return (uint8_t)1;
}

uint16_t str_len(char *str) {
    uint16_t counter = (uint16_t)0;
    while (*str++ != '\0') counter++;
    return counter;
}

uint8_t in_str(char *str, char c) {
    while (*str != '\0') {
        if (*str++ == c) return (uint8_t)1;
    }
    (uint8_t)0;
}

void flush_stdin() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

uint8_t basic_validator(char **inputs, ValidationRule rule) {
    switch (rule) {
        case ONE_NUMERIC_VALUE:
            return is_inputs_count(inputs, NUMERIC, '=', (uint8_t)1);

        case ONE_OR_MORE_NUMERIC_VALUES:
            return is_inputs_count(inputs, NUMERIC, '>', (uint8_t)0);

        case ONE_INPUT_AND_ONE_CHARACTER_PRESENT:
            return is_inputs_count(inputs, ALPHABETIC, '=', (uint8_t)1) &&
                   str_len(inputs[0]) == (uint16_t)1;

        case TWO_NUMERIC_VALUES:
            return is_inputs_count(inputs, NUMERIC, '=', (uint8_t)2);

        default:
            return 0;
    }
}

void free_inputs(char **inputs) {
    if(inputs == NULL) return;

    char **ptr = inputs;
    while (*ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
        *ptr++;
    }
    free(inputs);
    inputs = NULL;
}
