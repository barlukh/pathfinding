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
        bool isDrawModeOn() const;
        float getGridCellSize() const;
        const std::vector<Cell>& getGridVec() const;
        const Rectangle& getGridRec() const;
        void setDrawMode(bool mode);
        void setGridVec(int windowHeight);
        void setGridRec();

        // Member Functions
        Cell& at(int x, int y);
        State edit(int s1Key, Vector2 mGridCurPos, Vector2 mGridLastPos);
        void placeSpecialCell(int x, int y, Cell::Type paintType);
        void drawBresenhamLine(int x0, int y0, int x1, int y1, Cell::Type paintType);
        void clearSpecialCell(Cell::Type paintType);
        void drawGrid();

        // CLEAN THIS
        void setGridCell(const std::vector<int>& order);

    private:
        bool drawMode;
        int startIndex;
        int finishIndex;
        int counter;
        float gridCellSize;
        std::vector<Cell> gridVec;
        Rectangle gridRec;
};

#endif
