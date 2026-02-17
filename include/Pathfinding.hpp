/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.hpp                                                         */
/*  Purpose:    Header file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/17                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Cell.hpp"
#include <deque>
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
        void exec(std::vector<Cell>& gridVec, int S2Key, int start, int goal);
        void floodFind(std::vector<Cell>& gridVec, int w, int h, int start, int goal);
        bool deltaThresholdReached();

    private:
        bool inProgress;
        int currentAlgorithm;
        int cellsThisFrame;
        float deltaTimeAccumulator;
        std::deque<int> cellDeque;
        std::vector<int> dist;
        std::vector<int> parent;
};

#endif
