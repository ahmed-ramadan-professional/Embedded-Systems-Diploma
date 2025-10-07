#include <stdint.h>
#include <stdio.h>

unsigned int len(char *str) {
    unsigned int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}

char isExitSequencePressentAtStart(char *str) {
    char exit[5] = "exit";
    for (int i = 0; i < 4; i++) {
        if (str[i] == '\0' || str[i] != exit[i]) return 0;
    }
    return 1;
}

int main(int argc, char const *argv[]) {
    while (1) {
        char str[101];

        printf("Enter a string to count all of its characters (including spaces)\n");
        printf("type \"exit\" to quit the program\n");
        printf("> ");

        scanf(" %100[^\n]", str);
        if (isExitSequencePressentAtStart(str)) break;

        printf("\nString Given    : %s", str);
        if (str[len(str) - 1] == ' ') printf("[EOF]");
        printf("\nSize Calculated : %d\n\n", len(str));
    }
    return 0;
}
