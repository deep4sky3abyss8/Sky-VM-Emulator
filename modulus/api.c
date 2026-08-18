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

///--------| TIME |--------//
void showTime(int eip)
{
    int rn = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    if (rn >= 0 && rn < 30 && registers[rn].address != NULL)
    {
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
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

//--------| OPEN |--------//
void openFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    int r2 = (which_ram == OS) ? os_ram[eip].v2 : pr_ram[eip].v2;
    int r3 = (which_ram == OS) ? os_ram[eip].v3 : pr_ram[eip].v3;
    FILE *p = NULL;
    if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 &&
        registers[r1].address != NULL && registers[r2].address != NULL)
    {
        char *path = (char *)registers[r1].address;
        char *type = (char *)registers[r2].address;
        p = fopen(path, type);
        if (!p)
        {
            RED
            printf("The file is not found");
            RESET
            if (which_ram == OS) which_ram = OS;
        }
    }
    if (r3 >= 0 && r3 < 30)
    {
        registers[r3].address = (void *)p;
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}
//--------| CLOS |--------//
void closeFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL)
    {
        FILE *p = (FILE *)registers[r1].address;
        fclose(p);
        registers[r1].address = NULL;
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

//--------| READ |--------//
void readFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL)
    {
        FILE *p = (FILE *)registers[r1].address;
        int ch = fgetc(p);
        while (ch != EOF)
        {
            putchar(ch);
            ch = fgetc(p);
        }
        fseek(p, 0, SEEK_SET);
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}
//--------| FGET |--------//
void getword(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    int r2 = (which_ram == OS) ? os_ram[eip].v2 : pr_ram[eip].v2;
    if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 &&
        registers[r1].address != NULL && registers[r2].address != NULL)
    {
        FILE *p = (FILE *)registers[r1].address;
        int value = fgetc(p);
        switch (registers[r2].type) {
            case 'I':
                *((int *)registers[r2].address) = value;
                break;
            default:
                *((char *)registers[r2].address) = (char)value;
                break;
        }
    }
    else
    {
        RED
        printf("The file is not found");
        RESET
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

//--------| WRIT |--------//
void writeFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    int r2 = (which_ram == OS) ? os_ram[eip].v2 : pr_ram[eip].v2;
    if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 &&
        registers[r1].address != NULL && registers[r2].address != NULL)
    {
        char *line = (char *)registers[r1].address;
        FILE *p = (FILE *)registers[r2].address;
        unsigned long long len = strlen(line);
        fwrite(line, sizeof(char), len, p);
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

//--------| APND |--------//
void appendFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    int r2 = (which_ram == OS) ? os_ram[eip].v2 : pr_ram[eip].v2;
    if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 &&
        registers[r1].address != NULL && registers[r2].address != NULL)
    {
        char *line = (char *)registers[r1].address;
        FILE *p = (FILE *)registers[r2].address;
        unsigned long long len = strlen(line);
        fwrite(line, sizeof(char), len, p);
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

//--------| MAKE |--------//
void makeFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL)
    {
        char *name = (char *)registers[r1].address;
        FILE *p = fopen(name, "w");
        if (!p)
        {
            RED
            printf("can not make file");
            RESET
        }
        else
        {
            fclose(p);
        }
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

//--------| KILL |--------//
void deleteFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL)
    {
        char *name = (char *)registers[r1].address;
        int isAvailable = remove(name);

        if(isAvailable == 0)
        {
            printf("Successfully removed a file\n");
        }
        else
        {
            printf("Error in removing. please check if the file exists in directory\n");
        }
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

//--------| RUNF |--------//
void runProgram(int eip)    // --------> we have only one pr_ram , so can't run os and 2 prg , at most os & 1 prg ...
{
    int r1 = os_ram[eip].v1;
    if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL)
    {
        char *name = (char *)registers[r1].address;
        size_t len = strlen(name);
        size_t cap = len + 35;
        char *newName = (char *)malloc(cap);
        if (newName != NULL)
        {
            newName[0] = '\0';  // ensure the buffer starts as an empty string for safe "strcat" operations
            strcat(newName, RAW_ADDRESS);
            strcat(newName, name);
            strcat(newName, ".txt");

            which_ram = (!OS);
            loader(newName);
            free(newName);
            pr_eip = 0;
        }
    }
    os_eip++;
}

//--------| CLER |--------//
void clear_screen(int eip){
    (void)eip;
    if (which_ram == OS){
        os_eip++ ;
    }
    else{
        pr_eip++ ;
    }
    system("cls") ;
}
//--------| REST |--------//
void rest(int eip){
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    int timeout = 0;
    if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL)
    {
        timeout = *(int *)registers[r1].address;
    }
    if (which_ram == OS)
    {
        os_eip++;
    }
    else
    {
        pr_eip++;
    }
    Sleep(timeout);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CTCT color(R/G/B/Y/0)			// change terminal color to R->red , G->green ,  B->blue , Y->yellow , 0->reset		be carefull if you don't reset , it will not reset atumaticly !!!!!

//--------| CTCT |--------//
void change_terminal_color_to( int eip ){
    char color = (which_ram == OS) ? (char)os_ram[eip].v1 : (char)pr_ram[eip].v1;
    switch (color) {
    case 'R':
        RED
        break; 
    case 'G':
        GREEN
        break;
    case 'B':
        BLUE
        break;
    case 'Y':
        YELLOW
        break;
    default:
        RESET
        break;
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Created By MmdX 21:04
// Edited  By Plutroin 


