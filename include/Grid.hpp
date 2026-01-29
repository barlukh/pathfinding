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
        Grid() = delete;
        Grid(int gridCellsX, int gridCellsY);
        Grid(const Grid& other) = delete;
        Grid& operator=(const Grid& other) = delete;
        ~Grid() = default;

        // Getters & Setters
        void setGridCellSize(int windowHeight);
        Cell& at(int x, int y);

        // Member Functions
        void drawGrid();
        void drawCells();

    private:
        int _gridCellSize;
        std::vector<Cell> _cells;
};

#endif
