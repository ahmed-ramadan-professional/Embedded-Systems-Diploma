#include <stdio.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        float r = 0;

        printf("Enter the radius of a circle to calculate its area and circumference : ");
        scanf("%f", &r);

        printf("The area is : %f and the circumference is : %f\n", (3.14f)*r*r,2.0f*(3.14f)*r);
        printf("(note : PI has been set to equal \"3.14\" contact the owner for more precious calculations)\n");

    }
    return 0;
}
