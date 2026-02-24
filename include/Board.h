#pragma once

#include <vector>

#include "GameTypes.h"

class Board
{
public:
    Board(Vector2 dimensions);

    void PrintBoard() const;

private:
    Vector2 m_dimensions;
    std::vector<std::vector<Square>> m_grid{};
};
