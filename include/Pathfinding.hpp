/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.hpp                                                         */
/*  Purpose:    Header file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/07                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Cell.hpp"
#include <queue>
#include <stack>
#include <vector>


class Pathfinding
{
    public:
        // Constructors & Destructors
        Pathfinding();
        Pathfinding(const Pathfinding& other) = delete;
        Pathfinding& operator=(const Pathfinding& other) = delete;
        ~Pathfinding() = default;

        // Getters & Setters
        bool isInProgress() const;

        // Member Functions
        void execute(int S2Key, int startIndex, std::vector<Cell>& gridVec);
        void DFSFFill(std::vector<Cell>& gridVec, int w, int h, int startIndex);
        void BFSFfill(std::vector<Cell>& grid, int w, int h, int startIndex);
        bool deltaThresholdReached();

    private:
        bool inProgress;
        int currentAlgorithm;
        int cellsThisFrame;
        float deltaTimeAccumulator;
        std::queue<std::pair<int, int>> cellQueue;
        std::stack<std::pair<int, int>> cellStack;
};

#endif
