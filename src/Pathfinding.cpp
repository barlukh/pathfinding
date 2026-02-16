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
        bfsPathfind(gridVec, conf::gridCellsX, conf::gridCellsY, start, goal);
    default:
        break;
    }
}

void Pathfinding::floodFill(std::vector<Cell>& grid, int w, int h, int start)
{
    // Push start cell if needed
    if (!inProgress && cellDeque.empty())
    {
        int startX = start % conf::gridCellsX;
        int startY = start / conf::gridCellsX;
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

        // Skip walls / already visited / goal, exclude start from changing state
        switch (cellType)
        {
            case Cell::Type::WALL:
            case Cell::Type::VISITED:
            case Cell::Type::GOAL:
                continue;

            case Cell::Type::EMPTY:
            case Cell::Type::QUEUED:
                grid[index].setType(Cell::Type::VISITED);
                break;

            case Cell::Type::START:
                break;
        }

        // Helper lambda to push neighbors
        auto tryPush = [&](int nx, int ny)
        {
            if (nx < 0 || nx >= w || ny < 0 || ny >= h)
                return;

            int nIndex = ny * w + nx;
            Cell::Type nType = grid[nIndex].getType();

            // Only push if empty
            if (nType == Cell::Type::EMPTY)
            {
                grid[nIndex].setType(Cell::Type::QUEUED);
                cellDeque.push_back({nx, ny});
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

void Pathfinding::bfsPathfind(std::vector<Cell>& gridVec, int w, int h, int start, int goal)
{
    if (!inProgress)
    {
        dist.assign(w * h, conf::inf);
        parent.assign(w * h, -1);
        inProgress = true;
        dist[start] = 0;
        cellQueue.push(start);
    }


    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    if (!deltaThresholdReached())
        return;

    int processed = 0;

    while (!cellQueue.empty() && processed < cellsThisFrame)
    {
        int current = cellQueue.front();
        cellQueue.pop();

        if (current == goal)
            break;

        int r = current / w;
        int c = current % w;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nc >= 0 && nr < h && nc < w) {

                int neighbor = nr * w + nc;

                // Optional: skip blocked cells
                if (gridVec[neighbor].getType() == Cell::Type::WALL)
                    continue;

                if (dist[neighbor] == conf::inf) {
                    dist[neighbor] = dist[current] + 1;
                    parent[neighbor] = current;
                    cellQueue.push(neighbor);
                    gridVec[neighbor].setType(Cell::Type::QUEUED);
                }
            }
        }
    
        processed++;
    }

    if (cellQueue.empty())
        inProgress = false;
    else
        return;

    // If unreachable
    if (dist[goal] == conf::inf) {
        // std::cout << "No path found.\n";
        return;
    }

    // Reconstruct path
    std::vector<int> path;
    for (int at = goal; at != -1; at = parent[at]) {
        path.push_back(at);
    }

    // std::reverse(path.begin(), path.end());

    // Print path
    for (int idx : path)
        gridVec[idx].setType(Cell::Type::VISITED);
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
