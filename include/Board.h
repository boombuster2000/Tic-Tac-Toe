#pragma once

#include <vector>

#include "GameTypes.h"
#include "Vector2.h"

class Board
{
public:
    Board(int x, int y);
    explicit Board(Vector2 dimensions);

    void PrintBoard() const;
    [[nodiscard]] Vector2 GetDimensions() const;

    [[nodiscard]] bool IsInBounds(const Vector2& coords) const;

private:
    void InitialiseGrid();

private:
    Vector2 m_dimensions;
    std::vector<std::vector<Square>> m_grid{};
};
