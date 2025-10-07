#include <stdio.h>
#include <conio.h>

int main(int argc, char const *argv[])
{
    int t=0,d=0;

    
    while (1)
    {
        printf("Enter water temperature to calculate the required heater activation time : ");

        scanf("%d",&t);

        if(t<0 || t >100){
            printf("Invalid Input!\n");
            continue;
        }

        if(t>=0 && t<=30){
            d=7;
        }
        else if(t<=60){
            d=5;
        }
        else if(t<=90){
            d=3;
        }
        else{
            d=1;
        }

        printf("The required heater activation time is : %d\n",d);

    }
    return 0;
}
