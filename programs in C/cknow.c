#include <stdio.h>

void cknow(){

    char a[100], cha;
    int c, count=0;
    FILE *p;

    printf("Use .txt or any other extension to cknow\nEx: hello.txt\n\n");
    printf("Enter existing file name: ");
    scanf("%s", a);
    p = fopen(a, "r");
    if(p == NULL){
        printf("The file is not found\n");
        return;
    }

    fflush(stdin);
    printf("\nEnter the character to search: ");
    scanf("%c", &cha);

    c = fgetc(p);
    while(c != EOF){
        if(c == cha){
            count++;
        }
        c = fgetc(p);
    }

    fclose(p);

    printf("Number of times '%c' repeated is = %d\n",  cha, count);
}
