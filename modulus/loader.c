
#include <stdio.h>
#include <windows.h> // for Sleep(timeByMiliSec); function to make runtime more slowdow
#include <unistd.h>
#include <stdlib.h>
#include "../headers/memory_struct.h"
#include "../headers/disassmbly.h"
#include "../headers/colorama.h"
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
static void banner(void);
//-------------------------------------------------------------------------------------------------------
static int read_int(int *num , int index ,char * line) {
    *num = 0 ;
   int sign =1 ;
    for ( index ; line[index]!=' ' && line[index]!='\t' ; index++) {
        if (line[index] == '\n' || line[index] == '\0') {
           *num *= sign ;
           if(sign == -1 && num == 0)
              *num = '-' ;            // here if reach mean there's no any digit seen so just was - character.
            return 0 ;
        }
       if(line[index]=='-'){
          sign = -1 ;
          continue;
       }
        if (line[index]<'0' || line[index]>'9') {  // here let us to assign a character to register cell .
            *num = line[index] ;
            return 0 ;
        }
        *num = (*num)*10 + (line[index]-'0');
    }
   *num *= sign ;
    return index;
}
//-------------------------------------------------------------------------------------------------------
static int skip_space(int index , char * line) {
    while(line[index]==' ' || line[index]=='\t') {
        index++ ;
    }
    if (line[index]=='#' || line[index] == '\n' || line[index] == '\0'   ){
        return 0 ;
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
            return 1;
        read_int(&os_ram[index].v3 , i , line) ;
        return 1 ;
    }
    else {
        int i=0 ;
        for ( i ; i < 4 ; i++) {
            pr_ram[index].command[i] = *(line+i);
        }
        pr_ram[index].command[i] = '\0';
        if ( command_cmp( index, "PRIT") ) {
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
        return 1 ;
    }
}
//--------------------------------------------------------------------------------------------------------
int loader( const char* address ) {   // OPEN disassembly command like this but in method "a+"
    FILE* file = fopen( address, "r" );
    int index = 0 ;
    if ( which_ram == OS ) {
        if (file==NULL) {
            RED
            puts("[!][!][!]  Fatal Error : Os Boot Failed  [!][!][!]\n\tOperating System FilePath not found");
            RESET
            exit(1) ;
        }
        char *buffer;
        size_t bufsize = 200 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            RED
            puts("[!][!][!]  Fatal Error : Os Boot Failed  [!][!][!]\n\tmemory allocation failed, free disk");
            RESET
            exit(1) ;
        }
        while( fgets( buffer, bufsize, file ) ) {

            if (  ( *buffer<'A' || *buffer>'Z' )  &&  (*buffer<'a' || *buffer>'z') ){
                continue;
            }
            else {
                if (load( buffer , index ))
                    index++ ;
            }
        }
        if(index==0) {
            RED
            puts("[!][!][!]  Fatal Error : OS Boot Failed  [!][!][!]\n\tYou tried to load an empty file as Operating System!");
            RESET
            exit(1) ;
        }
        free(buffer);
    }
    else {

        if (file==NULL) {
            RED
            puts("> Command not found...");
            which_ram = OS ;
            RESET
            return 1 ;
        }
        char *buffer;
        size_t bufsize = 200 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            RED
            puts("> Command not found...");
            RESET
            which_ram = OS ;
            os_eip++ ;
            return 2 ;
        }
        while( fgets( buffer, bufsize, file) ){

            if (  ( *buffer<'A' || *buffer>'Z' )  &&  (*buffer<'a' || *buffer>'z') ) {
                continue;
            }
            else {
                if (load( buffer , index ))
                    index++ ;
            }
        }
        if(index==0) {
            free(buffer);
            RED
            puts("[!] Program Loading Error \n\tYou tried to load an empty file as program!");
            RESET
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
//--------------------------------------------------------------------------------------------------------
void wellcome(void){
    //fprintf(stderr,"Sky machine : preparing to boot ...\n\n");
    banner();
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tLoading ");
    printbydilay("!\b@\b#\b$\b%%\b^\b&\b*\b :)" , 300 , 600);
}
//--------------------------------------------------------------------------------------------------------
void Shutdownsky(void){
    Sleep(500);
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t[<>] ");
    printbydilay("Shutdown ",100,200);
    printbydilay("|\b/\b\\\b|",300,0);
    Sleep(600);
    return;
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
static void banner(void){

YELLOW
printf(
"\n\n"
"                                                                                                    shV122W5t                                                         \n"
"                                                                                              xsu  5bx      wrYl                                                       \n"
"                                                                                            72styaUt         tgaa                                                      \n"
"                                                                                    zg4ZZ4Xtlqp            xbnl3l                                                     \n"
"                                                                                  vXlbj                      zsjXgun44z                                               \n"
"                                                                                  h00u9                             mwic                                               \n"
"                                                                                p8csnf                             gWbm7Xu vkhjsz                                     \n"
"                                                                                gj                               tUw vofyV6t   v6Zx                                   \n"
"                                                                            rTZjswzjZYw   wtstw                                 7vVw                                  \n"
"                                                                          uXn6n      z1dYpy opwc1z                             jvck3                                  \n"
"                                                                oW1gsum3V61pkfoy       q     zt3 Wz                             zwmYlx                                \n"
"                                                              gXtfiu     xrel dz                yXZX6u                             vjeXw                              \n"
"                                                              9cphbx                                pqfe                             xeqW                              \n"
"                                                              Vriml                                 qxtw                            pxXwU                              \n"
"                                                              Wqvp                     yz                       wcVXdx              vwrWY6iookdZUr                     \n"
"                                                          oTnmx                    eYkrrdZv                  mYp u0wa7                   rprqh4zpZy                   \n"
"                                                  y4Za91XfX hx                   wYx8r    Y8VW3           uvje    hx79exrWWYWaz              zvxj  rpuz              \n"
"                                                  m0ijfyz wWr y               dUhfUtfux    xyvkkm        vYsvjz             r4kb                t yju69rnWv            \n"
"                                                rZomxz                      ttqj                                                                    v5qayXr       \n"
"                                            l17dcYVywty                                                                                              yvz xmt mddc0  \n"
"                                          Vt7py                                                                                                              mniko    \n"
"                                        x xyYigec076443221g9234454332222222221ZZZZYYWY13f7adfijkmmkkjkkjnopqrrrrrqpmjjljiifddaa0877776800aaaddegfgegfa0acaaaa00736evrett5     \n"
"                                                                                                                                                                      \n"
"\n"
"                                                          #######  ##   ## ##    ##     ####   ###  #####   ######  ##   ##  ##  ###   ##  #######\n"
"                                                          ##       ##  ##   ##  ##      ####  #### ##   ## ##       ##   ##  ##  ####  ##  ##\n"
"                                                          #######  #####     ####       ## #### ## ####### ##       #######  ##  ## #  ##  #######\n"
"                                                               ##  ##  ##     ##        ##  ##  ## ##   ## ##       ##   ##  ##  ##  ####  ##\n"
"                                                          #######  ##   ##    ##        ##      ## ##   ##  ######  ##   ##  ##  ##   ###  #######\n"
"                                                          \n"
"                                                          [ Mohammad Mahdi Qasemi Saadat Abadi ]--[ Mohammad Mahdi Tahvildar ]--[ Sajjad Sobhani ]\n"
"\n"
);
RESET
return ;
}

//--------------------------------------------------------------------------------------------------------
// Created by SkyAbyss on 6/6/2025.