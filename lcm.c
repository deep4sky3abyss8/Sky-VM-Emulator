#include <stdio.h>

void lcm(){
    int i, gcd, lcm, a, b;

    printf("Enter two numbers (by pressing enter):\n");
    printf("please enter an integer");
    scanf("%d %d", &a, &b);

    for(i=1; i<=a && i<=b; i++){
        if(a%i==0 && b%i==0){
            gcd = i;
        }
    }

    lcm = (a*b)/gcd;

    printf("LCM = %d\n", lcm);
}