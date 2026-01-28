/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.hpp                                                                */
/*  Purpose:    Header file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/28                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef GRID_HPP
#define GRID_HPP

#include "Cell.hpp"
#include <vector>


class Grid
{
    public:
        // Constructors & Destructors
        Grid() = default;
        Grid(const Grid& other) = delete;
        Grid& operator=(const Grid& other) = delete;
        ~Grid() = default;

        // Getters & Setters
        void setGridCellSize(int windowHeight);

        // Member Functions
        void DrawGrid();

    private:
        float _gridCellSize;
        std::vector<std::vector<Cell>> _cells;
};

#endif
