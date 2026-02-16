/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.cpp                                                         */
/*  Purpose:    Source file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/16                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Pathfinding.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include <deque>
#include <queue>
#include <utility>
#include <vector>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Pathfinding::Pathfinding()
:   inProgress(false),
    currentAlgorithm(0),
    cellsThisFrame(0),
    deltaTimeAccumulator(0.0f),
    cellDeque(),
    cellQueue(),
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
    case 0:
    case 1:
        floodFill(gridVec, conf::gridCellsX, conf::gridCellsY, start);
        break;
    case 2:
        bfsPath(gridVec, conf::gridCellsX, conf::gridCellsY, start, goal);
    default:
        break;
    }
}

void Pathfinding::floodFill(std::vector<Cell>& gridVec, int w, int h, int start)
{
    // Push start cell if needed
    if (!inProgress)
    {
        cellDeque.clear();
        cellDeque.push_back(start);
        inProgress = true;
    }

    // Only proceed if enough delta time has passed
    if (!deltaThresholdReached())
        return;

    int processed = 0;

    while (!cellDeque.empty() && processed < cellsThisFrame)
    {
        int current;

        // Select DFS or BFS
        if (currentAlgorithm == 0)
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

        Cell::Type cellType = gridVec[current].getType();

        // Skip walls / already visited / goal, exclude start from changing state
        switch (cellType)
        {
            case Cell::Type::WALL:
            case Cell::Type::VISITED:
            case Cell::Type::GOAL:
            case Cell::Type::PATH:
                continue;

            case Cell::Type::EMPTY:
            case Cell::Type::QUEUED:
                gridVec[current].setType(Cell::Type::VISITED);
                break;

            case Cell::Type::START:
                break;
        }

        int x = current % w;
        int y = current / w;

        // Helper lambda to push neighbors
        auto tryPush = [&](int nx, int ny)
        {
            if (nx < 0 || nx >= w || ny < 0 || ny >= h)
                return;

            int neighbour = ny * w + nx;

            // Only push if empty
            if (gridVec[neighbour].getType() == Cell::Type::EMPTY)
            {
                gridVec[neighbour].setType(Cell::Type::QUEUED);
                cellDeque.push_back(neighbour);
            }
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

void Pathfinding::bfsPath(std::vector<Cell>& gridVec, int w, int h, int start, int goal)
{
    // Initialize once (same as floodFill)
    if (!inProgress)
    {
        cellDeque.clear();

        dist.assign(w * h, conf::inf);
        parent.assign(w * h, -1);

        dist[start] = 0;

        cellDeque.push_back(start);
        inProgress = true;
    }

    if (!deltaThresholdReached())
        return;

    int processed = 0;
    bool goalFound = false;

    while (!cellDeque.empty() && processed < cellsThisFrame)
    {
        int current = cellDeque.front();   // BFS → always front
        cellDeque.pop_front();

        Cell::Type type = gridVec[current].getType();

        // Skip walls or already visited
        if (type == Cell::Type::WALL ||
            type == Cell::Type::VISITED ||
            type == Cell::Type::PATH)
        {
            continue;
        }

        if (current != start && current != goal)
            gridVec[current].setType(Cell::Type::VISITED);

        if (current == goal)
        {
            goalFound = true;
            break;
        }

        int x = current % w;
        int y = current / w;

        auto tryPush = [&](int nx, int ny)
        {
            if (nx < 0 || nx >= w || ny < 0 || ny >= h)
                return;

            int neighbor = ny * w + nx;

            if (gridVec[neighbor].getType() == Cell::Type::WALL)
                return;

            if (dist[neighbor] == conf::inf)
            {
                dist[neighbor] = dist[current] + 1;
                parent[neighbor] = current;

                if (gridVec[neighbor].getType() != Cell::Type::GOAL)
                    gridVec[neighbor].setType(Cell::Type::QUEUED);
                cellDeque.push_back(neighbor);
            }
        };

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

    // If unreachable
    if (dist[goal] == conf::inf)
        return;

    // Reconstruct path
    int at = goal;
    while (at != -1)
    {
        if (gridVec[at].getType() != Cell::Type::START &&
            gridVec[at].getType() != Cell::Type::GOAL)
        {
            gridVec[at].setType(Cell::Type::PATH);
        }

        at = parent[at];
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
