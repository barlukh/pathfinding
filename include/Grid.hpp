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
        bool drawFlag() const;
        const std::vector<Cell>& getGridVec() const;
        const Rectangle& getGridRec() const;
        void setDrawFlag(bool value);
        void setGridVec(int windowHeight);
        void setGridRec();
        
        void setGridCell(const std::vector<int>& order);
        int& getLastGridX();
        int& getLastGridY();

        // Member Functions
        Cell& at(int x, int y);
        void paintCells(int paintKey);
        void placeSpecialCell(int x, int y, Cell::Type paintType);
        void drawBresenhamLine(int gridX, int gridY, Cell::Type paintType);
        void clearSpecialCell(Cell::Type paintType);
        void drawGrid();

    private:
        bool _drawFlag;
        int _lastGridX;
        int _lastGridY;
        int _startIndex;
        int _finishIndex;
        int _counter;
        float _gridCellSize;
        std::vector<Cell> _gridVec;
        Rectangle _gridRec;
};

#endif
