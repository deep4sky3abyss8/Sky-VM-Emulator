#include <stdio.h>
#include "../headers/readfuncs.h"

//==============================================================================================//#
//-----------------------f1-f4-----------------------------------------
//--------------------------------------------------------------------
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
//-----------------------f5--------------------------------------------
//---------------------------------------------------------------------
unsigned long long str_len(const char str[]){
	if (!str) return 0;
	unsigned long long len;
	for (len = 0; str[len] != '\0'; len++);
	return len;
}
//-----------------------f6--------------------------------------------
//---------------------------------------------------------------------
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
//-----------------------f7--------------------------------------------
//---------------------------------------------------------------------
void str_cpy(char dest[], const char source[]){
	if (!dest || !source) return;
	int index = 0;
	while (source[index] != '\0') {
		dest[index] = source[index];
		index++;
	}
	dest[index] = '\0';
}
//-----------------------f8--------------------------------------------
//---------------------------------------------------------------------
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
//-----------------------f9--------------------------------------------
//---------------------------------------------------------------------
void str_cat(char dest[], const char source[]){
	if (!dest || !source) return;
	unsigned long long dest_len = str_len(dest);
	int index;
	for (index = 0; source[index] != '\0'; index++) {
		dest[dest_len + index] = source[index];
	}
	dest[dest_len + index] = '\0';
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// Created by SkyAbyss on 6/6/2025.


