#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../headers/machine_lan.h" // commands msut check here so here will include , no need otherplace .
#include "../headers/memory_struct.h" // include for global memory arrays .
#include "../headers/loader.h" // for halt command .
#include "../headers/readfuncs.h" // for read int and read str funcs since now
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------- BASIC DISASSEMBLY COMMANDS ------------------------------------
//-------| CHECK |--------// OK
int command_cmp( int line , const char *pointer ) {
	for (int index = 0; index < 4; index++) {
		if (os_ram[line].command[index] != *(pointer + index)) {
			return 0;
		}
	}
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
			os_eip = line ;
			return;
		}
		os_eip++ ;
	}
	else {
		int reg = pr_ram[eip].v1 ,
			line = pr_ram[eip].v2 ;
		if ( *(int*)registers[reg].address) {
			pr_eip = line ;
			return ;
		}
		pr_eip++ ;
	}
}
//--------| JUMP |--------//
int jump (int eip) {
	if(which_ram == OS) {
		int line = os_ram[eip].v1 ;
			os_eip = line ;
			return line ;
	}
	int line = pr_ram[eip].v1 ;
		pr_eip = line ;
		return line ;
}
//--------| HALT |--------//
int halt (int eip ){   // --> if in future we allocate any memory , here we must free them all .
	if(which_ram == OS) {
		system("cls");
		printbydilay("|\tWe are going to shutdown ...\n|\tSmile please !\n" , 70 , 2000 );
		printbydilay("|\tevery day every time ...\n|\tSmile please !\n" , 70 , 2000 );
		printbydilay("|\twe will see you soon ...\n|\tSmile please !\n" , 70 , 2000 );
		system("cls");
		Sleep(500);
		exit(0);
	}
	which_ram = OS ;
	pr_eip = 0 ; // program is finish so we reset every thing to start a new program .
	os_eip++ ;
	printbydilay("|\tGetting back to terminal !\n|\tIhope see you soon !" , 70 , 1000 );
	return 0 ;
}
//--------| PUTC |--------//
char put_char(int eip ) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char c = *((char*)registers[reg].address) ;
		os_eip++ ;
		putchar(c);
		return c ;
	}
	int reg = pr_ram[eip].v1 ;
	char c = *((char*)registers[reg].address) ;
	pr_eip++ ;
	putchar(c);
	return c ;
}
//--------| PUTS |--------//
char * put_str(int eip ) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char * c = (char*)registers[reg].address ,
			 * srast = c ;
		while (*c) {
			putchar(*c);
			c++ ;
		}
		putchar('\n');
		os_eip++ ;
		return srast ;
	}
	int reg = pr_ram[eip].v1 ;
	char * c = (char*)registers[reg].address ,
		 * srast = c ;
	while (*c) {
		putchar(*c);
		c++ ;
	}
	putchar('\n');
	os_eip++ ;
	return srast ;
}
//--------| PUTI |--------//
int put_int(int eip ) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ,
			d = *((int *)registers[reg].address) ;
		os_eip++ ;
		printf("%d",d);
		return d ;
	}
	int reg = pr_ram[eip].v1 ,
		d = *((int *)registers[reg].address) ;
	pr_eip++ ;
	printf("%d",d);
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
		*(int *)registers[res].address = a%b ;
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
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char character = getchar() ;
		*(char *)registers[reg].address = character ;
		os_eip++ ;
		return character ;
	}
	else {
		int reg = pr_ram[eip].v1 ;
		char character = getchar() ;
		*(char *)registers[reg].address = character ;
		pr_eip++ ;
		return character ;
	}
}
//--------| GETI |--------//
int get_int(int eip) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ,
			num = getchar()-'0';
		*(char *)registers[reg].address = num ;
		os_eip++ ;
		return num ;
	}
	else {
		int reg = pr_ram[eip].v1 ,
			num = getchar()-'0' ;
		*(char *)registers[reg].address = num ;
		pr_eip++ ;
		return num ;
	}
} // it take only one digit from stdin .
//--------| GETS |--------//  befor using this func user must call MOVE and move his register on strs heap segment .
int get_str(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			reg = os_ram[eip].v2 ,
			count =0 ;
		char * str = (char *)registers[r1].address ;
		count = read_str(str , ' ') ;
		*(int *) registers[reg].address = count ;
		os_eip++ ;
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
