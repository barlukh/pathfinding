/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.cpp                                                                */
/*  Purpose:    Source file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/30                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Grid.hpp"
#include "config.hpp"
#include "raylib.h"
#include <vector>


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
    Color color;

    for (int y = 0; y < conf::gridCellsY; y++)
    {
        for (int x = 0; x < conf::gridCellsX; x++)
        {
            switch (at(x, y).getType())
            {
            case Cell::Type::PLAYER:
                color = BLUE;
                break;
            case Cell::Type::EMPTY:
                color = LIGHTGRAY;
                break;
            case Cell::Type::OBSTACLE:
                color = BLACK;
                break;
            case Cell::Type::GOAL:
                color = YELLOW;
                break;
            default:
                color = RAYWHITE;
                break;
            }

            int posX = conf::halfPad + x * _gridCellSize;
            int posY = conf::halfPad + y * _gridCellSize;
            int width = _gridCellSize + 1;
            int height = _gridCellSize + 1;

            DrawRectangle(posX, posY, width, height, color);
            DrawRectangleLines(posX, posY, width, height, BLACK);
        }
    }
}
