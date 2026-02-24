#pragma once

#include <vector>

#include "GameTypes.h"

class Board
{
public:
    Board(int x, int y);
    Board(Vector2 dimensions);

    void PrintBoard() const;
    Vector2 GetDimensions() const;

    private:
    void InitialiseGrid();
private:
    Vector2 m_dimensions;
    std::vector<std::vector<Square>> m_grid{};
};
