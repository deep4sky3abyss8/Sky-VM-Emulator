#ifndef READFUNCS_H
#define READFUNCS_H

int read_str(char *result, char delim);
unsigned long long str_len(const char str[]);
int str_cmp(const char str1[] , const char str2[] );
void str_cpy(char dest[], const char source[]);
void str_cat(char dest[], const char source[]);
int str_str( const char str[] , const char substr[] );

#endif //READFUNCS_H

// Created by SkyAbyss on 6/6/2025.

