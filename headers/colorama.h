// colorama_cross.c

#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include <windows.h>
enum COLORS {
    BLACK = 0,
    RED = 4,
    GREEN = 2,
    YELLOW = 6,
    BLUE = 1,
    MAGENTA = 5,
    CYAN = 3,
    WHITE = 7,
    RESET = 7
};
static void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
#define RED set_color(RED);
#define GREEN set_color(GREEN);
#define YELLOW set_color(YELLOW);
#define RESET set_color(RESET);
#define BLUE set_color(BLUE);
//--------------------------------------------------------------------
//--------------------------------------------------------------------
/*

Exp :

RED
Printf("hello world!");
RESET

*/
#endif //COLOR_H
//-------------------------------------------------------------------
