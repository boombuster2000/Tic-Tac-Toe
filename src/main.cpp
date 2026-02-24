#include <iostream>
#include <string>
#include <regex>

#include "Board.h"
#include "GameTypes.h"

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

bool ExtractCoordsFromString(const std::string& text, Vector2& out)
{
    std::regex coordsPattern(R"(([0-9]+),([0-9]+))");
    std::smatch matches;

    if (!std::regex_match(text, matches, coordsPattern))
        return false;

    out.x = std::stoi(matches[1]);
    out.y = std::stoi(matches[2]);
    return true;
}

Vector2 GetCoordFromUser(int player)
{
    std::cout << "[P" << player << "] Enter coord (x,y): ";
    std::string userMove;

    while (true)
    {
        std::cin >> userMove;
        Vector2 coords;
        if (ExtractCoordsFromString(userMove, coords))
            return coords;

        // Escape Code Meanings
        // "\033[1A" - move cursor up 1 line
        // "\033[2K" - erase the entire current line
        std::cout << "\033[1A\033[2K";
        std::cout << "[P" << player << "] Invalid input. Enter coord (x,y): ";
    }
}


int main()
{
    Board board({3, 3});

    ClearScreen();
    board.PrintBoard();

    Vector2 coords = GetCoordFromUser(1);

}
