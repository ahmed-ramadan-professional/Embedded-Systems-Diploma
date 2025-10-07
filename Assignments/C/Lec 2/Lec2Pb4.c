#include <stdio.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        int n = 0;

        printf("Enter a three digit number to print each digit separated by three spaces : ");
        scanf("%d", &n);

        printf("Result = %d   %d   %d\n", n/100,n%100/10,n%100%10);
    }
    return 0;
}

