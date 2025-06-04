#include <stdio.h>

void lknow()
{
    char a[100];
    int c;
    int count=1;
    FILE *p;

    printf("Use .txt or any other extension to cknow\nEx: hello.txt\n\n");
    printf("Enter existing file name: ");
    scanf("%s", a);

    p = fopen(a, "r");

    if(p == NULL)
    {
        printf("The file is not found\n");
        return;
    }

    c = fgetc(p);
    while(c != EOF)
    {
        if(c == '\n')
        {
            count++;
        }
        c = fgetc(p);
    }

    fclose(p);

    printf("Number of lines = %d\n", count);
}

