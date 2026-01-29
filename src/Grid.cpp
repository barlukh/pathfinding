/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.cpp                                                                */
/*  Purpose:    Source file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/28                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Grid.hpp"
#include "config.hpp"
#include "raylib.h"
#include <vector>

static void drawGridBackRectanlge(int gridCellSize);
static void drawGridLines(int gridCellSize);


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Grid::Grid(int gridCellsX, int gridCellsY)
:   _gridCellSize(0),
    _cells(gridCellsX * gridCellsY)
{
    for (int y = 0; y < conf::gridCellsY; y++)
    {
        for (int x = 0; x < conf::gridCellsX; x++)
        {
            at(x, y) = Cell(x, y, Cell::Type::EMPTY);
        }
    }
}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

void Grid::setGridCellSize(int windowHeight)
{
    _gridCellSize = (windowHeight - conf::gridPad) / conf::gridCellsY;
}

Cell& Grid::at(int x, int y)
{
    return _cells[y * conf::gridCellsX + x];
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Grid::drawGrid()
{
    drawGridBackRectanlge(_gridCellSize);
    drawGridLines(_gridCellSize);
}

void Grid::drawCells()
{
    Color color = BLUE;

    for (int y = 0; y < conf::gridCellsY; y++)
    {
        for (int x = 0; x < conf::gridCellsX; x++)
        {
            // switch (at(x, y).getType())
            // {
            // case Cell::Type::PLAYER:
            //     color = BLUE;
            //     break;
            // case Cell::Type::EMPTY:
            //     color = RAYWHITE;
            //     break;
            // case Cell::Type::OBSTACLE:
            //     color = BLACK;
            //     break;
            // case Cell::Type::GOAL:
            //     color = YELLOW;
            //     break;
            // default:
            //     color = RAYWHITE;
            //     break;
            // }

            DrawRectangle(
                conf::halfPad + x * _gridCellSize,
                conf::halfPad + y * _gridCellSize + 1,
                _gridCellSize - 1,
                _gridCellSize - 1,
                color
            );
        }
    }
}


//----------------------------------------------------------------------------------------
// Static Functions
//----------------------------------------------------------------------------------------

static void drawGridBackRectanlge(int gridCellSize)
{
    DrawRectangle(
        conf::halfPad,
        conf::halfPad,
        conf::gridCellsX * gridCellSize,
        conf::gridCellsY * gridCellSize,
        LIGHTGRAY
    );
}

static void drawGridLines(int gridCellSize)
{
    for (int y = 0; y <= conf::gridCellsY; y++)
    {
        DrawLine(
            conf::halfPad,
            conf::halfPad + y * gridCellSize,
            conf::halfPad + conf::gridCellsX * gridCellSize,
            conf::halfPad + y * gridCellSize,
            BLACK
        );
    }

    for (int x = 0; x <= conf::gridCellsX; x++)
    {
        DrawLine(
            conf::halfPad + x * gridCellSize,
            conf::halfPad,
            conf::halfPad + x * gridCellSize,
            conf::halfPad + conf::gridCellsY * gridCellSize,
            BLACK
        );
    }
}
