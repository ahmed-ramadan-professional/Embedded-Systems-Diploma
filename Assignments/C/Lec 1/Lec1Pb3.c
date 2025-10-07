#include <stdio.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        float t = 0;

        printf("Enter the desired degree in Celsius to be converted into Fahrenheit : ");
        scanf("%f", &t);

        printf("The desired degree in Fahrenheit is : %.2f\n", (t*(9.0f/5.0f)+32.0f));
    }
    return 0;
}
