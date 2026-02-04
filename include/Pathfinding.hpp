/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Pathfinding.hpp                                                         */
/*  Purpose:    Header file for the Class Pathfinding                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/04                                                              */
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
        const std::vector<int>& getFloodFillOrder() const;

        // Member Functions
        void floodFill(const std::vector<Cell>& grid, int width, int height, int x, int y);

    private:
        std::vector<int> _floodFillOrder;
};

#endif
