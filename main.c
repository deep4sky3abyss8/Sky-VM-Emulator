# include <stdio.h>
# include <stdlib.h>
#define OS 1
//------------------------------------------------ STRUCTS ---------------
struct regs {  // a register which is a pointer to a place in memory .
    void * address ;
    char type[4]; // type of address of memory , when we want to cast void reg . use it to check typeof cast .
};
struct ram {
    char command[5];
    struct regs
        reg1,  // [+] this part for some commands which get register name , like ASSV R1 R2 , mean *reg[1] = *reg[2] ;
        reg2,
        reg3;
    int data1,  // [+] this part for some commands which get value , like ASSN or JUMP which get line number to jump .
        data2,
        data3 ;// be careful about datas and regs when you want to read program from file and fill ram . check commans then fill .

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
    eip_mem[10] ,  // -> eip registers which tell us which line of program/os we are in .
    which_ram= OS ; // -> it's the global flag which tell us now we are using os ram or programs ram ?!
//
struct regs reg[3] ;
/*read heap_M to understand about it .
 * [+] in worse case our command has 3 argoments so we need 3 registers for handel it .
 * [+] in C for command ASSN Rn Index Type : reg[Rn].address = &(heap
//------------------------------------------------         ----------------