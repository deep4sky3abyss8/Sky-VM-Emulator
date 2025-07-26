/*
TIME Pn					// save current time & data in string reg[Pn] . exp : reg[R1] = "2025/1/11 21:45:56"

OPEN R1 R2 R3 			// opening file from path which saved in reg[R1] in method which in reg[R2] and point to it by File* from R3 . reg[R3] = fopen( reg[R1] , reg[R2] );

READ R1 				// read and print file from File* in reg[R1]

WRIT R1 R2				// write a line str* from reg[R1] to File* reg[R2]

APND R1 R2				// append a line str* from reg[R1] to File* reg[R2]

CLER 					// clear screen : system("cls")

MAKE R1					// make a file by name str* reg[R1]

KILL R1					// delete a file by name str* reg[R1]

RUN R1					// open & boot & load & run program which reg[r1] poit to : example in our prj :	char * reg[R1]="prg.txt"; loader(reg[R1]); which_ram = !OS;
*/