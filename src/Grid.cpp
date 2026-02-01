/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.cpp                                                                */
/*  Purpose:    Source file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/01                                                              */
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
    _cells(gridCellsX * gridCellsY),
    _gridRec({0, 0, 0, 0})
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

const Rectangle& Grid::getGridRec() const
{
    return _gridRec;
}

void Grid::setCells(int windowHeight)
{
    _gridCellSize = static_cast<float>(windowHeight - conf::gridPad) / conf::gridCellsY;

    for (int y = 0; y < conf::gridCellsY; y++)
    {
        for (int x = 0; x < conf::gridCellsX; x++)
        {
            float posX = (static_cast<float>(x) * _gridCellSize) + conf::halfPad;
            float posY = (static_cast<float>(y) * _gridCellSize) + conf::halfPad;
            at(x, y) = Cell(posX, posY, _gridCellSize, Cell::Type::EMPTY);
        }
    }
}

void Grid::setGridRec()
{
    float x = conf::halfPad;
    float y = conf::halfPad;
    float width = static_cast<float>(conf::gridCellsX) * _gridCellSize;
    float height = static_cast<float>(conf::gridCellsY) * _gridCellSize;

    _gridRec = {x, y, width, height};
}

Cell& Grid::at(int x, int y)
{
    return _cells[y * conf::gridCellsX + x];
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Grid::paintCells(int optKey)
{
    Vector2 mousePos = GetMousePosition();

    int gridX = (mousePos.x - conf::halfPad) / _gridCellSize;
    int gridY = (mousePos.y - conf::halfPad) / _gridCellSize;

    bool hovering =
        gridX >= 0 && gridX < conf::gridCellsX &&
        gridY >= 0 && gridY < conf::gridCellsY;

    if (hovering)
    {
        at(gridX, gridY).setType(static_cast<Cell::Type>(optKey - 1));
    }
}

void Grid::drawGrid()
{
    Color color;

    for (int y = 0; y < conf::gridCellsY; y++)
    {
        for (int x = 0; x < conf::gridCellsX; x++)
        {
            Cell currentCell = at(x, y);
            Rectangle cellRec = currentCell.getCell();
            Cell::Type type = currentCell.getType();

            switch (type)
            {
            case Cell::Type::PLAYER:
                color = BLUE;
                break;
            case Cell::Type::GOAL:
                color = YELLOW;
                break;
            case Cell::Type::OBSTACLE:
                color = BLACK;
                break;
            case Cell::Type::EMPTY:
                color = LIGHTGRAY;
                break;
            default:
                color = RAYWHITE;
                break;
            }

            DrawRectangleRec(cellRec, color);
            DrawRectangleLinesEx(cellRec, 1.0f, DARKGRAY);
        }
    }

    DrawRectangleLinesEx(getGridRec(), 2.0f, DARKGRAY);
}
