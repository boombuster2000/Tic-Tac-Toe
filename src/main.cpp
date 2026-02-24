#include <iostream>

#include "Board.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

void ClearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD homeCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE) return;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hConsole, homeCoords);
#else
    std::fputs("\033[2J\033[H", stdout);
    std::fflush(stdout);
#endif
}

int main()
{
    Board board({3, 3});

    ClearScreen();
    board.PrintBoard();
}
