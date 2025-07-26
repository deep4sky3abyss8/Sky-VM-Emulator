// colorama_cross.c
#include <stdio.h>
#ifdef _WIN32
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
void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
// برای لینوکس یا مک
enum COLORS {
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    RESET = 0
};
void set_color(int color) {
    printf("\033[%dm", color);
}
#endif
//------------------------------------------------------------------
//--------------------------------------------------------------------
#define RED set_color(RED);
#define GREEN set_color(GREEN);
#define YELLOW set_color(YELLOW);
#define RESET set_color(RESET);
//------------------------------------------------------------------


/*

Exp :

RED
Printf("hello world!");
RESET


*/