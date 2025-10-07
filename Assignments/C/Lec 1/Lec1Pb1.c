#include <stdio.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        int a = 0, b = 0;

        printf("Enter the two numbers separated by a space to perform the calculations needed : ");
        scanf("%d %d", &a, &b);

        printf("Result = %d\n", ((a+b)*3)-10);
    }
    return 0;
}
