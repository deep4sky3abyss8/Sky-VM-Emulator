#include <stdio.h>
#include <stdlib.h>
#include "headers/loader.h"
#include <windows.h> // for Sleep(timeByMiliSec); function to make runtime more slowdown
#include "headers/machine_lan.h"
#include "headers/disassmbly.h"
#include "headers/memory_struct.h"
//--------------------------------------------  define   -------------------
#define BOOT_ADDRESS "DisassemblyPograms/os.txt"
//--------------------------------------------  main src   -----------------
int main(void) {
    welcome();
    loader(BOOT_ADDRESS);
    os_eip=0 ;
    // fixing boot protocol and way .
    // we need to define a const char string for booting os as rom .
    // need opening file , split , parse , ... FILEs function implement .
    // need protocole to filling rams first for os and after api disassbly func for programs .
    // need infinit loop for checking commmands and work by rams .
    // many if and else in loop for command checking .
    // api implement disassembly funcs .
    
    return 0;
}
