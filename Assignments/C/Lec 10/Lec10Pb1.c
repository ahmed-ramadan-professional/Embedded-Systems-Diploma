#include <stdint.h>
#include <stdio.h>

char getBit(uint32_t value, char bit) {
    if (bit > 31) return 0;
    return (value & (1 << bit)) >> bit;
}

void setBit(uint32_t *addr, char bit) {
    if (bit > 31) return;
    *addr |= (1 << bit);
}

char isAllCharactersDistinct(char *str) {
    uint32_t occurrences[3] = {0, 0, 0};
    while (*str != '\0') {
        if (getBit(occurrences[*str / 32 - 1], *str % 32)) return 0;
        setBit(&occurrences[*str / 32 - 1], *str % 32);
        str++;
    }
    return 1;
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

        printf("Enter a string to check if all its characters are distinct or not\n");
        printf("Wide Range of characters can be tested from ASCII[32] to ASCII[127]\n");
        printf("Including alphabit, numbers, spaces, Symbols, Etc .. \n");
        printf("type \"exit\" to quit the program\n");
        printf("> ");

        scanf(" %100[^\n]", str);
        if (isExitSequencePressentAtStart(str)) break;

        printf("\nAll the characters in the string given [%s] are%s distinct\n\n", str, isAllCharactersDistinct(str) ? "" : " not");
    }
    return 0;
}
