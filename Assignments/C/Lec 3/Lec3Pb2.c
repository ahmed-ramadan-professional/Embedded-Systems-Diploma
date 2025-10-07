#include <stdio.h>
#include <conio.h>

int main(int argc, char const *argv[])
{
    int c = 0;

    printf("Enter any lowercase letter in the alphabet and it will be converted to uppercase : \n");
    printf("(note : any other inputs besides lowercase letters will be ignored)\n");

    while (1)
    {
        c = getch();

        if ((c < 'a' || c > 'z') ) {getch();continue;} //ignore anything other than lowercase letters
        
        printf("%C => %c\n", c, c-32);
    }
    return 0;
}
