/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.hpp                                                         */
/*  Purpose:    Header file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/06                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Cell.hpp"
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
        void floodFill(std::vector<Cell>& gridVec, int w, int h, int start);
        bool deltaThresholdReached();

    private:
        bool inProgress;
        int currentAlgorithm;
        int cellsThisFrame;
        float deltaTimeAccumulator;
        std::stack<std::pair<int, int>> cellStack;
};

#endif
