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
#include <deque>
#include <utility>
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
        floodFill(gridVec, conf::gridCellsX, conf::gridCellsY, startIndex);
        break;
    case 1:
        floodFill(gridVec, conf::gridCellsX, conf::gridCellsY, startIndex);
        break;
    default:
        break;
    }
}

void Pathfinding::floodFill(std::vector<Cell>& grid, int w, int h, int startIndex)
{
    // Push start cell if needed
    if (!inProgress && cellDeque.empty())
    {
        int startX = startIndex % conf::gridCellsX;
        int startY = startIndex / conf::gridCellsX;
        cellDeque.push_back({startX, startY});
        inProgress = true;
    }

    // Only proceed if enough delta time has passed
    if (!deltaThresholdReached())
        return;

    int processed = 0;

    while (!cellDeque.empty() && processed < cellsThisFrame)
    {
        std::pair<int,int> cell;

        // Select DFS or BFS
        if (currentAlgorithm == 0)
        {
            // DFS → take from back
            cell = cellDeque.back();
            cellDeque.pop_back();
        }
        else
        {
            // BFS → take from front
            cell = cellDeque.front();
            cellDeque.pop_front();
        }

        auto [x, y] = cell;

        int index = y * w + x;
        Cell::Type cellType = grid[index].getType();

        // Skip walls / already visited / finish
        if (cellType != Cell::Type::START && cellType != Cell::Type::EMPTY)
            continue;

        // Mark current cell as visited
        if (cellType == Cell::Type::EMPTY)
            grid[index].setType(Cell::Type::VISITED);

        // Helper lambda to push neighbors
        auto tryPush = [&](int nx, int ny)
        {
            if (nx < 0 || nx >= w || ny < 0 || ny >= h)
                return;

            int nIndex = ny * w + nx;
            Cell::Type nType = grid[nIndex].getType();

            // Only push if empty or start
            if (nType == Cell::Type::EMPTY)
                cellDeque.push_back({nx, ny});
        };

        // Push 4 neighbors
        tryPush(x + 1, y);
        tryPush(x - 1, y);
        tryPush(x, y + 1);
        tryPush(x, y - 1);

        processed++;
    }

    // Done when deque is empty
    if (cellDeque.empty())
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
