#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <string>

#include "Board.h"
#include "Vector2.h"

class Game
{
public:
    Game();

    void Run();

private:
    static void ClearScreen();
    static void MoveCursorUp(int lines);
    static void ClearLine();

    bool IsCoordsInRange(const Vector2& coords) const;
    static bool ExtractCoordsFromString(const std::string& text, Vector2& out);
    Vector2 GetValidCoordsFromUser(const int player) const;

private:
    Board m_board;
};
