/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.hpp                                                         */
/*  Purpose:    Header file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/20                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Cell.hpp"
#include <deque>
#include <queue>
#include <utility>
#include <vector>


class Pathfinding
{
    public:
        enum class Algo
        {
            DFS_FF,
            BFS_FF,
            BFS_PF,
            A_STAR
        };

        // Constructors & Destructors
        Pathfinding();
        Pathfinding(const Pathfinding& other) = delete;
        Pathfinding& operator=(const Pathfinding& other) = delete;
        ~Pathfinding() = default;

        // Getters & Setters
        bool isInProgress() const;

        // Member Functions
        void exec(std::vector<Cell>& gridVec, int S2Key, int start, int goal);
        void floodFind(std::vector<Cell>& gridVec, int w, int h, int start, int goal);
        void aStar(std::vector<Cell>& gridVec, int w, int h, int start, int goal);
        bool deltaThresholdReached();

    private:
        bool inProgress;
        bool goalFound;
        int currentAlgorithm;
        int cellsThisFrame;
        float deltaTimeAccumulator;
        std::deque<int> cellDeque;
        std::vector<int> gScore;
        std::vector<int> parent;

        using Node = std::pair<int, int>; // (fScore, index)
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> cellPQueue;
};

#endif
