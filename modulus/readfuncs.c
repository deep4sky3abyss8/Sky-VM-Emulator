#include "stdio.h"
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
//-----------------------f1----------------------------------------------
int read_int(void){
	// function main variabels
	int digit, num=0 , digit_seen=_n_seen , num_is_negetive=0 ;
	if(_something_in_cache_){
		digit=cache ;
		_something_in_cache_= 0 ;
		if(digit<'9' && digit>'0'){
			num = num*10 + (digit-'0') ;
			digit_seen = _seen ;
		}
	}
	while((digit=getchar())!=EOF){
		if( (digit>'9' || digit<'0') && !digit_seen){
			if(digit=='-'){
				num_is_negetive = _NEGETIVE_ ;
			}
			continue ;
		}
		else if((digit>'9' || digit<'0') && digit_seen){
			break ;
		}
		else{
			num = num*10 + (digit-'0') ;
			digit_seen = _seen ;
		}
	}
	if(digit!=EOF){
		cache = digit ;
		_something_in_cache_= 1 ;
	}
	if(num_is_negetive){
		return (num*-1);
	}
	return num ;
}
//----------------------f2-----------------------------------------------
//-----------------------------------------------------------------------
//-------------------------f3-----------------------------------------
//--------------------------------------------------------------------
//-------------------------f4----------------------------------------
//-------------------------------------------------------------------
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
//---------------------------------------------------------------------
// Created by SkyAbyss on 6/6/2025.

