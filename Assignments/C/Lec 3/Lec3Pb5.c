#include <stdio.h>
#include <conio.h>

int main(int argc, char const *argv[])
{
    float a = 0, b = 0;

    
    while (1)
    {
  printf("Enter two floats separated by a space to calculate the floor of their sum : ");

        scanf("%f%f",&a,&b);

        printf("Result %d\n",(int)(a+b));

    }
    return 0;
}
