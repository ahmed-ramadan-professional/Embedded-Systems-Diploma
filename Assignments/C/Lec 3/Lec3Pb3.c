#include <stdio.h>
#include <conio.h>

int main(int argc, char const *argv[])
{
    int a = 0, b = 0;

    
    while (1)
    {
        printf("Enter two integers separated by a space to check whether the first is a multiple of the second : ");

        scanf("%d%d",&a,&b);

        printf("The first integer is%s a multiple of the second integer\n",a%b==0 ? "" : " not");

    }
    return 0;
}
