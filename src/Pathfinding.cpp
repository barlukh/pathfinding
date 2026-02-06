/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.cpp                                                         */
/*  Purpose:    Source file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/06                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Pathfinding.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include <stack>


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Pathfinding::execute(int S2Key, int startIndex, std::vector<Cell>& gridVec)
{
    int startX = startIndex % conf::gridCellsX;
    int startY = startIndex / conf::gridCellsX;

    switch (S2Key)
    {
    case 1:
        floodFill(gridVec, conf::gridCellsX, conf::gridCellsY, startX, startY);
        break;    
    default:
        break;
    }
}

void Pathfinding::floodFill(std::vector<Cell>& grid, int w, int h, int x, int y)
{
    std::stack<std::pair<int, int>> cellStack;
    cellStack.push({x, y});

    while (!cellStack.empty())
    {
        auto [x, y] = cellStack.top();
        cellStack.pop();

        // Check bounds
        if (x < 0 || x >= w || y < 0 || y >= h)
            continue;

        int index = y * w + x;

        // Skip if not empty or already visited
        Cell::Type type = grid[index].getType();
        if (type == Cell::Type::OBSTACLE || type == Cell::Type::VISITED)
            continue;

        // Mark as visited
        grid[index].setType(Cell::Type::VISITED);

        // Push neighbors onto stack
        cellStack.push({x + 1, y});
        cellStack.push({x - 1, y});
        cellStack.push({x, y + 1});
        cellStack.push({x, y - 1});
    }
}
