/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.cpp                                                         */
/*  Purpose:    Source file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/05                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Pathfinding.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include <stack>


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

const std::vector<int>& Pathfinding::getPathfindOrder() const
{
    return pathfindOrder;
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Pathfinding::execute(int S2Key, int startIndex, const std::vector<Cell>& gridVec)
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

void Pathfinding::floodFill(const std::vector<Cell>& grid, int w, int h, int x, int y)
{
    std::vector<Cell> visitedGrid = grid;
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
        if (visitedGrid[index].getType() == Cell::Type::OBSTACLE || visitedGrid[index].getType() == Cell::Type::VISITED)
            continue;

        // Mark as visited
        visitedGrid[index].setType(Cell::Type::VISITED);
        pathfindOrder.push_back(index);

        // Push neighbors onto stack
        cellStack.push({x + 1, y});
        cellStack.push({x - 1, y});
        cellStack.push({x, y + 1});
        cellStack.push({x, y - 1});
    }
}
