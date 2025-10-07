#include <stdio.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        int n = 0, b = 0;

        printf("Enter a number followed by a space then the bit index you wish to toggle : ");
        scanf("%d%d", &n, &b);

        printf("Result = %d\n", n ^ (1<<b));
    }
    return 0;
}
