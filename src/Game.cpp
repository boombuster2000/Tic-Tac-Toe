#include "Game.h"

#include <iostream>
#include <regex>


Game::Game() : m_board{3,3}
{
}

bool Game::ExtractCoordsFromString(const std::string& text, Vector2& out)
{
    std::regex coordsPattern(R"(([0-9]+),([0-9]+))");
    std::smatch matches;

    if (!std::regex_match(text, matches, coordsPattern))
        return false;

    out.x = std::stoi(matches[1]);
    out.y = std::stoi(matches[2]);
    return true;
}

Vector2 Game::GetCoordsFromUser(const int player)
{
    std::cout << "[P" << player << "] Enter coord (x,y): ";
    std::string userMove;

    while (true)
    {
        std::cin >> userMove;
        Vector2 coords;

        if (!ExtractCoordsFromString(userMove, coords))
        {
            MoveCursorUp(1);
            ClearLine();

            std::cout << "[P" << player << "] Invalid input. Enter coord (x,y): ";
            continue;
        }
    }
}

void Game::Run()
{
    m_board.PrintBoard();
    Vector2 coords = GetCoordsFromUser(1);
}

void Game::ClearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD homeCoords = {0, 0};

    if (hConsole == INVALID_HANDLE_VALUE)
        return;

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

void Game::MoveCursorUp(int lines)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD pos = {0, short(csbi.dwCursorPosition.Y - lines)};
    SetConsoleCursorPosition(hConsole, pos);
#else
    std::cout << "\033[" << lines << "A";
#endif
}

void Game::ClearLine()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD pos = {0, csbi.dwCursorPosition.Y};
    DWORD written;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, pos, &written);
    SetConsoleCursorPosition(hConsole, pos);
#else
    std::cout << "\033[2K";
#endif
}
