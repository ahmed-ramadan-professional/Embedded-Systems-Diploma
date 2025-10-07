#include <stdint.h>
#include <stdio.h>

void convertUpperToLower(char *str) {
    while (*str != '\0') {
        if (*str >= 'A' && *str <= 'Z') *str += 32;
        str++;
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

        printf("Enter a string to convert all of its uppercase characters to lowercase\n");
        printf("other characters beside uppercase ones won't be affected\n");
        printf("type \"exit\" to quit the program\n");
        printf("> ");

        scanf(" %100[^\n]", str);
        if (isExitSequencePressentAtStart(str)) break;

        printf("\nString given [Before Conversion] : %s\n", str);
        convertUpperToLower(str);
        printf("String given [After Conversion]  : %s\n\n", str);
    }
    return 0;
}
