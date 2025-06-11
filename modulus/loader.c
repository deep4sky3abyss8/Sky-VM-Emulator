
#include <stdio.h>
#include <windows.h> // for Sleep(timeByMiliSec); function to make runtime more slowdow
#include <unistd.h>
#include <stdlib.h>
#include "../headers/memory_struct.h"
#include "../headers/disassmbly.h"
//-------------------------------------------------------------------------------------------------------
static int read_int(int *num , int index ,char * line) {
    *num = 0 ;
    for ( index ; line[index]!=' ' || line[index]!='\t' ; index++) {
        if (line[index] == '\n' || line[index] == '\0') {
            return 0 ;
        }
        if (line[index]<'0' || line[index]>'9') {  // here let us to assign a character to register cell .
            *num = line[index] ;
            return 0 ;
        }
        *num = (*num)*10 + (line[index]-'0');
    }
    return index;
}
//-------------------------------------------------------------------------------------------------------
static int skip_space(int index , char * line) {
    while(line[index]==' ' || line[index]=='\t') {
        if (line[index] == '\n' || line[index] == '\0')
            return 0 ;
        index++ ;
    }
    return index;
}
//-------------------------------------------------------------------------------------------------------
static int load(char * line , int index ){
    if (which_ram==OS){
        int i=0 ;
        for ( i ; i < 4 ; i++) {
            os_ram[index].command[i] = *(line+i);
        }
        os_ram[index].command[i] = '\0';
        if ( command_cmp( index, "PRIT") ){
            printf("%s\n",line+i);
            return 0 ;
        }
        if (!(i=skip_space(i , line)))
            return 1;
        if (! (i=read_int(&os_ram[index].v1 , i , line)))
            return 1;
        if (!(i=skip_space(i , line)))
            return 1;
        if (! (i=read_int(&os_ram[index].v2 , i , line)))
            return 1;
        if (!(i=skip_space(i , line)))
            return 11;
        read_int(&os_ram[index].v3 , i , line) ;
    }
    else {
        int i=0 ;
        for ( i ; i < 4 ; i++) {
            pr_ram[index].command[i] = *(line+i);
        }
        pr_ram[index].command[i] = '\0';
        if ( command_cmp( pr_ram[index].command, "PRIT") ) {
            printf("%s",line+i);
            return 0 ;
        }
        if (!(i=skip_space(i , line)))
            return 1;
        if (! (i=read_int(&pr_ram[index].v1 , i , line)))
            return 1;
        if (!(i=skip_space(i , line)))
            return 1;
        if (! (i=read_int(&pr_ram[index].v2 , i , line)))
            return 1;
        if (!(i=skip_space(i , line)))
            return 1;
        read_int(&pr_ram[index].v3 , i , line) ;
    }
}
//--------------------------------------------------------------------------------------------------------
int loader( const char* address ) {   // OPEN disassembly command like this but in method "a+"
    FILE* file = fopen( address, "r" );
    int index = 0 ,
        print = 0 ;
    if ( which_ram == OS ) {
        if (file==NULL) {
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        char *buffer;
        size_t bufsize = 50 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        while( fgets( buffer, bufsize, file ) ) {
            if (*buffer<'A' || *buffer>'Z') {
                continue;
            }
            else {
                print=load( buffer , index );
                if (print)
                    index++ ;
            }
        }
        if(index==0) {
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        free(buffer);
    }
    else {
        if (file==NULL) {
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            return 1 ;
        }
        char *buffer;
        size_t bufsize = 50 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            free(buffer);
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            os_eip++ ;
            return 2 ;
        }
        while( fgets( buffer, bufsize, file) ){
            if (*buffer<'A' || *buffer>'Z') {
                continue;
            }
            else {
                print = load( buffer , index );
                if (print)
                    index++ ;
            }
        }
        if(index==0) {
            free(buffer);
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            os_eip++ ;
            return 3 ;
            ;
        }
        free(buffer);
    }
    fclose(file);
    return index ; // how many line readed from file .
}
//--------------------------------------------------------------------------------------------------------
void printbydilay(char str[] , int firsdilay , int secenddilay ){
    int index ;
    for(index=0 ; str[index]!='\0' ; index++ ){
        putchar(str[index]);
        Sleep(firsdilay);
    }
    Sleep(secenddilay);
}
//--------------------------------------------------------------------------------------------------------
/*void wellcome(void){
    printf("----------------------------------------------------------------------\n");
    Sleep(2000);
    printbydilay( "|\tWellcome to AssbOS_v1.0.0 , 2025 Best Os\n|\n" , 70 , 1000 );
    printbydilay("|\tWhat You Want ? Just Tell Us !\n|\n" , 70 , 1000);
    printbydilay("|\t1. Info : For all Tea(books) we have\n",60,900);
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
}*/
//--------------------------------------------------------------------------------------------------------
// Created by SkyAbyss on 6/6/2025.
