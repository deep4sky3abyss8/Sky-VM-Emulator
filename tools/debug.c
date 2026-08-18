//
// Created by SkyAbyss on 7/15/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>
#include "../headers/machine_lan.h"
#include "../headers/memory_struct.h"
#include "../headers/colorama.h"

#define RAW_ADDRESS "../DisassemblyPograms/"
#define BOOT_ADDRESS "../DisassemblyPograms/prg.txt"

//--------------------------------------------  external var src   -----------------
struct ram os_ram[10000];
struct ram pr_ram[10000];
struct heap_s heap;
struct regs registers[30];
int stck_mem[100];
int os_eip = 0;
int pr_eip = 0;
int which_ram = OS;

//--------------------------------------------------------------------
//----------------------- String & I/O Helper Functions --------------
//--------------------------------------------------------------------
unsigned long long str_len(const char str[]){
	if (!str) return 0;
	unsigned long long len;
	for (len = 0; str[len] != '\0'; len++);
	return len;
}

int str_cmp(const char str1[], const char str2[]){
	if (!str1 && !str2) return 0;
	if (!str1) return -1;
	if (!str2) return 1;
	unsigned long long len1 = str_len(str1), len2 = str_len(str2);
	if (len1 > len2) {
		return 1;
	} else if (len1 < len2) {
		return -1;
	} else {
		for (unsigned long long index = 0; index < len2; index++) {
			if ((unsigned char)str1[index] > (unsigned char)str2[index]) {
				return 1;
			} else if ((unsigned char)str1[index] < (unsigned char)str2[index]) {
				return -1;
			}
		}
	}
	return 0;
}

void str_cpy(char dest[], const char source[]){
	if (!dest || !source) return;
	int index = 0;
	while (source[index] != '\0') {
		dest[index] = source[index];
		index++;
	}
	dest[index] = '\0';
}

int str_str(const char str[], const char substr[]){
	if (!str || !substr) return -1;
	unsigned long long strr_len = str_len(str), substr_len = str_len(substr);
	if (strr_len < substr_len) {
		return -1;
	}
	for (unsigned long long out_loop_index = 0; out_loop_index <= (strr_len - substr_len); out_loop_index++) {
		int _found_ = 1;
		for (unsigned long long in_loop_index = 0; in_loop_index < substr_len; in_loop_index++) {
			if (substr[in_loop_index] != str[out_loop_index + in_loop_index]) {
				_found_ = 0;
				break;
			}
		}
		if (_found_) {
			return (int)out_loop_index;
		}
	}
	return -1;
}

void str_cat(char dest[], const char source[]){
	if (!dest || !source) return;
	unsigned long long dest_len = str_len(dest);
	int index;
	for (index = 0; source[index] != '\0'; index++) {
		dest[dest_len + index] = source[index];
	}
	dest[dest_len + index] = '\0';
}

int read_str(char *result, char delim){
	if (!result) return 0;
	int character, index = 0;
	while ((character = getchar()) != EOF && character != '\n' && character != delim && index < 199) {
		result[index] = (char)character;
		index++;
	}
	result[index] = '\0';
	return index;
}

void printbydilay(char str[] , int firsdilay , int secenddilay ){
	int index ;
	for(index=0 ; str[index]!='\0' ; index++ ){
		putchar(str[index]);
		Sleep(firsdilay);
	}
	Sleep(secenddilay);
}

void wellcome(void){
    printbydilay("\nSky machine : preparing to boot ...\n\n" , 30 , 300);
    printbydilay("loading ",80,0);
    printf(" ____________________________________________\rloading ");
    Sleep(500);
    printbydilay("#############################################",90,0);
    printf("\r                                                     \r");
    printf("----------------------------------------------------------\n");
}

//--------------------------------------------------------------------
//--------------------- BASIC DISASSEMBLY COMMANDS -------------------
//--------------------------------------------------------------------
int command_cmp( int line , const char *pointer ) {
	if (line < 0 || line >= 10000 || !pointer) return 0;
	for (int index = 0; index < 4; index++) {
		if (which_ram == OS) {
			if (os_ram[line].command[index] != *(pointer + index)) {
				return 0;
			}
		} else {
			if (pr_ram[line].command[index] != *(pointer + index)) {
				return 0;
			}
		}
	}
	printf("\t* [%d]\tRun\t< %s >\n",line+1,pointer);
	return 1;
}

void assigne_num( int eip ){
	if(which_ram == OS){
		int reg_index = os_ram[eip].v1 ,
		value = os_ram[eip].v2 ;
		if (reg_index >= 0 && reg_index < 30 && registers[reg_index].address != NULL) {
			switch (registers[reg_index].type) {
				case 'I':
					*((int * )registers[reg_index].address)= value ;
					break;
				default:
					*((char * )registers[reg_index].address)= (char)value ;
					break;
			}
		}
		os_eip++ ;
	}
	else{
		int reg_index = pr_ram[eip].v1 ,
		value = pr_ram[eip].v2 ;
		if (reg_index >= 0 && reg_index < 30 && registers[reg_index].address != NULL) {
			switch (registers[reg_index].type) {
				case 'I':
					*((int * )registers[reg_index].address)= value ;
					break;
				default:
					*((char * )registers[reg_index].address)= (char)value ;
					break;
			}
		}
		pr_eip++ ;
	}
}

void move_to_reg ( int eip) {
	if(which_ram == OS) {
		int index = os_ram[eip].v1 ;
		int target =  os_ram[eip].v2 ;
		if (index >= 0 && index < 30) {
			switch (os_ram[eip].v3) {
				case 'I':
					if (target >= 0 && target < 100) registers[index].address = &(heap.ints[target]) ;
					else registers[index].address = NULL;
					break;
				case 'C':
					if (target >= 0 && target < 100) registers[index].address = &(heap.chrs[target]) ;
					else registers[index].address = NULL;
					break;
				case 'S' :
					if (target >= 0 && target < 1000) registers[index].address = &(heap.strs[target]) ;
					else registers[index].address = NULL;
					break;
				default:
					registers[index].address = NULL;
					break;
			}
			registers[index].type = (char)os_ram[eip].v3 ;
		}
		os_eip++ ;
	}
	else {
		int index = pr_ram[eip].v1 ;
		int target =  pr_ram[eip].v2 ;
		if (index >= 0 && index < 30) {
			switch (pr_ram[eip].v3) {
				case 'I':
					if (target >= 0 && target < 100) registers[index].address = &(heap.ints[target]) ;
					else registers[index].address = NULL;
					break;
				case 'C':
					if (target >= 0 && target < 100) registers[index].address = &(heap.chrs[target]) ;
					else registers[index].address = NULL;
					break;
				case 'S' :
					if (target >= 0 && target < 1000) registers[index].address = &(heap.strs[target]) ;
					else registers[index].address = NULL;
					break;
				default:
					registers[index].address = NULL;
					break;
			}
			registers[index].type = (char)pr_ram[eip].v3 ;
		}
		pr_eip++ ;
	}
}

void assign_var ( int eip) {
	if(which_ram == OS) {
		int des = os_ram[eip].v1 ;
		int src =  os_ram[eip].v2 ;
		if (des >= 0 && des < 30 && src >= 0 && src < 30 &&
		    registers[des].address != NULL && registers[src].address != NULL) {
			switch (registers[src].type) {
				case 'I':
					*((int *)registers[des].address) = * ((int *)registers[src].address) ;
					break;
				default:
					*((char*)registers[des].address) = * ((char*)registers[src].address) ;
					break;
			}
			registers[des].type = registers[src].type ;
		}
		os_eip++ ;
	}
	else {
		int des = pr_ram[eip].v1 ;
		int src =  pr_ram[eip].v2 ;
		if (des >= 0 && des < 30 && src >= 0 && src < 30 &&
		    registers[des].address != NULL && registers[src].address != NULL) {
			switch (registers[src].type) {
				case 'I':
					*((int *)registers[des].address) = * ((int *)registers[src].address) ;
					break;
				default:
					*((char*)registers[des].address) = * ((char*)registers[src].address) ;
					break;
			}
			registers[des].type = registers[src].type ;
		}
		pr_eip++ ;
	}
}

void compare ( int eip) {
	if(which_ram == OS) {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		if (src >= 0 && src < 30 && des >= 0 && des < 30 && res >= 0 && res < 30 &&
		    registers[src].address != NULL && registers[des].address != NULL && registers[res].address != NULL) {
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
		}
		os_eip++ ;
	}
	else {
		int src = pr_ram[eip].v1 ,
			des = pr_ram[eip].v2 ,
			res = pr_ram[eip].v3 ;
		if (src >= 0 && src < 30 && des >= 0 && des < 30 && res >= 0 && res < 30 &&
		    registers[src].address != NULL && registers[des].address != NULL && registers[res].address != NULL) {
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
		}
		pr_eip++ ;
	}
}

void equal(int eip) {
	if(which_ram == OS) {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		if (src >= 0 && src < 30 && des >= 0 && des < 30 && res >= 0 && res < 30 &&
		    registers[src].address != NULL && registers[des].address != NULL && registers[res].address != NULL) {
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
		}
		os_eip++ ;
	}
	else {
		int src = pr_ram[eip].v1 ,
			des = pr_ram[eip].v2 ,
			res = pr_ram[eip].v3 ;
		if (src >= 0 && src < 30 && des >= 0 && des < 30 && res >= 0 && res < 30 &&
		    registers[src].address != NULL && registers[des].address != NULL && registers[res].address != NULL) {
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
		}
		pr_eip++ ;
	}
}

void not_equal(int eip) {
	if(which_ram == OS) {
		int src = os_ram[eip].v1 ,
			des = os_ram[eip].v2 ,
			res = os_ram[eip].v3 ;
		if (src >= 0 && src < 30 && des >= 0 && des < 30 && res >= 0 && res < 30 &&
		    registers[src].address != NULL && registers[des].address != NULL && registers[res].address != NULL) {
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
		}
		os_eip++ ;
	}
	else {
		int src = pr_ram[eip].v1 ,
			des = pr_ram[eip].v2 ,
			res = pr_ram[eip].v3 ;
		if (src >= 0 && src < 30 && des >= 0 && des < 30 && res >= 0 && res < 30 &&
		    registers[src].address != NULL && registers[des].address != NULL && registers[res].address != NULL) {
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
		}
		pr_eip++ ;
	}
}

void con_jump(int eip) {
	if(which_ram == OS) {
		int reg = os_ram[eip].v1 ,
			line = os_ram[eip].v2 ;
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL && *(int*)registers[reg].address) {
			if (line >= 1 && line <= 10000) {
				os_eip = line-1 ;
				return;
			}
		}
		os_eip++ ;
	}
	else {
		int reg = pr_ram[eip].v1 ,
			line = pr_ram[eip].v2 ;
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL && *(int*)registers[reg].address) {
			if (line >= 1 && line <= 10000) {
				pr_eip = line-1 ;
				return ;
			}
		}
		pr_eip++ ;
	}
}

int jump (int eip) {
	if(which_ram == OS) {
		int line = os_ram[eip].v1 ;
		if (line >= 1 && line <= 10000) {
			os_eip = line-1 ;
		} else {
			os_eip++ ;
		}
		return line ;
	}
	int line = pr_ram[eip].v1 ;
	if (line >= 1 && line <= 10000) {
		pr_eip = line-1 ;
	} else {
		pr_eip++ ;
	}
	return line ;
}

int halt (int eip ){
	(void)eip;
	if(which_ram == OS) {
		return 1 ;
	}
	which_ram = OS ;
	pr_eip = 0 ;
	return 0 ;
}

char put_char(int eip ) {
	if(which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char c = '\0';
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
			c = *((char*)registers[reg].address) ;
			putchar(c);
		}
		os_eip++ ;
		return c ;
	}
	int reg = pr_ram[eip].v1 ;
	char c = '\0';
	if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
		c = *((char*)registers[reg].address) ;
		putchar(c);
	}
	pr_eip++ ;
	return c ;
}

char * put_str(int eip ) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
            r2 = os_ram[eip].v2 ;
		if (r1 < 0 || r1 >= 30 || r2 < 0 || r2 >= 30 || !registers[r1].address || !registers[r2].address) {
			os_eip++;
			return NULL;
		}
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
        putchar(*(str+len));
		os_eip++ ;
		return str ;
	}
	int r1 = pr_ram[eip].v1 ,
        r2 = pr_ram[eip].v2 ;
	if (r1 < 0 || r1 >= 30 || r2 < 0 || r2 >= 30 || !registers[r1].address || !registers[r2].address) {
		pr_eip++;
		return NULL;
	}
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
    putchar(*(str+len));
    pr_eip++ ;
	return str ;
}

int put_int(int eip ) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		int d = 0;
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
			d = *((int *)registers[reg].address) ;
			printf("%d ",d);
		}
		os_eip++ ;
		return d ;
	}
	int reg = pr_ram[eip].v1 ;
	int d = 0;
	if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
		d = *((int *)registers[reg].address) ;
		printf("%d",d);
	}
	pr_eip++ ;
	return d ;
}

char * push_str(int eip ) {
    if (which_ram == OS) {
        int r1 = os_ram[eip].v1 ,
            r2 = os_ram[eip].v2 ,
            r3 = os_ram[eip].v3 ;
		if (r1 < 0 || r1 >= 30 || r2 < 0 || r2 >= 30 || r3 < 0 || r3 >= 30 ||
		    !registers[r1].address || !registers[r2].address || !registers[r3].address) {
			os_eip++;
			return NULL;
		}
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
        *(char*)registers[r3].address = *(str+len);
        os_eip++ ;
        return str ;
    }
    int r1 = pr_ram[eip].v1 ,
        r2 = pr_ram[eip].v2 ,
        r3 = pr_ram[eip].v3 ;
	if (r1 < 0 || r1 >= 30 || r2 < 0 || r2 >= 30 || r3 < 0 || r3 >= 30 ||
	    !registers[r1].address || !registers[r2].address || !registers[r3].address) {
		pr_eip++;
		return NULL;
	}
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
    *(char*)registers[r3].address = *(str+len);
    pr_eip++ ;
    return str ;
}

void store_char (int eip ) {
    if (which_ram == OS) {
        int r1 = os_ram[eip].v1 ,
            r2 = os_ram[eip].v2 ,
            r3 = os_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && r3 >= 0 && r3 < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[r3].address != NULL) {
        	int idx = *((int*)registers[r2].address);
            char * str = (char*)registers[r1].address,
				   character = *((char*)registers[r3].address);
			*( str + idx ) = character ;
		}
		os_eip++ ;
	}
	else {
        int r1 = pr_ram[eip].v1 ,
            r2 = pr_ram[eip].v2 ,
            r3 = pr_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && r3 >= 0 && r3 < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[r3].address != NULL) {
        	int idx = *((int*)registers[r2].address);
            char * str = (char*)registers[r1].address,
				   character = *((char*)registers[r3].address);
			*( str + idx ) = character ;
		}
		pr_eip++ ;
	}
}

int add_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;
			*(int *)registers[res].address = a+b ;
		}
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;
			*(int *)registers[res].address = a+b ;
		}
		pr_eip++ ;
		return res ;
	}
}

void plus_one(int eip) {
	if (which_ram == OS) {
		int r = os_ram[eip].v1 ;
		if (r >= 0 && r < 30 && registers[r].address != NULL) {
			int a = *(int *)registers[r].address ;
			a++ ;
			*(int *)registers[r].address = a ;
		}
		os_eip++ ;
		return;
	}
	int r = pr_ram[eip].v1 ;
	if (r >= 0 && r < 30 && registers[r].address != NULL) {
		int a = *(int *)registers[r].address ;
		a++ ;
		*(int *)registers[r].address = a ;
	}
	pr_eip++ ;
}

int mult_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;
			*(int *)registers[res].address = a*b ;
		}
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;
			*(int *)registers[res].address = a*b ;
		}
		pr_eip++ ;
		return res ;
	}
}

int div_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;

			if (b == 0) {
				printf("ERR");
				*(int *)registers[res].address = 0;
			}
			else if (a == INT_MIN && b == -1) {
				*(int *)registers[res].address = INT_MAX;
			}
			else {
				*(int *)registers[res].address = a/b ;
			}
		}
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;

			if (b == 0) {
				printf("ERR");
				*(int *)registers[res].address = 0;
			}
			else if (a == INT_MIN && b == -1) {
				*(int *)registers[res].address = INT_MAX;
			}
			else {
				*(int *)registers[res].address = a/b ;
			}
		}
		pr_eip++ ;
		return res ;
	}
}

int mode_ints(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			res= os_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;

			if (b == 0) {
				printf("ERR");
				*(int *)registers[res].address = 0;
			}
			else if (a == INT_MIN && b == -1) {
				*(int *)registers[res].address = 0;
			}
			else {
				*(int *)registers[res].address = a%b ;
			}
		}
		os_eip++ ;
		return res ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			res= pr_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && res >= 0 && res < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[res].address != NULL) {
			int a = *(int *)registers[r1].address ,
				b = *(int *)registers[r2].address ;

			if (b == 0) {
				printf("ERR");
				*(int *)registers[res].address = 0;
			}
			else if (a == INT_MIN && b == -1) {
				*(int *)registers[res].address = 0;
			}
			else {
				*(int *)registers[res].address = a%b ;
			}
		}
		pr_eip++ ;
		return res ;
	}
}

char get_char(int eip) {
	GREEN
	printf("\n\ninput : ");
	RESET
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		char character = (char)getchar() ;
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
			*(char *)registers[reg].address = character ;
		}
		os_eip++ ;
		printf("\n\n");
		return character ;
	}
	else {
		int reg = pr_ram[eip].v1 ;
		char character = (char)getchar() ;
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
			*(char *)registers[reg].address = character ;
		}
		pr_eip++ ;
		printf("\n\n");
		return character ;
	}
}

int get_int(int eip) {
	if (which_ram == OS) {
		int reg = os_ram[eip].v1 ;
		int num = getchar()-'0';
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
			if (registers[reg].type == 'I') {
				*(int *)registers[reg].address = num ;
			} else {
				*(char *)registers[reg].address = (char)num ;
			}
		}
		os_eip++ ;
		return num ;
	}
	else {
		int reg = pr_ram[eip].v1 ;
		int num = getchar()-'0' ;
		if (reg >= 0 && reg < 30 && registers[reg].address != NULL) {
			if (registers[reg].type == 'I') {
				*(int *)registers[reg].address = num ;
			} else {
				*(char *)registers[reg].address = (char)num ;
			}
		}
		pr_eip++ ;
		return num ;
	}
}

int get_str(int eip) {
	if (which_ram == OS) {
		int r1 = os_ram[eip].v1 ,
			reg = os_ram[eip].v2 ,
			count = 0 ;
		if (r1 >= 0 && r1 < 30 && reg >= 0 && reg < 30 &&
		    registers[r1].address != NULL && registers[reg].address != NULL) {
			char * str = (char *)registers[r1].address ;
			count = read_str(str , ' ') ;
			*(int *) registers[reg].address = count ;
		}
		os_eip++ ;
		return count ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			reg = pr_ram[eip].v2 ,
			count = 0 ;
		if (r1 >= 0 && r1 < 30 && reg >= 0 && reg < 30 &&
		    registers[r1].address != NULL && registers[reg].address != NULL) {
			char * str = (char *)registers[r1].address ;
			count = read_str(str , ' ') ;
			*(int *) registers[reg].address = count ;
		}
		pr_eip++ ;
		return count ;
	}
}

void and (int eip){
	if (which_ram==OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			r3 = os_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && r3 >= 0 && r3 < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[r3].address != NULL) {
			*(int *)registers[r3].address = (*(int *)registers[r2].address && *(int *)registers[r1].address) ? 1 : 0 ;
		}
        os_eip++ ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			r3 = pr_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && r3 >= 0 && r3 < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[r3].address != NULL) {
			*(int *)registers[r3].address = (*(int *)registers[r2].address && *(int *)registers[r1].address) ? 1 : 0 ;
		}
        pr_eip++ ;
	}
}

void or (int eip){
	if (which_ram==OS) {
		int r1 = os_ram[eip].v1 ,
			r2 = os_ram[eip].v2 ,
			r3 = os_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && r3 >= 0 && r3 < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[r3].address != NULL) {
			*(int *)registers[r3].address = (*(int *)registers[r2].address || *(int *)registers[r1].address) ? 1 : 0 ;
		}
        os_eip++ ;
	}
	else {
		int r1 = pr_ram[eip].v1 ,
			r2 = pr_ram[eip].v2 ,
			r3 = pr_ram[eip].v3 ;
		if (r1 >= 0 && r1 < 30 && r2 >= 0 && r2 < 30 && r3 >= 0 && r3 < 30 &&
		    registers[r1].address != NULL && registers[r2].address != NULL && registers[r3].address != NULL) {
			*(int *)registers[r3].address = (*(int *)registers[r2].address || *(int *)registers[r1].address) ? 1 : 0 ;
		}
        pr_eip++ ;
	}
}

void not(int eip){
	if (which_ram==OS) {
		int r1 = os_ram[eip].v1 ;
		if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL) {
			int tmp = *(int *)registers[r1].address ;
			*(int *)registers[r1].address = (!tmp) ? 1 : 0 ;
		}
        os_eip++ ;
	}
	else {
		int r1 = pr_ram[eip].v1 ;
		if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL) {
			int tmp = *(int *)registers[r1].address ;
			*(int *)registers[r1].address = (!tmp) ? 1 : 0 ;
		}
        pr_eip++ ;
	}
}

//-------------------------------------------------------------------------------------------------------
//----------------------- Loader & Execution Engine -----------------------------------------------------
//-------------------------------------------------------------------------------------------------------
static int read_int(int *num , int index ,char * line) {
    if (!num || !line) return 0;
    *num = 0 ;
    int sign = 1 ;
    for ( ; line[index]!=' ' && line[index]!='\t' && line[index]!='\0' ; index++) {
        if (line[index] == '\n' || line[index] == '\0') {
           *num *= sign ;
           if(sign == -1 && *num == 0)
              *num = '-' ;
            return 0 ;
        }
       if(line[index]=='-'){
          sign = -1 ;
          continue;
       }
        if (line[index]<'0' || line[index]>'9') {
            *num = line[index] ;
            return 0 ;
        }
        *num = (*num)*10 + (line[index]-'0');
    }
    *num *= sign ;
    return index;
}

static int skip_space(int index , char * line) {
    if (!line) return 0;
    while(line[index]==' ' || line[index]=='\t') {
        index++ ;
    }
    if (line[index] == '#' || line[index] == '\n' || line[index] == '\0'){
        return 0 ;
    }
    return index;
}

static int load(char * line , int index ){
    if (!line || index < 0 || index >= 10000) return 0;
    if (which_ram==OS){
        os_ram[index].v1 = 0;
        os_ram[index].v2 = 0;
        os_ram[index].v3 = 0;
        int i = 0;
        for ( ; i < 4 && line[i] != '\0' && line[i] != '\n' && line[i] != ' ' && line[i] != '\t' ; i++) {
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
        pr_ram[index].v1 = 0;
        pr_ram[index].v2 = 0;
        pr_ram[index].v3 = 0;
        int i = 0;
        for ( ; i < 4 && line[i] != '\0' && line[i] != '\n' && line[i] != ' ' && line[i] != '\t' ; i++) {
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

int loader( const char* address ) {
    FILE* file = fopen( address, "r" );
    int index = 0 ;
    if ( which_ram == OS ) {
        if (file==NULL) {
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        char *buffer;
        size_t bufsize = 200 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            fclose(file);
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
        while( index < 10000 && fgets( buffer, bufsize, file ) ) {
            if ((*buffer<'A' || *buffer>'Z') && (*buffer<'a' || *buffer>'z')) {
                continue;
            }
            else {
                if (load( buffer , index ))
                    index++ ;
            }
        }
        free(buffer);
        fclose(file);
        if(index==0) {
            perror("[!][!][!]  Fatal Error : Boot Failed  [!][!][!]");
            exit(1) ;
        }
    }
    else {
        if (file==NULL) {
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            return 1 ;
        }
        char *buffer;
        size_t bufsize = 200 * sizeof(char);
        buffer = (char*) malloc( bufsize );
        if (buffer==NULL) {
            fclose(file);
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            os_eip++ ;
            return 2 ;
        }
        while( index < 10000 && fgets( buffer, bufsize, file) ){
            if ((*buffer<'A' || *buffer>'Z') && (*buffer<'a' || *buffer>'z')) {
                continue;
            }
            else {
                if (load( buffer , index ))
                    index++ ;
            }
        }
        free(buffer);
        fclose(file);
        if(index==0) {
            perror("[!][!]  Fatal Error : Loading Error  [!][!]");
            which_ram = OS ;
            os_eip++ ;
            return 3 ;
        }
    }
    return index ;
}

//--------------------------------------------------------------------
//--------------------- OS API COMMANDS ------------------------------
//--------------------------------------------------------------------
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
    }
    if (r3 >= 0 && r3 < 30)
    {
        registers[r3].address = (void *)p;
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

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

void makeFile(int eip)
{
    int r1 = (which_ram == OS) ? os_ram[eip].v1 : pr_ram[eip].v1;
    if (r1 >= 0 && r1 < 30 && registers[r1].address != NULL)
    {
        char *name = (char *)registers[r1].address;
        FILE *p = fopen(name, "w");
        if (p)
        {
            fclose(p);
        }
    }
    if (which_ram == OS) os_eip++;
    else pr_eip++;
}

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

void runProgram(int eip)
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
            newName[0] = '\0';
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

//--------------------------------------------  main src   -----------------
int main(void) {
	char a[16] = "111111111";
	while(1) {
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
			if (*eip < 0 || *eip >= 10000) {
				fprintf(stderr, "[!]\tFatal Error : EIP out of bounds <%d>\n", *eip);
				exit(3);
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
			else if (command_cmp(*eip , _TIME_ ))
				{showTime(* eip);}
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
			else if (command_cmp(*eip , _RUNF_ ))
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
		RED
		printf("\nPress\n[ 0 ] To quit\n[ 1 ] To RERUN\n\n[!] Enter code : ");
		RESET
		if (scanf("%15s", a) != 1) {
			break;
		}
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		if( a[0]=='0' || a[1]=='0' || a[2]=='0' ){
			break;
		}
	}
	printf("-------------------------------------\n");

	return 0;
}
