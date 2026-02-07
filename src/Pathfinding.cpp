/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.cpp                                                         */
/*  Purpose:    Source file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/07                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Pathfinding.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include <queue>
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

bool Pathfinding::isInProgress() const
{
    return inProgress;
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Pathfinding::execute(int S2Key, int startIndex, std::vector<Cell>& gridVec)
{
    // Check if start cell is actually set
    if (startIndex == -1)
        return;

    if (!inProgress)
        currentAlgorithm = S2Key - 1;

    switch (currentAlgorithm)
    {
    case 0:
        DFSFFill(gridVec, conf::gridCellsX, conf::gridCellsY, startIndex);
        break;
    case 1:
        BFSFfill(gridVec, conf::gridCellsX, conf::gridCellsY, startIndex);
        break;
    default:
        break;
    }
}

void Pathfinding::DFSFFill(std::vector<Cell>& grid, int w, int h, int startIndex)
{
    // Push start cell onto stack
    if (!inProgress && cellStack.empty())
    {
        int startX = startIndex % conf::gridCellsX;
        int startY = startIndex / conf::gridCellsX;
        cellStack.push({startX, startY});
        inProgress = true;
    }

    // Proceed only when delta time reaches a threshold
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

        // Skip wall, visited and finish cells
        Cell::Type type = grid[index].getType();
        if (type != Cell::Type::START && type != Cell::Type::EMPTY)
            continue;

        // Mark as visited
        if (type == Cell::Type::EMPTY)
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

void Pathfinding::BFSFfill(std::vector<Cell>& grid, int w, int h, int startIndex)
{
    // Push start cell onto stack
    if (!inProgress && cellQueue.empty())
    {
        int startX = startIndex % conf::gridCellsX;
        int startY = startIndex / conf::gridCellsX;
        cellQueue.push({startX, startY});
        inProgress = true;
    }

    // Proceed only when delta time reaches a threshold
    if (!deltaThresholdReached())
        return;

    int processed = 0;

    while (!cellQueue.empty() && processed < cellsThisFrame)
    {
        auto [x, y] = cellQueue.front();
        cellQueue.pop();

        // Check bounds
        if (x < 0 || x >= w || y < 0 || y >= h)
            continue;

        int index = y * w + x;

        // Skip wall, visited and finish cells
        Cell::Type type = grid[index].getType();
        if (type != Cell::Type::START && type != Cell::Type::EMPTY)
            continue;

        // Mark as visited
        if (type == Cell::Type::EMPTY)
            grid[index].setType(Cell::Type::VISITED);

        // Push neighbors onto stack
        cellQueue.push({x + 1, y});
        cellQueue.push({x - 1, y});
        cellQueue.push({x, y + 1});
        cellQueue.push({x, y - 1});

        processed++;
    }

    if (cellQueue.empty())
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
