/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.cpp                                                         */
/*  Purpose:    Source file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/19                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Pathfinding.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include <algorithm>
#include <deque>
#include <queue>
#include <utility>
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
    steps(),
    parent(),
    cellPQueue()
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
            break;
        case static_cast<int>(Algo::A_STAR):
            aStar(gridVec, conf::gridCellsX, conf::gridCellsY, start, goal);
            break;
        default:
            break;
    }
}

void Pathfinding::floodFind(std::vector<Cell>& gridVec, int w, int h, int start, int goal)
{
    // Initialize vectors and push start cell
    if (!inProgress)
    {
        if (currentAlgorithm == static_cast<int>(Algo::BFS_PF))
        {
            steps.assign(w * h, conf::inf);
            parent.assign(w * h, -1);
            steps[start] = 0;
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
            {
                goalFound = true;
                break;
            }
            else
                continue;
        }

        int x = current % w;
        int y = current / w;

        // Helper lambda to push neighbours
        auto tryPush = [&](int nx, int ny)
        {
            if (nx < 0 || nx >= w || ny < 0 || ny >= h)
                return;

            int neighbour = ny * w + nx;

            Cell::Type t = gridVec[neighbour].getType();

            // Process only empty and goal cells
            if (t != Cell::Type::EMPTY && t != Cell::Type::GOAL)
                return;

            // Handle the push to the queue and mark the information about the path
            if (currentAlgorithm == static_cast<int>(Algo::BFS_PF))
            {
                if (steps[neighbour] == conf::inf)
                {
                    steps[neighbour] = steps[current] + 1;
                    parent[neighbour] = current;

                    if (t == Cell::Type::EMPTY)
                        gridVec[neighbour].setType(Cell::Type::QUEUED);

                    cellDeque.push_back(neighbour);
                }
            }
            else
            {
                if (t == Cell::Type::EMPTY)
                    gridVec[neighbour].setType(Cell::Type::QUEUED);

                cellDeque.push_back(neighbour);
            }
        };

        // Push 4 neighbours
        tryPush(x + 1, y);
        tryPush(x - 1, y);
        tryPush(x, y + 1);
        tryPush(x, y - 1);

        // Push also diagonal neigbours (warning: this allows diagonal wall skip)
        // tryPush(x + 1, y + 1);
        // tryPush(x - 1, y + 1);
        // tryPush(x + 1, y - 1);
        // tryPush(x - 1, y - 1);

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
        if (steps[goal] == conf::inf)
            return;
    
        // Reconstruct path
        for (int at = goal; at != -1; at = parent[at])
        {
            if (at != start && at != goal)
                gridVec[at].setType(Cell::Type::PATH);
        }
    }
}

void Pathfinding::aStar(std::vector<Cell>& gridVec, int w, int h, int start, int goal)
{
    // Helper lambda to determine the heuristic value
    auto heuristic = [&](int a, int b)
    {
        int ax = a % w;
        int ay = a / w;
        int bx = b % w;
        int by = b / w;

        // Manhattan distance (for 4-direction grid)
        return std::abs(ax - bx) + std::abs(ay - by);
    };

    // Initialize vectors and push start cell
    if (!inProgress)
    {
        steps.assign(w * h, conf::inf);
        parent.assign(w * h, -1);
        steps[start] = 0;

        while (!cellPQueue.empty())
            cellPQueue.pop();
        cellPQueue.push({heuristic(start, goal), start});

        inProgress = true;
        goalFound = false;
    }

    // Only proceed if enough delta time has passed
    if (!deltaThresholdReached())
        return;

    int processed = 0;

    while (!cellPQueue.empty() && processed < cellsThisFrame)
    {
        int current = cellPQueue.top().second;
        cellPQueue.pop();

        Cell::Type t = gridVec[current].getType();

        // React only to queued and goal cells
        if (t == Cell::Type::QUEUED)
            gridVec[current].setType(Cell::Type::VISITED);
        else if (t == Cell::Type::GOAL)
        {
            goalFound = true;
            break;
        }

        int x = current % w;
        int y = current / w;

        // Helper lambda to push neighbours
        auto tryPush = [&](int nx, int ny)
        {
            if (nx < 0 || ny < 0 || nx >= w || ny >= h)
                return;

            int neighbour = ny * w + nx;

            Cell::Type t = gridVec[neighbour].getType();

            // Process only empty and goal cells
            if (t != Cell::Type::EMPTY && t != Cell::Type::GOAL)
                return;

            // Handle the push to the queue and mark the information about the path
            int tentativeG = steps[current] + 1;

            if (tentativeG < steps[neighbour])
            {
                steps[neighbour] = tentativeG;
                parent[neighbour] = current;

                int fScore = tentativeG + conf::weight * heuristic(neighbour, goal);

                if (gridVec[neighbour].getType() != Cell::Type::GOAL)
                    gridVec[neighbour].setType(Cell::Type::QUEUED);

                cellPQueue.push({ fScore, neighbour });
            }
        };

        // Push 4 neighbours
        tryPush(x + 1, y);
        tryPush(x - 1, y);
        tryPush(x, y + 1);
        tryPush(x, y - 1);

        processed++;
    }

    // If still processing next frame
    if (!goalFound && !cellPQueue.empty())
        return;

    // Finished searching
    inProgress = false;

    // If unreachable
    if (steps[goal] == conf::inf)
        return;

    // Reconstruct path
    for (int at = goal; at != -1; at = parent[at])
    {
        if (at != start && at != goal)
            gridVec[at].setType(Cell::Type::PATH);
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
