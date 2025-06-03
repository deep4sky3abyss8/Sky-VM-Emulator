#include <stdio.h>
#include "machine_lan.h" // commands msut check here so here will include , no need otherplace .
#include "memory_struct.h" // include for global memory arrays .



//-------| CHECK |--------//

int command_cmp( int line , const char *pointer ){
	for(int index=0 ; index<4 ; index++){
		if(OS_Ram[line].command[index] != *(pointer+index)){
			return 0 ;
		}
	}
	return 1 ;
}// useed to checking every line commands . -> use in main src , as if condition , befor func call for comand .



//--------| ASSN |--------//

void assigne( int lineNumber /* -> index of loop move troght Rams array*/ ){
	int variable_hex_address = OS_Ram[lineNumber][4]; // -> no need to define this variable, but for reading simpifying.
	int value = OS_Ram[lineNumber][5] ;
	Var_Mem[variable_hex_address] = value ;
}


//--------| ASSV |--------//


//--------| COMP |--------//


//--------| EQAL |--------//

