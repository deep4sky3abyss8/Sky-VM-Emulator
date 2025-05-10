#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef  MAX
#define MAX 100
#endif

void read_from_file(const char *filename ){
	FILE *file = fopen(filename , "r") ;
	char word[MAX] ;
	while ( fscanf(file,"%s" , word ) != EOF ){
		printf("%s\n",word );
	}
	fclose(file) ;
}

int main(void) {
	const char *filename="s.txt" ;
	filename = "ali.txt" ;
	read_from_file(filename) ;
scanf("%d",&filename);
putchar(a);

}