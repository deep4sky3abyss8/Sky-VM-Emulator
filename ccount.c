#include <stdio.h>

void ccount(){

    char a[100];
    int c, count=0;
    FILE *p;

    printf("Use .txt or any other extension to ccount\nEx: hello.txt\n\n");
    printf("Enter existing file name: ");
    scanf("%s", a);

    p = fopen(a, "r");

    if(p == NULL)
    {
        printf("The file is not found\n");
        return;
    }

    c = fgetc(p);
    while(c != EOF){
        if(c != ' ' && c != '\n'){
            count++;
        }
        c = fgetc(p);
    }

    fclose(p);

    printf("Number of characters in file is = %d\n", count);
}
