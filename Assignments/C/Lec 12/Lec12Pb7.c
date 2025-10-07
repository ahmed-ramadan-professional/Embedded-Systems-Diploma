#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// assignment solution
unsigned int len(char *str) {
    unsigned int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}

char *getStringLastTwoCharactersFlipped(char *str) {
    unsigned int str_len = len(str);
    char *output = (char *)malloc(4 * sizeof(char));
    str_len > 1 ? sprintf(output, "%c %c", *(str + str_len - 1), *(str + str_len - 2))
                : sprintf(output, "ERR");
    return output;
}

int main(int argc, char const *argv[]) {
    while (1) {
        char str[101];

        printf("Enter a string to echo back its last two characters flipped\n");
        printf("type (e) to exit \n");
        printf("> ");

        scanf(" %100[^\n]", str);
        if (str[0] == 'e' || str[0] == 'E') break;

        printf("\nString Given                : %s", str);
        if (str[len(str) - 1] == ' ') printf("[EOF]");
        printf("\nLast Two Characters Flipped : %s\n\n", getStringLastTwoCharactersFlipped(str));
    }
    return 0;
}
