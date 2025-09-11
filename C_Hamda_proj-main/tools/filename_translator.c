#include <stdio.h>

int main(){
	int name[300];
	int c,i=0,reg=0,reg2=0,REG3=0,start=0;

printf("start :" );
while((c=getchar())!='\n'){
		start = start * 10 + c - '0';
}
printf("reg :" );
while((c=getchar())!='\n'){
		reg = reg * 10 + c - '0';
}
printf("reg for type :" );
while((c=getchar())!='\n'){
		reg2 = reg2 * 10 + c - '0';
}
printf("reg for RES :" );
while((c=getchar())!='\n'){
		REG3 = REG3 * 10 + c - '0';
}
while((c=getchar())!=EOF&&c!='\n'){
	name[i]=c;i++;name[i+1] = 0;
}
	for(int j=0;j<i+1;j++)
		printf("MOVE %d %d S\nASSN %d %d\n",reg,j+start,reg,name[j]);
	printf("MOVE %d %d S\n",reg,start);
	printf("ASSN %d 114\nOPEN %d %d %d\n\nCLOS %d\n",reg2,reg,reg2,REG3,REG3);
}
