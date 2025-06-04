#include <stdio.h>

int getInt()
{
    int c;
    int num=0;
    while((c=getchar())!= '\n')
    {
        num = (num * 10) + (c-'0');
    }
    return num;
}

char isEven(int num)
{
    if (num%2==0)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
}

int main()
{
    int x=getInt();
    isEven(x);
}