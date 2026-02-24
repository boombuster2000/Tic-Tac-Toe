#include <iostream>

#include "Board.h"

Board::Board(int x, int y) : m_dimensions(x,y)
{
    InitialiseGrid();
}

Board::Board(Vector2 dimensions) : m_dimensions(dimensions)
{
    InitialiseGrid();
}

void Board::PrintBoard() const
{
    for (const auto& row : m_grid)
    {
        for (const auto& square : row)
        {
            using enum Square;
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

        [[likely]] if (&row != &m_grid.back())
            std::cout << "\n-+-+-\n";
        else
            std::cout << "\n\n";
    }
}

Vector2 Board::GetDimensions() const
{
    return m_dimensions;
}

void Board::InitialiseGrid()
{
    m_grid.resize(m_dimensions.y, std::vector<Square>(m_dimensions.x));
}
