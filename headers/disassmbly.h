#ifndef DISASSMBLY_H
#define DISASSMBLY_H

int command_cmp( int line , const char *pointer );
void assigne_num( int eip );
void move_to_reg ( int eip);
void assign_var ( int eip);
void compare ( int eip);
void equal(int eip);
void not_equal(int eip);
void con_jump(int eip);
void jump(int eip);
int halt (int eip );
char put_char(int eip );
char * put_str(int eip );
int put_int(int eip );
int add_ints(int eip);
void plus_one(int eip);
int mult_ints(int eip);
int div_ints(int eip) ;
char get_char(int eip);
char * get_str(int eip);
int get_int (int eip);
void and (int eip);
void or (int eip);
void not(int eip);

#endif DISASSMBLY_H
// Created by SkyAbyss on 6/6/2025.
