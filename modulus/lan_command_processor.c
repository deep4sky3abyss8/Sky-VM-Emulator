#include <stdio.h>
#include <stdlib.h>
#include "../headers/machine_lan.h" // commands msut check here so here will include , no need otherplace .
#include "../headers/memory_struct.h" // include for global memory arrays .
#include "../headers/typing-wellcome.h" // for halt command .
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//-------| CHECK |--------//
int command_cmp( int line , const char *pointer ) {
	for (int index = 0; index < 4; index++) {
		if (os_ram[line].command[index] != *(pointer + index)) {
			return 0;
		}
	}
	return 1;
} // useed to checking every line commands . -> use in main src , as if condition , befor func call for comand .
//--------| ASSN |--------//
void assigne_num( int lineNumber ){
	if(which_ram == OS){
		int reg_index = os_ram[lineNumber].v1 ,
		value = os_ram[lineNumber].v2 ;
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
		int reg_index = pr_ram[lineNumber].v1 ,
		value = pr_ram[lineNumebr].v2 ;
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
//--------| MOVE |--------//
void move_to_reg ( int eip) {
	if(which_ram == OS) {
		int index = os_ram[eip].v1 ;
		int target =  os_ram[eip].v2 ;
		registers[index].address = &(heap.ints[target]) ;
		registers[index].type = os_ram[eip].v3 ;
		os_eip++ ;
	}
	else {
		int index = pr_ram[eip].v1 ;
		int target =  pr_ram[eip].v2 ;
		registers[index].address = &(heap.ints[target]) ;
		registers[index].type = pr_ram[eip].v3 ;
		pr_eip++ ;
	}
}
//--------| ASSV |--------//
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
		printf("\e[H\e[J");
		printbydilay("|\tWe are going to shutdown ...\n|\tSmile please !" , 70 , 2000 );
		exit(0);
	}
	which_ram = OS ;
	pr_eip = 0 ; // program is finish so we reset every thing to start a new program .
	os_eip++ ;
	printbydilay("|\tGetting back to terminal !\n|\tIhope see you soon !" , 70 , 1000 );
	return 0 ;
}
//--------| PUTC |--------//
char print_char(int eip ) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char c = *((char*)registers[reg].address) ;
		putchar(c);
		return c ;
	}
	int reg = pr_ram[eip].v1 ;
	char c = *((char*)registers[reg].address) ;
	putchar(c);
	return c ;
}
//--------| PUTC |--------//