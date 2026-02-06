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
#include <vector>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Pathfinding::Pathfinding()
:   inProgress(false),
    currentAlgorithm(0),
    cellsThisFrame(0),
    deltaTimeAccumulator(0.0f)
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

bool Pathfinding::getInProgress() const
{
    return inProgress;
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Pathfinding::execute(int S2Key, int startIndex, std::vector<Cell>& gridVec)
{
    if (!inProgress)
        currentAlgorithm = S2Key - 1;

    switch (currentAlgorithm)
    {
    case 0:
        floodFill(gridVec, conf::gridCellsX, conf::gridCellsY, startIndex);
        break;
    default:
        break;
    }
}

void Pathfinding::floodFill(std::vector<Cell>& grid, int w, int h, int startIndex)
{
    if (!inProgress && cellStack.empty())
    {
        int startX = startIndex % conf::gridCellsX;
        int startY = startIndex / conf::gridCellsX;
        cellStack.push({startX, startY});
        inProgress = true;
    }

    if (!deltaThresholdReached())
        return;

    int processed = 0;

    while (!cellStack.empty() && processed < cellsThisFrame)
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

        processed++;
    }

    if (cellStack.empty())
        inProgress = false;
}

bool Pathfinding::deltaThresholdReached()
{
    deltaTimeAccumulator += GetFrameTime() * conf::cellsPerSecond;
    cellsThisFrame = (int)deltaTimeAccumulator;
    if (cellsThisFrame == 0)
        return false;

    deltaTimeAccumulator -= cellsThisFrame;
    return true;
}
