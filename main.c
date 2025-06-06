# include <stdio.h>
# include <stdlib.h>
#include "headers/typing-wellcome.h"
#include "headers/machine_lan.h"
//------------------------------------------------ STRUCTS ---------------
struct regs {  // a register which is a pointer to a place in memory .
    void * address ;
    char type; // [ I/C/S ] -> short for int/char/str , type of address of memory , when we want to cast void reg . use it to check typeof cast .
};
struct ram {
    char command[5];
    int v1,  // [+] this part for some commands which get value , like ASSN or JUMP which get line number to jump .
        v2,
        v3; // be careful about datas and regs when you want to read program from file and fill ram . check commans then fill .
};
struct heap_s { // short for heap segment .
    int ints[100]; // -> 100 cell for integers .
    char chrs[100],// -> 100 cell for single characters .
         strs[1000];//-> 1000 cell for strings .
};
//------------------------------------------------ GLOBALS ---------------
const struct ram os_ram[1000];
struct ram pr_ram[1000];
struct heap_s heap ;
/* heap memory of programs and os . access by register pointers .
 * [+] passing address of them by assembly command : MOVE {register number} {heap index} {type:str/int/chr}
*/
int stck_mem[100] , // short for stack memory segment .
    os_eip=0 ,  // -> eip registers which tell us which line of program/os we are in .
    pr_eip=0 ,
    which_ram= OS ; // -> it's the global flag which tell us now we are using os ram or programs ram ?!
//
struct regs registers[5];
/*read heap_M to understand about it .
 * [+] in worse case our command has 3 argoments so we need 3 registers for handel it .
 * [+] in C for command ASSN Rn Index Type : reg[Rn].address = &(heap
 */
//--------------------------------------------           -----------------
int main(void) {
    //wellcome() ; // need fix from tea lib to hamda project .
}