#include <stdio.h>
#include <conio.h>

const char *ascii_names[128] = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
    "Backspace", "Tab", "Enter", "VT", "FF", "CR", "SO", "SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
    "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US",
    "Space", "!", "\"", "#", "$", "%", "&", "\'",
    "(", ")", "*", "+", ",", "-", ".", "/",
    "0", "1", "2", "3", "4", "5", "6", "7",
    "8", "9", ":", ";", "<", "=", ">", "?",
    "@", "A", "B", "C", "D", "E", "F", "G",
    "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W",
    "X", "Y", "Z", "[", "\\", "]", "^", "_",
    "`", "a", "b", "c", "d", "e", "f", "g",
    "h", "i", "j", "k", "l", "m", "n", "o",
    "p", "q", "r", "s", "t", "u", "v", "w",
    "x", "y", "z", "{", "|", "}", "~", "DEL"};

int main(int argc, char const *argv[])
{
    int c = 0;

    printf("Enter any \"printable character\" to check whether it's in the alphabet or not\n");

    while (1)
    {
        c = getch();

        if(c == 0 || c == 224){getch();printf("Extended Characters are Out of Scope!\n");continue;} //ignore extended characters

        printf("%s", ascii_names[c]);

        (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? printf(" in the alphabet\n") : printf(" not in the alphabet\n");
    }
    return 0;
}
