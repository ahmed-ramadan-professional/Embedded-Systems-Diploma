#include <stdint.h>
#include <stdio.h>

char *getLastAddr(char *str) {
    char *last = str;

    while (*str != '\0') {
        last = str++;
    }

    return last;
}

void reverseString(char *str) {
    char *last = getLastAddr(str);

    while (str <= last && *str != '\0') {
        char temp = *str;
        *str++ = *last;
        *last-- = temp;
    }
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

        printf("Enter a string to be reversed\n");
        printf("type \"exit\" to quit the program\n");
        printf("> ");

        scanf(" %100[^\n]", str);
        if (isExitSequencePressentAtStart(str)) break;

        printf("\nString given [Before Reversal] : %s\n", str);
        reverseString(str);
        printf("String given [After Reversal]  : %s\n\n", str);
    }
    return 0;
}
