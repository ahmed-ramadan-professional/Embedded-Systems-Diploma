#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_EXPLODE_BUFFER_SIZE 50

typedef struct {
    char name[20];
    int roll;
    int marks;

} Student;

uint16_t char_count(char *str, char c) {
    uint16_t count = 0;
    while (*str != '\0') {
        if (*str++ == c) count++;
    }
    return count;
}

// Welcome to another series of "extra functions to make it harder for myself for no apparent reason" XD
void str_cpy(char *str_1, char *str_2, uint16_t size) {
    uint16_t count = 0;
    while (*str_1 != '\0' && count < size - 1) {
        *(str_2++) = *(str_1++);
        count++;
    }
    *str_2 = '\0';
}

// To clean the string of extra separators and leave only one
// just incase the user decided to brick my program for no reason
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
// my favorite function
char **str_explode(char *str, char separator) {
    uint8_t count = 0;
    char buffer[STR_EXPLODE_BUFFER_SIZE];

    str_clean(str, separator);
    // why +2 ? => (+1 for single element array) and another (+1 for null at the end to indicate end of array)
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

uint8_t is_positive_number(char *str) {
    while (*str != '\0') {
        if (*str < '0' || *str > '9') return 0;
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

    // forgot to evaluate negative numbers in previous assignments when parcing arrays from stdin my bad :(
    if (negative_flag) output *= -1;

    return output;
}

void flush_stdin() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(int argc, char const *argv[]) {
    char input_str[101], **inputs = NULL, **ptr = NULL;
    int inputs_count = 0;
    Student student;

    while (1) {
        printf("This program will store student information you enter\n");
        printf("Enter student name, roll and marks each in order and separated by a space \n");
        printf("You have [100] character input buffer (use it wisely) \n");
        printf("type (e) to exit \n");
        printf("> ");

        scanf(" %100[^\n]", input_str);
        if (input_str[0] == 'e' || input_str[0] == 'E') break;
        flush_stdin();

        inputs = str_explode(input_str, ' ');

        ptr = inputs;
        inputs_count = 0;
        while (*ptr != NULL) {
            inputs_count++;
            ptr++;
        }

        if (inputs_count != 3) {
            printf("\nInvalid Input!\n\n");
            continue;
        }

        if (!is_positive_number(inputs[1]) || !is_positive_number(inputs[2])) {
            printf("\nInvalid Input!\n\n");
            continue;
        }

        str_cpy(inputs[0], student.name, 20);
        student.roll = eval_int(inputs[1]);
        student.marks = eval_int(inputs[2]);

        printf("\nStudent Information :- \n\n");
        printf("  Student Name  : %s\n", student.name);
        printf("  Student Roll  : %d\n", student.roll);
        printf("  Student Marks : %d\n\n", student.marks);

        char c;
        printf("type (e) to exit or hit enter to start over > ");
        scanf("%c", &c);
        if (c == 'e' || c == 'E') break;
        if (c != '\n') flush_stdin();
        system("cls");
    }

    return 0;
}
