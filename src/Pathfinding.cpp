/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.cpp                                                         */
/*  Purpose:    Source file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/17                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Pathfinding.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include <deque>
#include <vector>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Pathfinding::Pathfinding()
:   inProgress(false),
    goalFound(false),
    currentAlgorithm(0),
    cellsThisFrame(0),
    deltaTimeAccumulator(0.0f),
    cellDeque(),
    dist(),
    parent()
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

void Pathfinding::exec(std::vector<Cell>& gridVec, int S2Key, int start, int goal)
{
    // Check if start cell is actually set
    if (start == -1)
        return;

    if (!inProgress)
        currentAlgorithm = S2Key - 1;

    switch (currentAlgorithm)
    {
        case static_cast<int>(Algo::DFS_FF):
        case static_cast<int>(Algo::BFS_FF):
        case static_cast<int>(Algo::BFS_PF):
            floodFind(gridVec, conf::gridCellsX, conf::gridCellsY, start, goal);
        default:
            break;
    }
}

void Pathfinding::floodFind(std::vector<Cell>& gridVec, int w, int h, int start, int goal)
{
    // Push start cell if needed, initialize dist and parent vectors
    if (!inProgress)
    {
        if (currentAlgorithm == static_cast<int>(Algo::BFS_PF))
        {
            dist.assign(w * h, conf::inf);
            parent.assign(w * h, -1);
            dist[start] = 0;
        }

        cellDeque.clear();
        cellDeque.push_back(start);
        inProgress = true;
        goalFound = false;
    }

    // Only proceed if enough delta time has passed
    if (!deltaThresholdReached())
        return;

    int processed = 0;

    while (!cellDeque.empty() && processed < cellsThisFrame)
    {
        int current;

        // Select DFS or BFS
        if (currentAlgorithm == static_cast<int>(Algo::DFS_FF))
        {
            // DFS → take from back
            current = cellDeque.back();
            cellDeque.pop_back();
        }
        else
        {
            // BFS → take from front
            current = cellDeque.front();
            cellDeque.pop_front();
        }

        Cell::Type t = gridVec[current].getType();

        // React only to queued and goal cells
        if (t == Cell::Type::QUEUED)
            gridVec[current].setType(Cell::Type::VISITED);
        else if (t == Cell::Type::GOAL)
        {
            if (currentAlgorithm == static_cast<int>(Algo::BFS_PF))
                goalFound = true;
            else
                continue;
        }

        int x = current % w;
        int y = current / w;

        // Helper lambda to push neighbors
        auto tryPush = [&](int nx, int ny)
        {
            if (nx < 0 || nx >= w || ny < 0 || ny >= h)
                return;

            int neighbour = ny * w + nx;

            Cell::Type t = gridVec[neighbour].getType();

            // Push only empty and goal cells
            if (t == Cell::Type::EMPTY || t == Cell::Type::GOAL)
            {
                if (t == Cell::Type::EMPTY)
                    gridVec[neighbour].setType(Cell::Type::QUEUED);

                cellDeque.push_back(neighbour);
            }
            else
                return;

            // Add information to dist and parent vectors when using BFS pathfinding
            if (currentAlgorithm == static_cast<int>(Algo::BFS_PF))
            {
                if (gridVec[neighbour].getType() == Cell::Type::WALL)
                    return;

                if (dist[neighbour] == conf::inf)
                {
                    dist[neighbour] = dist[current] + 1;
                    parent[neighbour] = current;
                }
            }
        };

        // Push 4 neighbors
        tryPush(x + 1, y);
        tryPush(x - 1, y);
        tryPush(x, y + 1);
        tryPush(x, y - 1);

        processed++;
    }

    // If still processing next frame
    if (!goalFound && !cellDeque.empty())
        return;

    // Finished searching
    inProgress = false;

    if (currentAlgorithm == static_cast<int>(Algo::BFS_PF))
    {
        // If unreachable
        if (dist[goal] == conf::inf)
            return;
    
        // Reconstruct path
        int at = goal;
        while (at != -1)
        {
            Cell::Type t = gridVec[at].getType();
            if (t != Cell::Type::START && t != Cell::Type::GOAL)
                gridVec[at].setType(Cell::Type::PATH);
    
            at = parent[at];
        }
    }
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
