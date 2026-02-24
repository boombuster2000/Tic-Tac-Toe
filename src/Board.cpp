#include <iostream>

#include "Board.h"

Board::Board(Vector2 dimensions) : m_dimensions(dimensions)
{
    m_grid.resize(dimensions.y, std::vector<Square>(dimensions.x));
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
            std::cout << "\n";
    }
}
