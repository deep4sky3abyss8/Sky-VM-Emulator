#include <stdio.h>
#include <stdlib.h>
#include "../headers/loader.h"
#include "../headers/machine_lan.h"
#include "../headers/colorama.h"
#include "../headers/disassmbly.h"
#include "../headers/memory_struct.h"
#include "../headers/WndHijack.h"
#include "../headers/api.h"
#include <windows.h>
//--------------------------------------------[  define  ]-------------------
//--------------------------------------------[  define  ]-------------------
#define BOOT_ADDRESS "../DisassemblyPograms/os.txt"
//--------------------------------------------[   external var src  ] -----------------
int stck_mem[100] , // short for stack memory segment .
    os_eip=0 ,  // -> eip registers which tell us which line of program/os we are in .
    pr_eip=0 ,
    which_ram= OS ;
//--------------------------------------------[  main src  ]-----------------
int main(void) {


    HIJACK_FULL_SCREEN
    HIJACK_MAXIMIZE_BTM
    wellcome();
    loader(BOOT_ADDRESS);
    Sleep(500);
    system("cls");


    os_eip=0 ;
    int *eip ;



    while (1) {


        if (which_ram==OS){     eip = &os_eip;  }
        else{                   eip = &pr_eip;  }



        if(command_cmp(*eip , _ASSN_ ))
            assigne_num(*eip);
        else if (command_cmp(*eip , _ASSV_ ))
            assign_var(*eip);
        else if (command_cmp(*eip , _MOVE_ ))
            move_to_reg(*eip) ;
        else if (command_cmp(*eip , _COMP_ ))
            compare(*eip);
        else if (command_cmp(*eip , _EQAL_ ))
            equal(*eip);
        else if (command_cmp(*eip , _NEQL_ ))
            not_equal(*eip);
        else if (command_cmp(*eip , _CJMP_ ))
            con_jump(*eip);
        else if (command_cmp(*eip , _JUMP_ ))
            jump(*eip);
        else if (command_cmp(*eip , _HALT_ )){
            if (!halt(*eip))
                continue;
            break;
        }
        else if (command_cmp(*eip , _PUTC_ ))
            put_char(*eip);
        else if (command_cmp(*eip , _PUTS_ ))
            put_str(*eip);
        else if (command_cmp(*eip , _PUTI_ ))
            put_int(*eip);
        else if (command_cmp(*eip , _PUSH_ ))
            push_str(*eip);
        else if (command_cmp(*eip , _STOR_ ))
            store_char(*eip);
        else if (command_cmp(*eip , _ADDN_ ))
            add_ints(*eip);
        else if (command_cmp(*eip , _ADDO_ ))
            plus_one(*eip);
        else if (command_cmp(*eip , _MULT_ ))
            mult_ints(*eip);
        else if (command_cmp(*eip , _DIVI_ ))
            div_ints(*eip);
        else if (command_cmp(*eip , _MODE_ ))
            mode_ints(*eip);
        else if (command_cmp(*eip , _GETC_ ))
            get_char(*eip);
        else if (command_cmp(*eip , _GETS_ ))
            get_str(*eip);
        else if (command_cmp(*eip , _GETI_ )){
            get_int(*eip);
        }



        //============[ LOGICAL ]=============
        else if (command_cmp(*eip , _ANDC_ ))
            and(*eip);
        else if (command_cmp(*eip , _ORLC_ ))
            or(*eip);
        else if (command_cmp(*eip , _NOTC_ ))
            not(*eip);




        //==============[ API ]===============
        /*====================================*/
        else if (command_cmp(*eip , _TIME_ ))
            {showTime(* eip);}
		else if (command_cmp(*eip , _FGET_ ))
            {getword(* eip);}
        else if (command_cmp(*eip , _OPEN_ ))
            {openFile(* eip) ;}
        else if (command_cmp(*eip , _READ_ ))
            {readFile(* eip);}
        else if (command_cmp(*eip , _WRIT_ ))
            {writeFile(* eip);}
	    else if (command_cmp(*eip , _CLOS_ ))
            {closeFile(* eip);}
        else if (command_cmp(*eip , _APND_ ))
            {appendFile(* eip);}
        else if (command_cmp(*eip , _MAKE_ ))
            {makeFile(* eip);}
        else if (command_cmp(*eip , _KILL_ ))
            {deleteFile(* eip);}
        else if (command_cmp(*eip , _RUNF_ ) && which_ram==OS )
            {runProgram(* eip);}
        
        else if (command_cmp(*eip , _CLER_ )){
            clear_screen(*eip);
        }
        else if (command_cmp(*eip , _CTCT_ )){
            change_terminal_color_to(*eip);
        }



        //====================================
        else {
            
            if (which_ram==OS) {
                RED
                fprintf(stderr, "[!]Fatal Error occurred in < Operating System >\nInvalid disassembly command : <%s>\n",os_ram[os_eip].command);
                RESET
                exit(1);
            }
            else {
                RED
                fprintf(stderr, "[!]Fatal Error occurred in < Program running>\nInvalid disassembly command : <%s>\n",pr_ram[pr_eip].command);
                RESET
                exit(2);
            }
        }
    }

    
    // shut down box ->
    Shutdownsky();
    RESET_HIJACKING
    return 0;
}
