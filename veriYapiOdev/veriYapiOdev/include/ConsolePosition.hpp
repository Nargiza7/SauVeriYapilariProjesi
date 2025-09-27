#ifndef CONSOLEPOSITION_HPP
#define CONSOLEPOSITION_HPP

#include <windows.h>

static class ConsolePosition {
public:

    static void gotoxy(int x, int y) {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }


} ConsolePosition;


#endif 

