#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_EXPLODE_BUFFER_SIZE 50

typedef struct {
    enum {
        TIME_M_12H,
        TIME_M_24H,
    } Mode;

    enum {
        UNSET,
        AM,
        PM,
    } Midday;

    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;

    uint8_t mode;
    uint8_t midday;

    uint32_t total_seconds;
} Time;

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

uint8_t time_validator(char **time, char *mode) {
    char **ptr = time;
    uint8_t inputs_count = 0;
    uint8_t time_mode = TIME_M_24H;
    uint8_t midday = UNSET;

    while (*ptr != NULL) {
        char *temp = *ptr;
        while (*temp != '\0') {
            if (*temp < '0' || *temp > '9') return 0;
            temp++;
        }
        inputs_count++;
        ptr++;
    }

    if (inputs_count > 3) {
        return 0;
    }

    for (int i = 0; mode != NULL && mode[i] != '\0'; i++) {
        if (i > 1) return 0;
        if (i == 0) {
            if (mode[i] != 'a' && mode[i] != 'A' && mode[i] != 'p' && mode[i] != 'P') return 0;
            midday = mode[i] == 'a' || mode[i] == 'A' ? AM : PM;
            time_mode = TIME_M_12H;
        }
        if (i == 1) {
            if (mode[i] != 'm' && mode[i] != 'M') return 0;
        }
    }

    if (time_mode == TIME_M_12H) {
        uint8_t h = eval_int(time[0]);
        if (h < 0 || h > 12) return 0;
        if (midday == AM && h > 11) return 0;
        if (midday == PM && h < 1) return 0;
    }

    if (time_mode == TIME_M_24H) {
        uint8_t h = eval_int(time[0]);
        if (h < 0 || h > 23) return 0;
    }

    ptr = time + 1;
    while (*ptr != NULL) {
        uint8_t v = eval_int(*ptr);
        if (v < 0 || v > 59) return 0;
        ptr++;
    }

    return 1;
}

uint8_t time_init(Time *t, char *input_str) {
    char **inputs = str_explode(input_str, ' '), **ptr = inputs;
    uint8_t inputs_count = 0;

    while (*ptr != NULL) {
        inputs_count++;
        ptr++;
    }

    if (inputs_count > 2) {
        return 0;
    }

    char **time = str_explode(inputs[0], ':');
    char *mode = inputs[1] ? inputs[1] : NULL;

    if (!time_validator(time, mode)) return 0;

    t->mode = mode == NULL ? TIME_M_24H : TIME_M_12H;
    t->midday = mode != NULL ? mode[0] == 'a' || mode[0] == 'A' ? AM : PM : UNSET;

    t->hours = eval_int(time[0]);
    if (t->midday == PM && t->hours < 12) t->hours += 12;

    t->minutes = time[1] ? eval_int(time[1]) : 0;
    t->seconds = time[1] && time[2] ? eval_int(time[2]) : 0;
    t->total_seconds = t->hours * 60 * 60 + t->minutes * 60 + t->seconds;

    return 1;
}

void convert_12h_to_24h_time_mode(Time *t) {
    if (t->mode == TIME_M_24H) return;

    if (t->midday == PM && t->hours < 12) {
        t->hours += 12;
    }

    t->mode = TIME_M_24H;
    t->midday = UNSET;
}

void convert_24h_to_12h_time_mode(Time *t) {
    if (t->mode == TIME_M_12H) return;

    if (t->hours < 12) {
        t->midday = AM;
    } else {
        if (t->hours > 12) t->hours -= 12;
        t->midday = PM;
    }

    t->mode = TIME_M_12H;
}

void time_print(Time t) {
    convert_12h_to_24h_time_mode(&t);
    printf("%02d:%02d:%02d", t.hours, t.minutes, t.seconds);

    printf(" <OR> ");

    convert_24h_to_12h_time_mode(&t);
    printf("%02d:%02d:%02d %s", t.hours, t.minutes, t.seconds, t.midday == AM ? "AM" : "PM");
}

uint32_t calculate_duration(Time t1, Time t2) {
    convert_12h_to_24h_time_mode(&t1);
    convert_12h_to_24h_time_mode(&t2);

    return (uint32_t)abs(t1.total_seconds - t2.total_seconds);
}

void flush_stdin() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(int argc, char const *argv[]) {
    char input_str[50], **inputs = NULL, **ptr = NULL;
    int inputs_count = 0;
    Time t1, t2;

    while (1) {
        printf("This program will calculate the duration between two time inputs provided by you\n");
        printf("You can use either 24H mode or 12H mode\n");
        printf("For 24H mode simply enter time following this format -> 23:00:00\n");
        printf("For 12H mode simply enter time following this format -> 11:00:00 AM or 11:00:00 PM\n");
        printf("(note:minutes and seconds values can be ignored in either modes)\n");
        printf("type (e) to exit \n\n");

        printf("First Time Interval  : ");

        scanf(" %50[^\n]", input_str);
        if (input_str[0] == 'e' || input_str[0] == 'E') break;

        if (!time_init(&t1, input_str)) {
            printf("\nInvalid Input!\n\n");
            continue;
        }
        flush_stdin();

        printf("Second Time Interval : ");

        scanf(" %50[^\n]", input_str);
        if (input_str[0] == 'e' || input_str[0] == 'E') break;

        if (!time_init(&t2, input_str)) {
            printf("\nInvalid Input!\n\n");
            continue;
        }
        flush_stdin();

        printf("\nFirst Time Interval Given  : ");
        time_print(t1);
        printf("\nSecond Time Interval Given : ");
        time_print(t2);
        printf("\n\n");

        uint32_t duration = calculate_duration(t1, t2);

        printf("Duration Calculated Between Two Time Intervals Is : %02d Hours, %02d Minutes, %02d Seconds\n\n",
               duration / (60 * 60), duration % (60 * 60) / 60, duration % 60);

        char c;
        printf("type (e) to exit or hit enter to start over > ");
        scanf("%c", &c);
        if (c == 'e' || c == 'E') break;
        if (c != '\n') flush_stdin();
        system("cls");
    }
    return 0;
}