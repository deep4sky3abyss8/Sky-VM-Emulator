#include <stdio.h>
#include "../headers/machine_lan.h" // commands msut check here so here will include , no need otherplace .
#include "../headers/memory_struct.h" // include for global memory arrays .


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

void assigne( int lineNumber ){
	if(which_ram == OS){
		int reg_index = os_ram[lineNumber].v1 ,
		value = PR_Ram[lineNumber].v2 ;
		reg[reg_index]= value ;
		return ;
	}
	else{
		int reg_index = PR_Ram[lineNumber].v1 ,
		value = PR_Ram[lineNumebr].v2 ;
		reg[reg_index]= value ;
		return ;
	}
}
//--------| MOVE |--------//


//--------| ASSV |--------//


//--------| COMP |--------//


//--------| EQAL |--------//
/*
int main(){
puts("ali");
return 0 ;
}
*/