#ifndef memory_struct_h
#define memory_struct_h
//
extern const struct ram os_ram[] ;
extern struct ram pr_ram[] ;
extern struct heap_s heap ;
/* heap memory of programs and os . access by register pointers .
 * [+] passing address of them by assembly command : MOVE {register number} {heap index} {type:str/int/chr}
*/
extern int stck_mem[] ,
           os_eip ,  // point to line of ram which read .
           pr_eip ,
           which_ram ;
extern struct regs registers[] ;
/*
struct ram {
    char command[5];
    int v1,
        v2,
        v3;
};
struct heap_s { // short for heap segment .
    int ints[100];
    char chrs[100],
         strs[1000];
};
struct regs {  // a register which is a pointer to a place in memory .
    void * address ;
    char type[4]; // type of address of memory , when we want to cast void reg . use it to check typeof cast .
};
*/
#endif