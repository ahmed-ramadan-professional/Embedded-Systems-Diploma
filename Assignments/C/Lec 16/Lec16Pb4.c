#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_EXPLODE_BUFFER_SIZE 50

typedef struct {
    char name[20];
    int id;
    int grade;

} Student;

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

    if (negative_flag) output *= -1;

    return output;
}

uint8_t student_init(char *input_str, Student *student) {
    char **inputs = str_explode(input_str, ' '), **ptr = inputs;
    int inputs_count = 0;

    while (*ptr != NULL) {
        inputs_count++;
        ptr++;
    }

    if (inputs_count != 3) return 0;

    if (!is_positive_number(inputs[1]) || !is_positive_number(inputs[2])) return 0;

    str_cpy(inputs[0], student->name, 20);
    student->id = eval_int(inputs[1]);
    student->grade = eval_int(inputs[2]);
}

void flush_stdin() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

Student **students_scanner(uint8_t size) {
    Student **students = (Student **)malloc((size + 1) * sizeof(Student *)), **ptr = students;
    char input_str[101];
    uint8_t counter = 1;

    while (counter <= size ) {
        printf("Enter Student [%02d] Information > ",counter);

        scanf(" %100[^\n]", input_str);
        if (input_str[0] == 'e' || input_str[0] == 'E') return NULL;
        flush_stdin();

        *ptr = (Student *)malloc(sizeof(Student));

        if (!student_init(input_str, *ptr)) {
            printf("========Invalid Input!========\n");
            continue;
        }

        counter++;
        ptr++;
    }
    *ptr = NULL;
    return students;
}

void students_printer(Student **students) {
    Student **ptr = students;
    uint8_t counter = 1;

    if (students == NULL) return;

    while (*ptr != NULL) {
        printf("\nStudent [%d] Information :- \n\n", counter++);
        printf("  Student Name  : %s\n", (*ptr)->name);
        printf("  Student Roll  : %d\n", (*ptr)->id);
        printf("  Student Marks : %d\n\n", (*ptr)->grade);
        ptr++;
    }
}
// after all these pointers i've been dealing with it's safe to say regarding pointers i'm unstoppable
// pointers and double pointers have been my favorite since collage
// but they still hurt my brain when i use them for a long period of time tho :)
int main(int argc, char const *argv[]) {

    Student **students = NULL;

    while (1) {
        printf("This program will store 10 students information you enter\n");
        printf("Enter student name, id and grade each in order and separated by a space \n");
        printf("You have [100] character input buffer for each (use it wisely) \n");
        printf("type (e) to exit \n");
        printf("\n");

        students = students_scanner(10);
        students_printer(students);

        char c;
        printf("type (e) to exit or hit enter to start over > ");
        scanf("%c", &c);
        if (c == 'e' || c == 'E') break;
        if (c != '\n') flush_stdin();
        system("cls");
    }

    return 0;
}
