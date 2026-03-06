#pragma once

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

    static bool ExtractCoordsFromString(const std::string& text, Vector2& out);
    Vector2 GetValidCoordsFromUser(int player) const;

private:
    Board m_board;
};
