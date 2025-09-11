/*

TIME Pn					// save current time & data in string reg[Pn] . exp : reg[R1] = "2025/1/11 21:45:56"

OPEN R1 R2 R3 			// opening file from path which saved in reg[R1] in method which in reg[R2] and point to it by File* from R3 . reg[R3] = fopen( reg[R1] , reg[R2] );

CLOS R1                 // close a file. R1 is the open file.

READ R1 				// read and print file from File* in reg[R1]

WRIT R1 R2				// write a line str* from reg[R1] to File* reg[R2]

APND R1 R2				// append a line str* from reg[R1] to File* reg[R2]

MAKE R1	R2				// make a file by name str* reg[R1] and save it in R2

KILL R1					// delete a file by name str* reg[R1]

RUNF R1					// open & boot & load & run program which reg[r1] point to : example in our prj :  ( reg[R1] is a char pointer )   reg[R1]="prg.txt"; loader(reg[R1]); which_ram = !OS;

CLER 					// clear screen : system("cls")
*/
//-----------------------| HEADERS |----------------------//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../headers/loader.h"
#include "../headers/memory_struct.h" // include for global memory arrays .
#include "../headers/colorama.h" //   >>> for CTCT
//--------------------------------------------------------//
//--------------------------------------------------------//
#define RAW_ADDRESS "../DisassemblyPograms/"
//--------------------------------------------------------//
//--------------------------------------------------------//

//--------| TIME |--------//
void showTime(int eip)
{
    if (which_ram == OS)
    {
        int rn = os_ram[eip].v1;
        char *dest = (char *)registers[rn].address;
        SYSTEMTIME t;
//        SYSTEMTIME is a struct that define in windows.h =>>
//        typedef struct _SYSTEMTIME {
//        WORD wYear;         // مثلاً 2025
//        WORD wMonth;        // از 1 تا 12
//        WORD wDay;          // از 1 تا 31
//        WORD wHour;         // از 0 تا 23
//        WORD wMinute;       // از 0 تا 59
//        WORD wSecond;       // از 0 تا 59
//        WORD wMilliseconds; // صدم ثانیه (اینجا استفاده نشده)
//        WORD wDayOfWeek;    // 0 (Sunday) تا 6 (Saturday) - اینم استفاده نمی‌شه
//    } SYSTEMTIME;
        GetLocalTime(&t); // one of the API of the WINDOWS

        sprintf(dest, "%04d/%d/%d %02d:%02d:%02d",
                t.wYear,
                t.wMonth,
                t.wDay,
                t.wHour,
                t.wMinute,
                t.wSecond);
        os_eip++;
    }
    else
    {
        int rn = pr_ram[eip].v1;
        char *dest = (char *)registers[rn].address;
        SYSTEMTIME t;
        GetLocalTime(&t);

        sprintf(dest, "%04d/%d/%d %02d:%02d:%02d",
                t.wYear,
                t.wMonth,
                t.wDay,
                t.wHour,
                t.wMinute,
                t.wSecond);
        pr_eip++;
    }
}

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
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
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
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        registers[r3].address = (void *) p;
        pr_eip++;
    }
}
//--------| CLOS |--------//
void closeFile(int eip)
{
    if (which_ram==OS)
    {
        int r1 = os_ram[eip].v1;
        FILE *p = (FILE *) registers[r1].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        fclose(p);
        registers[r1].address = NULL;
        os_eip++;
    }
    else
    {
        int r1 = pr_ram[eip].v1;
        FILE *p = (FILE *) registers[r1].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        fclose(p);
        registers[r1].address = NULL;
        pr_eip++;
    }
}

//--------| READ |--------//
void readFile(int eip)
{
    if (which_ram==OS)
    {
        int r1 = os_ram[eip].v1;
        FILE *p = (FILE *) registers[r1].address;
        FILE *p1 = p;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        int ch = fgetc(p);
        while (ch != EOF)
        {
            putchar(ch);
            ch = fgetc(p);
        }
        os_eip++;
        p = p1;
    }
    else
    {
        int r1 = pr_ram[eip].v1;
        FILE *p = (FILE *) registers[r1].address;
        FILE *p1 = p;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        int ch = fgetc(p);
        while (ch != EOF)
        {
            putchar(ch);
            ch = fgetc(p);
        }
        pr_eip++;
        p = p1;
    }
}
//--------| FGET |--------//
void getword(int eip)
{
    if (which_ram==OS)
    {
        int r1 = os_ram[eip].v1,
			r2 = os_ram[eip].v2;
        FILE *p = (FILE *) registers[r1].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
		int value = fgetc(p) ;
		switch (registers[r2].type) {
			case 'I':
				*((int * )registers[r2].address)= value ;
				break;
			default:
				*((char * )registers[r2].address)= (char)value ;
				break;
		}
        os_eip++;
    }
    else
    {
        int r1 = pr_ram[eip].v1,
			r2 = pr_ram[eip].v2;
		
        FILE *p = (FILE *) registers[r1].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
		int value = fgetc(p) ;
		switch (registers[r2].type) {
			case 'I':
				*((int * )registers[r2].address)= value ;
				break;
			default:
				*((char * )registers[r2].address)= (char)value ;
				break;
        }
        pr_eip++;
    }
}

//--------| WRIT |--------//
void writeFile(int eip)
{
    if (which_ram==OS)
    {
        int r1 = os_ram[eip].v1,
            r2 = os_ram[eip].v2;
        char *line = (char *) registers[r1].address;
        FILE *p = (FILE *) registers[r2].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        unsigned long long len = strlen(line);
        fwrite(line, sizeof(char),len,p);
        os_eip++;
    }
    else
    {
        int r1 = pr_ram[eip].v1,
            r2 = pr_ram[eip].v2;
        char *line = (char *) registers[r1].address;
        FILE *p = (FILE *) registers[r2].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        unsigned long long len = strlen(line);
        fwrite(line, sizeof(char),len,p);
        pr_eip++;
    }
}

//--------| APND |--------//RED printf reset
// just like writeFile. when you write THE OS be careful about the type of "fopen"
void appendFile(int eip)
{
    if (which_ram==OS)
    {
        int r1 = os_ram[eip].v1,
            r2 = os_ram[eip].v2;
        char *line = (char *) registers[r1].address;
        FILE *p = (FILE *) registers[r2].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        unsigned long long len = strlen(line);
        fwrite(line, sizeof(char),len,p);
        os_eip++;
    }
    else
    {
        int r1 = pr_ram[eip].v1,
            r2 = pr_ram[eip].v2;
        char *line = (char *) registers[r1].address;
        FILE *p = (FILE *) registers[r2].address;
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        unsigned long long len = strlen(line);
        fwrite(line, sizeof(char),len,p);
        pr_eip++;
    }
}

//--------| MAKE |--------//
// I changed the definition
void makeFile(int eip)
{
    if (which_ram==OS)
    {
        int r1 = os_ram[eip].v1,
            r2 = os_ram[eip].v2;
        char *name = (char *) registers[r1].address;
        FILE *p = fopen(name, "w");
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        registers[r2].address=p;
        os_eip++;
    }
    else
    {
        int r1 = pr_ram[eip].v1,
            r2 = pr_ram[eip].v2;
        char *name = (char *) registers[r1].address;
        FILE *p = fopen(name, "w");
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
        }
        registers[r2].address=p;
        pr_eip++;
    }
}

//--------| KILL |--------//
void deleteFile(int eip)
{
    if (which_ram==OS)
    {
        int r1 = os_ram[eip].v1;
        char *name = (char *) registers[r1].address;
        int isAvailable = remove(name);

        if(isAvailable == 0)
        {
            printf("Successfully removed a file\n");
        }
        else
        {
            printf("Error in removing. please check if the file exists in directory\n");
        }

        os_eip++;
    }
    else
    {
        int r1 = pr_ram[eip].v1;
        char *name = (char *) registers[r1].address;
        int isAvailable = remove(name);

        if(isAvailable == 0)
        {
            printf("Successfully removed a file\n");
        }
        else
        {
            printf("Error in removing. please check if the file exists in directory\n");
        }

        pr_eip++;
    }
}

//--------| RUNF |--------//
void runProgram(int eip)    // --------> we have only one pr_ram , so can't run os and 2 prg , at most os & 1 prg ...
{
    int r1 = pr_ram[eip].v1;
    char *name = (char *) registers[r1].address;
    int i=0;

    while (name[i] != '\0') i++;
    size_t len = strlen(name);
    size_t cap = len + 35;
    char *newName = malloc(cap);
    newName[0] = '\0';  // ensure the buffer starts as an empty string for safe "strcat" operations
    strcat(newName,RAW_ADDRESS);
    strcat(newName, name);
    strcat(newName, ".txt");
    loader(newName);
    free(newName);

    which_ram = (!OS) ;
    os_eip++;
    pr_eip=0;

}

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
// Created By MmdX 21:04

