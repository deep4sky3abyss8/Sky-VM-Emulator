//
// Created by SkyAbyss on 7/15/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../headers/machine_lan.h" // commands msut check here so here will include , no need otherplace .
#include "../headers/memory_struct.h" // include for global memory arrays .
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Created by SkyAbyss on 6/6/2025.
#define _seen 1 //  < f1, f2, f3, f4
#define _n_seen 0 // < f1, f2, f3. f4
#ifndef _NEGETIVE_
#define _NEGETIVE_ 1 // < f1, f2, f3
#endif
//==============================================================================================//#
//==============================================================================================//#
static int cache ,_something_in_cache_= 0 ;														//#
//==============================================================================================//#
//==============================================================================================//#
//-----------------------f1-------------------------------------------
//----------------------f2--------------------------------------------
//--------------------------------------------------------------------
// colorama_cross.c
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
enum COLORS {
    BLACK = 0,
    RED = 4,
    GREEN = 2,
    YELLOW = 6,
    BLUE = 1,
    MAGENTA = 5,
    CYAN = 3,
    WHITE = 7,
    RESET = 7
};
void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

#endif
//-------------------------f3-----------------------------------------
//--------------------------------------------------------------------
#define RED set_color(RED);
#define GREEN set_color(GREEN);
#define YELLOW set_color(YELLOW);
#define RESET set_color(RESET);
#define BLUE set_color(BLUE);
//-------------------------f4-----------------------------------------
//--------------------------------------------------------------------
int read_str(char *result, char delim){
	int character , char_seen = _n_seen , index=0 ;
	if(_something_in_cache_){
		character = cache ;
		_something_in_cache_= 0 ;
		if(character!=delim && character!='\n'){
			result[index]=character ;
			index++ ;
			char_seen = _seen ;
		}
	}
	while((character=getchar())!='\n' && index<200 ){
		if( character==delim && !char_seen ){
			continue ;
		}
		else if(character==delim && char_seen ){
			break ;
		}
		else{
			result[index]=character ;
			index++ ;
			char_seen = _seen ;
		}
	}
	result[index] = '\0' ;
	if(character!=EOF){//------>>> I a little confused that delim can be a part of another func call?
		cache = character ;//          |__like this : stdio = 1111Hi1Ali111 => read_str(my_str , '1');
		_something_in_cache_= 1 ;
	}
	return index-1 ;
}
//--------------------- BASIC DISASSEMBLY COMMANDS ------------------------------------
void printbydilay(char str[] , int firsdilay , int secenddilay ){
	int index ;
	for(index=0 ; str[index]!='\0' ; index++ ){
		putchar(str[index]);
		Sleep(firsdilay);
	}
	Sleep(secenddilay);
}
//-------| CHECK |--------// OK
int command_cmp( int line , const char *pointer ) {

	for (int index = 0; index < 4; index++) {
		if (os_ram[line].command[index] != *(pointer + index)) {
			return 0;
		}
	}
	printf("\t* [%d]\tRun\t< %s >\n",line+1,pointer);
	return 1;
} // useed to checking every line commands . -> use in main src , as if condition , befor func call for comand .
//--------| ASSN |--------// OK
void assigne_num( int eip ){
	if(which_ram == OS){
		int reg_index = os_ram[eip].v1 ,
		value = os_ram[eip].v2 ;
		switch (registers[reg_index].type) {
			case 'I':
				*((int * )registers[reg_index].address)= value ;
				break;
			default:
				*((char * )registers[reg_index].address)= (char)value ;
				break;
		}
		os_eip++ ;
	}
	else{
		int reg_index = pr_ram[eip].v1 ,
		value = pr_ram[eip].v2 ;
		switch (registers[reg_index].type) {
			case 'I':
				*((int * )registers[reg_index].address)= value ;
				break;
			default:
				*((char * )registers[reg_index].address)= (char)value ;
				break;
		}
		pr_eip++ ;
	}
}
//--------| MOVE |--------// OK
void move_to_reg ( int eip) {
	if(which_ram == OS) {
		int index = os_ram[eip].v1 ;
		int target =  os_ram[eip].v2 ;
		switch (os_ram[eip].v3) {
			case 'I':
				registers[index].address = &(heap.ints[target]) ;
				break;
			case 'C':
				registers[index].address = &(heap.chrs[target]) ;
				break;
			case 'S' :
				registers[index].address = &(heap.strs[target]) ;
				break;
		}
		registers[index].type = os_ram[eip].v3 ;
		os_eip++ ;
	}
	else {
		int index = pr_ram[eip].v1 ;
		int target =  pr_ram[eip].v2 ;
		switch (pr_ram[eip].v3) {
			case 'I':
				registers[index].address = &(heap.ints[target]) ;
				break;
			case 'C':
				registers[index].address = &(heap.chrs[target]) ;
				break;
			case 'S' :
				registers[index].address = &(heap.strs[target]) ;
				break;
		}
		registers[index].type = pr_ram[eip].v3 ;
		pr_eip++ ;
	}
}
//--------| ASSV |--------// OK
void assign_var ( int eip) {
	if(which_ram == OS) {
		int des = os_ram[eip].v1 ;
		int src =  os_ram[eip].v2 ;
		switch (registers[src].type) {
			case 'I':
				*((int *)registers[des].address) = * ((int *)registers[src].address) ;
				break;
			default:
				*((char*)registers[des].address) = * ((char*)registers[src].address) ;
				break;
		}
		registers[des].type = registers[src].type ;
		os_eip++ ;
	}
	else {
		int des = pr_ram[eip].v1 ;
		int src =  pr_ram[eip].v2 ;
		switch (registers[src].type) {
			case 'I':
				*((int *)registers[des].address) = * ((int *)registers[src].address) ;
				break;
			default:
				*((char*)registers[des].address) = * ((char*)registers[src].address) ;
				break;
		}
		registers[des].type = registers[src].type ;
		pr_eip++ ;
	}
}
//--------| COMP |--------//
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

void compare ( int eip) {
	if(which_ram == OS) {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		registers[res].type = 'I' ;
		if (registers[src].type == registers[des].type) {
			switch (registers[src].type) {
				case 'I':
					if (*((int *)registers[des].address) > *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((char *)registers[des].address) > *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		else {
			*(int*)registers[res].address = 0 ;
		}
		os_eip++ ;
	}
	else {
		int src = pr_ram[eip].v1 ,
			des = pr_ram[eip].v2 ,
			res = pr_ram[eip].v3 ;
		registers[res].type = 'I' ;
		if (registers[src].type == registers[des].type) {
			switch (registers[src].type) {
				case 'I':
					if (*((int *)registers[des].address) > *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((char *)registers[des].address) > *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		else {
			*(int*)registers[res].address = 0 ;
		}
		pr_eip++ ;
	}
}
//--------| EQAL |--------//
void equal(int eip) {
	if(which_ram == OS) {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		registers[res].type = 'I' ;
		if (registers[src].type == registers[des].type) {
			switch (registers[src].type) {
				case 'I':
					if (*((int *)registers[des].address) == *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((char *)registers[des].address) == *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		else {
			switch (registers[src].type) {
				case 'I':
					if (*((char *)registers[des].address) == *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					//printf("----> It's reach <-----\n");
					break;
				default:
					if (*((int *)registers[des].address) == *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		os_eip++ ;
	}
	else {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		registers[res].type = 'I' ;
		if (registers[src].type == registers[des].type) {
			switch (registers[src].type) {
				case 'I':
					if (*((int *)registers[des].address) == *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((char *)registers[des].address) == *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		else {
			switch (registers[src].type) {
				case 'I':
					if (*((char *)registers[des].address) == *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((int *)registers[des].address) == *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		pr_eip++ ;
	}
}
//--------| NEQL |--------//
void not_equal(int eip) {
	if(which_ram == OS) {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		registers[res].type = 'I' ;
		if (registers[src].type == registers[des].type) {
			switch (registers[src].type) {
				case 'I':
					if (*((int *)registers[des].address) != *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((char *)registers[des].address) != *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		else {
			switch (registers[src].type) {
				case 'I':
					if (*((char *)registers[des].address) != *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((int *)registers[des].address) != *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		os_eip++ ;
	}
	else {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		registers[res].type = 'I' ;
		if (registers[src].type == registers[des].type) {
			switch (registers[src].type) {
				case 'I':
					if (*((int *)registers[des].address) != *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((char *)registers[des].address) != *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		else {
			switch (registers[src].type) {
				case 'I':
					if (*((char *)registers[des].address) != *((int *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
				default:
					if (*((int *)registers[des].address) != *((char *)registers[src].address))
						*(int*)registers[res].address = 1 ;
					else
						*(int*)registers[res].address = 0 ;
					break;
			}
		}
		pr_eip++ ;
	}
}
//--------| CJMP |--------//
void con_jump(int eip) {
	if(which_ram == OS) {
		int reg = os_ram[eip].v1 ,
			line = os_ram[eip].v2 ;
		if ( *(int*)registers[reg].address) {
			printf("\n\nJump to line [ %d ]\n\n",line);
			os_eip = line-1 ;
			return;
		}
		os_eip++ ;
	}
	else {
		int reg = pr_ram[eip].v1 ,
			line = pr_ram[eip].v2 ;
		if ( *(int*)registers[reg].address) {
			printf("\n\nJump to line [ %d ]\n\n",line);
			pr_eip = line-1 ;
			return ;
		}
		pr_eip++ ;
	}
}
//--------| JUMP |--------//
int jump (int eip) {
	if(which_ram == OS) {
		int line = os_ram[eip].v1 ;
		printf("\n\nJump to line [ %d ]\n\n",line);
			os_eip = line-1 ;
			return line ;
	}
	int line = pr_ram[eip].v1 ;
	printf("\n\nJump to line [ %d ]\n\n",line);
		pr_eip = line-1 ;
		return line ;
}
//--------| HALT |--------//
int halt (int eip ){   // --> if in future we allocate any memory , here we must free them all .
	if(which_ram == OS) {
		printf("------------------------------------\n");
		return 1 ;
	}
	printf("++++++++++++++++++++++++++++++++++++\n");
	which_ram = OS ;
	pr_eip = 0 ; // program is finish so we reset every thing to start a new program .
	os_eip++ ;
	printbydilay("|\tGetting back to terminal !\n|\tIhope see you soon !" , 70 , 1000 );
	return 0 ;
}
//--------| PUTC |--------//
char put_char(int eip ) {
	if(which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char c = *((char*)registers[reg].address) ;
		os_eip++ ;
		YELLOW
		printf("\n\noutput : %c\n\n",c);
		RESET
		return c ;
	}
	int reg = pr_ram[eip].v1 ;
	char c = *((char*)registers[reg].address) ;
	pr_eip++ ;
	YELLOW
	printf("\n\noutput : %c\n\n",c);
	RESET
	return c ;
}
//--------| PUTS |--------//
char * put_str(int eip ) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
            r2 = os_ram[eip].v2 ;
        switch(registers[r1].type){
            case 'I':
		    perror("[!] invalid register type for register point to string\n");
		printf ("[!] line %d %s %d %d\n",eip,os_ram[eip].command,r1,r2);
                return NULL ;
            default :
                break;
        }
        switch(registers[r2].type){
            case 'I':
                break;
            default :
                perror("[!] invalid register type for register point to integer\n");
		printf ("[!] line %d %s %d %d\n",eip,os_ram[eip].command,r1,r2);
                return NULL ;
        }
        int len = *((int*)registers[r2].address);
		char * str = (char*)registers[r1].address ;
		YELLOW
		printf("\n\noutput : %c\n\n",*(str+len));
		RESET
		os_eip++ ;
		return str ;
	}
	int r1 = pr_ram[eip].v1 ,
        r2 = pr_ram[eip].v2 ;
    switch(registers[r1].type){
        case 'I':
		perror("[!] invalid register type for register point to string\n");
		printf ("[!] line %d %s %d %d\n",eip,pr_ram[eip].command,r1,r2);
                return NULL ;
        default :
            break;
    }
    switch(registers[r2].type){
        case 'I':
            break;
        default :
            perror("[!] invalid register type for register point to integer\n" );
		printf ("[!] line %d %s %d %d\n",eip,pr_ram[eip].command,r1,r2);
            return NULL ;
    }
    int len = *((int*)registers[r2].address);
    char * str = (char*)registers[r1].address ;
	YELLOW
	printf("\n\noutput : %c\n\n",*(str+len));
	RESET
    pr_eip++ ;
	return str ;
}
//--------| PUTI |--------//
int put_int(int eip ) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ,
			d = *((int *)registers[reg].address) ;
		os_eip++ ;
		YELLOW
		printf("\n\noutput : %d\n\n", d );
		RESET
		return d ;
	}
	int reg = pr_ram[eip].v1 ,
		d = *((int *)registers[reg].address) ;
	pr_eip++ ;
	YELLOW
	printf("\n\noutput : %d\n\n", d );
	RESET
	return d ;
}
//--------| ADDN |--------//
int add_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
		*(int *)registers[res].address = a+b ;
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
		*(int *)registers[res].address = a+b ;
		pr_eip++ ;
		return res ;
	}
}
//--------| ADDO |--------//
void plus_one(int eip) {
	if (which_ram == OS) {
		int r = os_ram[eip].v1 ,
			a = *(int *)registers[r].address ;
		a++ ;
		*(int *)registers[r].address = a ;
		os_eip++ ;
		return;
	}
	int r = pr_ram[eip].v1 ,
		a = *(int *)registers[r].address ;
	a++ ;
	*(int *)registers[r].address = a ;
	pr_eip++ ;
}
//--------| MULT |--------//
int mult_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
		*(int *)registers[res].address = a*b ;
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
		*(int *)registers[res].address = a*b ;
		pr_eip++ ;
		return res ;
	}
}
//--------| DIVI |--------//
int div_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
		*(int *)registers[res].address = a/b ;
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
		*(int *)registers[res].address = a/b ;
		pr_eip++ ;
		return res ;
	}
}
//--------| MODE |--------//
int mode_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
			//printf("\n-------------------------\n");
			//Sleep(3000) ;
		*(int *)registers[res].address = a%b ;
		//printf("\n-------------------------\n");
		//	Sleep(3000) ;
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ,
			a= *(int *)registers[r1].address ,
			b= *(int *)registers[r2].address ;
		*(int *)registers[res].address = a%b ;
		pr_eip++ ;
		return res ;
	}
}
//--------| GETC |--------//
char get_char(int eip) {
	GREEN
	printf("\n\ninput : ");
	RESET
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char character = getchar() ;
		*(char *)registers[reg].address = character ;
		os_eip++ ;
		printf("\n\n");
		return character ;
	}
	else {
		int reg = pr_ram[eip].v1 ;
		char character = getchar() ;
		*(char *)registers[reg].address = character ;
		pr_eip++ ;
		printf("\n\n");
		return character ;
	}
}
//--------| GETI |--------//
int get_int(int eip) {
	GREEN
	printf("\n\ninput : ");
	RESET
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ,
			num = getchar()-'0';
		*(char *)registers[reg].address = num ;
		os_eip++ ;
		printf("\n\n");
		return num ;
	}
	else {
		int reg = pr_ram[eip].v1 ,
			num = getchar()-'0' ;
		*(char *)registers[reg].address = num ;
		pr_eip++ ;
		printf("\n\n");
		return num ;
	}
} // it take only one digit from stdin .
//--------| GETS |--------//  befor using this func user must call MOVE and move his register on strs heap segment .
int get_str(int eip) {
	GREEN
	printf("\n\ninput : ");
	RESET
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			reg = os_ram[eip].v2 ,
			count =0 ;
		char * str = (char *)registers[r1].address ;
		count = read_str(str , ' ') ;
		*(int *) registers[reg].address = count ;
		os_eip++ ;
		printf("\n\n");
		return count ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			reg = pr_ram[eip].v2 ,
			count =0 ;
		char * str = (char *)registers[r1].address ;
		count = read_str(str , ' ') ;
		*(int *) registers[reg].address = count ;
		pr_eip++ ;
		printf("\n\n");
		return count ;
	}
}
//--------| ANDC |--------//
void and (int eip){
	if (which_ram==OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			r3 = os_ram[eip].v3 ;
		*(int *)registers[r3].address = *(int *)registers[r2].address && *(int *)registers[r1].address ;
        os_eip++ ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			r3 = pr_ram[eip].v3 ;
		*(int *)registers[r3].address = *(int *)registers[r2].address && *(int *)registers[r1].address ;
        pr_eip++ ;
	}
}
//--------| ORLC |--------//
void or (int eip){
	if (which_ram==OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			r3 = os_ram[eip].v3 ;
		*(int *)registers[r3].address = *(int *)registers[r2].address || *(int *)registers[r1].address ;
        os_eip++ ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			r3 = pr_ram[eip].v3 ;
		*(int *)registers[r3].address = *(int *)registers[r2].address || *(int *)registers[r1].address ;
        pr_eip++ ;
	}
}
//--------| NOTC |--------//
void not(int eip){
	if (which_ram==OS) {
		int r1 = os_ram[eip].v1 ,
			tmp ;
		tmp = *(int *)registers[r1].address ;
		*(int *)registers[r1].address = !tmp ;
        os_eip++ ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			tmp ;
		tmp = *(int *)registers[r1].address ;
		*(int *)registers[r1].address = !tmp ;
        pr_eip++ ;
	}
}
//------------------------- WINDOWS API COMMANDS ------------------------------
/*
MKFL name.type // make file.type

MKDR name // make directory by name

SPCE // get me space for app running. make index of App's RAM zero .

OPNF name.type // open file.type

REDF name.type // read file.type and save it by protocol into App's RAM

RUNF name.type // run file.type , from App's RAM index
*/
/*
int main() {
	puts("l");
	return 0 ;
}*/

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
   if (line[index] == '\n' || line[index] == '\0'){
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
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        char *buffer;
        size_t bufsize = 50 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        while( fgets( buffer, bufsize, file ) ) {
            if (*buffer<'A' || *buffer>'Z') {
                continue;
            }
            else {
                if (load( buffer , index ))
                    index++ ;
            }
        }
        if(index==0) {
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        free(buffer);
    }
    else {
        if (file==NULL) {
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            return 1 ;
        }
        char *buffer;
        size_t bufsize = 50 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            free(buffer);
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            os_eip++ ;
            return 2 ;
        }
        while( fgets( buffer, bufsize, file) ){
            if (*buffer<'A' || *buffer>'Z') {
                continue;
            }
            else {
                if (load( buffer , index ))
                    index++ ;
            }
        }
        if(index==0) {
            free(buffer);
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
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

//--------------------------------------------------------------------------------------------------------
void wellcome(void){
    //fprintf(stderr,"Sky machine : preparing to boot ...\n\n");
    printbydilay("\nSky machine : preparing to boot ...\n\n" , 30 , 300);
    printbydilay("loading ",80,0);
    printf(" ____________________________________________\rloading ");
    Sleep(500);
    printbydilay("#############################################",90,0);
    printf("\r                                                     \r");
    printf("----------------------------------------------------------\n");
}
//--------------------------------------------------------------------------------------------------------

//-----------------------f5--------------------------------------------
//---------------------------------------------------------------------
unsigned long long str_len(char str[]){
	unsigned long long len ;
	for(len=0 ; str[len]!='\0'; len++);
	return len ;
}
//-----------------------f6--------------------------------------------
//---------------------------------------------------------------------
int str_cmp(char str1[] , char str2[] ){
	unsigned long long len1=0 , len2=0 ;
	if((len1=str_len(str1))>(len2=str_len(str2))){
		return 1 ;
	}else if(len1<len2){
		return -1 ;
	}else{
		for(int index=0 ; index<len2 ; index++){
			if(str1[index]>str2[index]){
				return 1 ;
			}else if(str1[index]<str2[index]){
				return -1 ;
			}
		}
	}
	return 0 ;
}
//-----------------------f7--------------------------------------------
//---------------------------------------------------------------------
// > absolute didi not talk about len , i copy source to des only to its last char and '\0' .
void str_cpy(char dest[], char source[]){
    int index=0 , token ;
    unsigned long long dest_len = str_len(dest) ;
    for(index ; (token=source[index])!='\0' && index < dest_len-1 ; index++){
        dest[index]=token ;
    }
    dest[index]='\0' ;
}
//-----------------------f8--------------------------------------------
//---------------------------------------------------------------------
// > absolute did not talk about len , so i check it before sub finding .
int str_str( char str[] , char substr[] ){
	unsigned long long strr_len=str_len(str) , substr_len=str_len(substr);
	if(strr_len<substr_len){
		return -1 ;
	}
	int out_loop_index , _found_= 0 ;
	for(out_loop_index=0 ; out_loop_index <= (strr_len - substr_len) ; out_loop_index++ ){
		_found_= 1 ;
		for( int in_loop_index=0 ; in_loop_index < substr_len ; in_loop_index++ ){
			if( substr[in_loop_index] != str[out_loop_index + in_loop_index]){
				_found_=0 ;
				break ;
			}
		}
		if(_found_){
			return out_loop_index ;
		}
	}
	return -1 ;
}
//-----------------------f9--------------------------------------------
//---------------------------------------------------------------------
// > because did not talk about dest &  source array len , i asume that it have enough space for cating .
void str_cat(char dest[], char source[]){
    int index, token ;
    unsigned long long dest_len = str_len(dest) ;
    for(index=0 ; (token=source[index])!='\0' ; index++){
    	dest[dest_len+index] = token ;
    }
    dest[dest_len + index] = '\0' ;
}
//---------------------------------------------------------------------
//--------------------------------------------------------//
//--------| TIME |--------//

//--------| OPEN |--------//

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
//---------------------------------------------------------------------
// Created by SkyAbyss on 6/6/2025.

//--------------------------------------------  define   -------------------
#define BOOT_ADDRESS "../DisassemblyPograms/prg.txt"
//--------------------------------------------  external var src   -----------------
int stck_mem[100] , // short for stack memory segment .
	os_eip=0 ,  // -> eip registers which tell us which line of program/os we are in .
	pr_eip=0 ,
	which_ram= OS ;
//--------------------------------------------  main src   -----------------
int main(void) {
	char a[]="111111111" , 
	trash[]="trash" ;
	while(a) {
		loader(BOOT_ADDRESS);
	
		os_eip=0 ;
		int *eip ;
		printf("----------------booted------------------\n");
		while (1) {
			if (which_ram==OS) {
				eip = &os_eip;
			}
			else {
				eip = &pr_eip ;
			}
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
			/*====================================

			else if (command_cmp(*eip , _TIME_ ))*/

			else if (command_cmp(*eip , _OPEN_ ))
				openFile(* eip) ;
			/*
			else if (command_cmp(*eip , _READ_ ))

			else if (command_cmp(*eip , _WRIT_ ))

			else if (command_cmp(*eip , _CLOS_ ))

			else if (command_cmp(*eip , _APND_ ))

			else if (command_cmp(*eip , _MAKE_ ))

			else if (command_cmp(*eip , _KILL_ ))

			else if (command_cmp(*eip , _RUNF_ ))

			*/

			else if (command_cmp(*eip , _CLER_ )){
				clear_screen(*eip);
			}
			else if (command_cmp(*eip , _CTCT_ )){
				change_terminal_color_to(*eip);
			}
			//====================================
			else {
				if (which_ram==OS) {
					fprintf(stderr, "[!]\tFatal Error : Invalid disassembly command : %s\n",os_ram[os_eip].command);
					exit(1);
				}
				else {
					fprintf(stderr, "[!]\tFatal Error : Invalid disassembly command : %s\n",pr_ram[pr_eip].command);
					exit(2);
				}
			}
		}
		// shut down box ->
		Sleep(200);
		//printf("shutdown ");
		RED
		printf("\nPress\n[ 0 ] To quit\n[ 1 ] To RERUN\n\n[!] Enter code : ");
		RESET
		scanf("%s",&a);
		gets(trash) ;
		//scanf("%d",&a);
		//printf("%c",a[0]);
		if( a[0]=='0' || a[1]=='0' || a[2]=='0' ){
			break;
		}
	}
	printf("-------------------------------------");

	return 0;

}


