#include <iostream>

#include "Board.h"
#include "Vector2.h"

Board::Board(const int x, const int y) : m_dimensions(static_cast<float>(x), static_cast<float>(y))
{
    InitialiseGrid();
}

Board::Board(const Vector2 dimensions) : m_dimensions(dimensions)
{
    InitialiseGrid();
}

void Board::PrintBoard() const
{
    for (const auto& row : m_grid)
    {
        for (const auto& square : row)
        {
            using enum CellState;
            switch (square)
            {
            case EMPTY:
                std::cout << " ";
                break;
            case CIRCLE:
                std::cout << "O";
                break;
            case CROSS:
                std::cout << "X";
                break;
            }

            [[likely]] if (&square != &row.back())
                std::cout << "|";
        }

        if (&row != &m_grid.back()) [[likely]]
            std::cout << "\n-+-+-\n";
        else
            std::cout << "\n\n";
    }
}

Vector2 Board::GetDimensions() const
{
    return m_dimensions;
}

bool Board::IsInBounds(const Vector2& coords) const
{
    return Vector2{0,0} <= coords && coords < m_dimensions;
}

bool Board::IsSpaceTaken(const Vector2& coords) const
{
    return m_grid[coords.y][coords.x] != CellState::EMPTY;
}

void Board::InitialiseGrid()
{
    m_grid.resize(m_dimensions.y, std::vector<CellState>(m_dimensions.x));
}
