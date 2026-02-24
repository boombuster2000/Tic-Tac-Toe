#pragma once

#include <vector>

#include "Vector2.h"

class Board
{
public:
    Board(Vector2 dimensions);

    void PrintBoard() const;

private:
    Vector2 m_dimensions;
    std::vector<std::vector<int>> m_grid{};
};
