
#ifndef LOADER_H
#define LOADER_H
static int read_int(int *num , int index ,char * line);
static int skip_space(int index , char * line);
static int load(char * line , int index );
int loader( const char* address );
void printbydilay(char str[] , int firstdilay , int secenddilay );
void wellcome(void);
void Shutdownsky(void);
#endif //LOADER_H

// Created by SkyAbyss on 6/6/2025.