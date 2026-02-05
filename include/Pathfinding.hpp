/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.hpp                                                         */
/*  Purpose:    Header file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/05                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Cell.hpp"
#include <vector>


class Pathfinding
{
    public:
        // Constructors & Destructors
        Pathfinding() = default;
        Pathfinding(const Pathfinding& other) = delete;
        Pathfinding& operator=(const Pathfinding& other) = delete;
        ~Pathfinding() = default;

        // Getters & Setters
        const std::vector<int>& getPathfindOrder() const;

        // Member Functions
        void execute(int S2Key, int startIndex, const std::vector<Cell>& gridVec);
        void floodFill(const std::vector<Cell>& gridVec, int w, int h, int x, int y);

    private:
        std::vector<int> pathfindOrder;
};

#endif
