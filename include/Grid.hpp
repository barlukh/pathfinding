/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.hpp                                                                */
/*  Purpose:    Header file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/02                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef GRID_HPP
#define GRID_HPP

#include "Cell.hpp"
#include "raylib.h"
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
        const Rectangle& getGridRec() const;
        int& getLastGridX();
        int& getLastGridY();
        void setCells(int windowHeight);
        void setGridRec();
        Cell& at(int x, int y);

        // Member Functions
        void paintCells(int optKey);
        void drawGrid();

    private:
        int _lastGridX;
        int _lastGridY;
        float _gridCellSize;
        std::vector<Cell> _cells;
        Rectangle _gridRec;
};

#endif
