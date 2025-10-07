#include <stdio.h>
#include <stdlib.h>

unsigned int len(char *str) {
    unsigned int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}

char *concatenateStrings(char *str_1, char *str_2) {
    unsigned int size = len(str_1) + len(str_2) + 1;
    char *str = (char *)malloc(size * sizeof(char)), *p = str;

    while (*str_1 != '\0') *p++ = *str_1++;
    while (*str_2 != '\0') *p++ = *str_2++;

    *p = '\0';
    return str;
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
        char str_1[101], str_2[101];

        printf("Enter two strings to be concatenated together\n");
        printf("type \"exit\" to quit the program\n");

        printf("First String > ");
        scanf(" %100[^\n]", str_1);
        if (isExitSequencePressentAtStart(str_1)) break;

        printf("Second String > ");
        scanf(" %100[^\n]", str_2);
        if (isExitSequencePressentAtStart(str_2)) break;

        printf("\nResult String concatenated from String 1 [%s] and String 2 [%s] is : %s\n\n", str_1, str_2, concatenateStrings(str_1, str_2));
    }
    return 0;
}
