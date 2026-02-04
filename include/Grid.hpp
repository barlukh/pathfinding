/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.hpp                                                                */
/*  Purpose:    Header file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/04                                                              */
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
        int& getLastGridX();
        int& getLastGridY();
        const std::vector<Cell>& getGrid() const;
        const Rectangle& getGridRec() const;
        bool getDrawFloodFill() const;
        void setDrawFloodFill(bool value);
        void setCells(int windowHeight);
        void setGridRec();
        void setGridCell(const std::vector<int>& order);
        Cell& at(int x, int y);

        // Member Functions
        void paintCells(int paintKey);
        void placeSpecialCell(int x, int y, Cell::Type paintType);
        void drawBresenhamLine(int gridX, int gridY, Cell::Type paintType);
        void clearSpecialCell(Cell::Type paintType);
        void drawGrid();

    private:
        bool _draw;
        int _lastGridX;
        int _lastGridY;
        int _startIndex;
        int _finishIndex;
        int _counter;
        float _gridCellSize;
        std::vector<Cell> _grid;
        Rectangle _gridRec;
};

#endif
