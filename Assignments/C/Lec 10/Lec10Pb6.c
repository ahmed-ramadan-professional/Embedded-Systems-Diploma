#include <stdint.h>
#include <stdio.h>

void removeNonAlphabet(char *str) {
    char *overwrite_pointer = str;
    while (*str != '\0') {
        if ((*str < 'A' || *str > 'Z') && (*str < 'a' || *str > 'z')) {
            str++;
            continue;
        }

        *overwrite_pointer = *str;

        str++;
        overwrite_pointer++;
    }
    *overwrite_pointer = '\0';
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

        printf("Enter a string to non-alphabet characters in it\n");
        printf("type \"exit\" to quit the program\n");
        printf("> ");

        scanf(" %100[^\n]", str);
        if (isExitSequencePressentAtStart(str)) break;

        printf("\nString given [Before Removal] : %s\n", str);
        removeNonAlphabet(str);
        printf("String given [After Removal]  : %s\n\n", str);
    }
    return 0;
}
