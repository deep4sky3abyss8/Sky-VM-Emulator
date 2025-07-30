/*

TIME Pn					// save current time & data in string reg[Pn] . exp : reg[R1] = "2025/1/11 21:45:56"

OPEN R1 R2 R3 			// opening file from path which saved in reg[R1] in method which in reg[R2] and point to it by File* from R3 . reg[R3] = fopen( reg[R1] , reg[R2] );

READ R1 				// read and print file from File* in reg[R1]

WRIT R1 R2				// write a line str* from reg[R1] to File* reg[R2]

APND R1 R2				// append a line str* from reg[R1] to File* reg[R2]

CLER 					// clear screen : system("cls")

MAKE R1					// make a file by name str* reg[R1]

CLOS R1

KILL R1					// delete a file by name str* reg[R1]

RUNF R1					// open & boot & load & run program which reg[r1] poit to : example in our prj :  ( reg[R1] is a char pointer )   reg[R1]="prg.txt"; loader(reg[R1]); which_ram = !OS;

*/
//-----------------------| HEADERS |----------------------//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../headers/memory_struct.h" // include for global memory arrays .
#include "../headers/colorama.h" //   >>> for CTCT
//--------------------------------------------------------//
//--------| TIME |--------//

//--------| OPEN |--------//
void openFile(int eip)
{
    if (which_ram == OS)
    {
        int r1 = os_ram[eip].v1,
            r2 = os_ram[eip].v2,
            r3 = os_ram[eip].v3;
        char * path = (char *)registers[r1].address ,
             * type = (char *)registers[r2].address;
        FILE *p = fopen(path,type);
        registers[r3].address = (void *) p;
        os_eip++;
    }
    else
    {
        int r1 = pr_ram[eip].v1,
            r2 = pr_ram[eip].v2,
            r3 = pr_ram[eip].v3;
        char * path = (char *)registers[r1].address ,
             * type = (char *)registers[r2].address;
        FILE *p = fopen(path,type);
        registers[r3].address = (void *) p;
        pr_eip++;
    }
}
//--------| CLOS |--------//

//--------| READ |--------//

//--------| WRIT |--------//

//--------| APND |--------//

//--------| MAKE |--------//

//--------| KILL |--------//

//--------| RUNF |--------//

//--------| CLER |--------//
void clear_screen(int eip){
    if (which_ram == OS){
        os_eip++ ;
    }
    else{
        pr_eip++ ;
    }
    system("cls") ;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CTCT color(R/G/B/Y/0)			// change terminal color to R->red , G->green ,  B->blue , Y->yellow , 0->reset		be carefull if you don't reset , it will not reset atumaticly !!!!!

//--------| CTCT |--------//
void change_terminal_color_to( int eip ){
    if (which_ram==OS){
        char color = os_ram[eip].v1 ;
        switch (color) {
        case 'R' :
            RED
            break; 
        case 'G' :
            GREEN
            break;
        case 'B' :
            BLUE
            break;
        case 'Y' :
            YELLOW
            break;
        default :
            RESET
            break;
        }
        os_eip++ ;
    }
    else {
        char color = pr_ram[eip].v1 ;
        switch (color) {
        case 'R' :
            RED
            break;
        case 'G' :
            GREEN
            break;
        case 'B' :
            BLUE
            break;
        case 'Y' :
            YELLOW
            break;
        default :
            RESET
            break;
        }
        pr_eip++;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
