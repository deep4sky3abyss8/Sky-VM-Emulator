#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "../headers/colorama.h"

int main(void){
    const char *compile_command = "gcc main.c disassmblyfuncs.c api.c loader.c readfuncs.c -o ++++++MACHINE++++++.exe" ;
        
    YELLOW
    printf("-----------------\n[C&C] compiling start ...\n\n") ;
    RESET

    if ( system(compile_command)){
        RED
        printf("[!]Something Went wrong in compiling ...\n") ;
        RESET
    }
    else{
    GREEN
    printf("[+] Prj compiled successfully ...\n") ;
    RESET
    }
    printf("Press any key to quit ...") ;
    int sleep = getchar() ;
    return 0 ;
         
}