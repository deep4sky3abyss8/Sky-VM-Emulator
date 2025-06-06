
#include <stdio.h>
#include <windows.h> // for Sleep(timeByMiliSec); function to make runtime more slowdow
#include <unistd.h>
void printbydilay(char str[] , int firsdilay , int secenddilay ){
    int index ;
    for(index=0 ; str[index]!='\0' ; index++ ){
        putchar(str[index]);
        Sleep(firsdilay);
    }
    Sleep(secenddilay);
}
void wellcome(void){
    printf("----------------------------------------------------------------------\n");
    Sleep(2000);
    printbydilay("|\tHi Pretty Honny ! \n" , 70 , 1000 );
    printbydilay( "|\tWellcome to Tea_Library_v1.0.0 Our first Modular Project \n|\n" , 70 , 1000 );
    printbydilay("|\tWhat You Want ? Just Tell Us !\n|\n" , 70 , 1000);
    printbydilay("|\t1. TeaInfo : For all Tea(books) we have\n",60,900);
    printbydilay("|\t2. FindTea : For finding a tea(book) in Our lib \n" , 60 , 900);
    printbydilay("|\t3. AddTea : For adding a tea into Our lib  \n|\n",60 , 900 );
    printbydilay("|\t4. Exit\n",60,900);
    printf("----------------------------------------------------------------------\n");
    printbydilay("loading ",200,0);
    printf(" ____________________________________________\rloading ");
    Sleep(500);
    printbydilay("#############################################",500,0);
    printf("\r                                                     \r");
    Sleep(1000);
}
/*int main(void){
    wellcome();
    return 0;}
// Created by SkyAbyss on 6/6/2025.*/
