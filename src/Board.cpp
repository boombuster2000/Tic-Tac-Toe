#include <iostream>

#include "Board.h"

Board::Board(Vector2 dimensions) : m_dimensions(dimensions)
{
    // m_grid.resize(dimensions.y);

    for (int y = 0; y < dimensions.y; y++)
    {
        std::vector<int> row;
        // m_grid[y].resize(dimensions.x);
        for (int x = 0; x < dimensions.x; x++)
            row.push_back(0);

        m_grid.push_back(row);
    }
}

void Board::PrintBoard() const
{
    for (const auto& row : m_grid)
    {
        for (const auto& square : row)
        {
            switch (square)
            {
            case 0:
                std::cout << " ";
                break;
            case 1:
                std::cout << "O";
                break;
            case -1:
                std::cout << "X";
                break;
            }

            std::cout << "|";
        }

        [[likely]] if (&row != &m_grid.back())
            std::cout << "\n-+-+-+-\n";
        else
            std::cout << "\n";
    }
}
