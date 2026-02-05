/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.hpp                                                                */
/*  Purpose:    Header file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/05                                                              */
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
        enum class State
        {
            MODIFIED,
            OUTOFBOUNDS
        };

        // Constructors & Destructors
        Grid() = delete;
        Grid(int gridCellsX, int gridCellsY);
        Grid(const Grid& other) = delete;
        Grid& operator=(const Grid& other) = delete;
        ~Grid() = default;

        // Getters & Setters
        bool drawState() const;
        float getGridCellSize() const;
        const std::vector<Cell>& getGridVec() const;
        const Rectangle& getGridRec() const;
        void setDrawState(bool state);
        void setGridVec(int windowHeight);
        void setGridRec();
        
        void setGridCell(const std::vector<int>& order);


        // Member Functions
        Cell& at(int x, int y);
        State updateCells(Vector2 mGridCurPos, Vector2 mGridLastPos, int paintKey);
        void placeSpecialCell(int x, int y, Cell::Type paintType);
        void drawBresenhamLine(int x0, int y0, int x1, int y1, Cell::Type paintType);
        void clearSpecialCell(Cell::Type paintType);
        void drawGrid();

    private:
        bool _drawState;
        int _startIndex;
        int _finishIndex;
        int _counter;
        float _gridCellSize;
        std::vector<Cell> _gridVec;
        Rectangle _gridRec;
};

#endif
