/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.cpp                                                                */
/*  Purpose:    Source file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/04                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Grid.hpp"
#include "config.hpp"
#include "raylib.h"
#include <cstdlib>
#include <vector>


#include <iostream>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Grid::Grid(int gridCellsX, int gridCellsY)
:   _drawFlag(false),
    _lastGridX(-1),
    _lastGridY(-1),
    _startIndex(-1),
    _finishIndex(-1),
    _counter(0),
    _gridCellSize(0),
    _gridVec(gridCellsX * gridCellsY),
    _gridRec({0, 0, 0, 0})
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

int& Grid::getLastGridX()
{
    return _lastGridX;
}

int& Grid::getLastGridY()
{
    return _lastGridY;
}

const std::vector<Cell>& Grid::getGridVec() const
{
    return _gridVec;
}

const Rectangle& Grid::getGridRec() const
{
    return _gridRec;
}

bool Grid::drawFlag() const
{
    return _drawFlag;
}

void Grid::setDrawFlag(bool value)
{
    _drawFlag = value;
}


void Grid::setGridVec(int windowHeight)
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

void Grid::setGridCell(const std::vector<int>& order)
{
    if (_counter < static_cast<int>(order.size() - 1))
    {
        _gridVec[order[_counter]].setType(Cell::Type::VISITED);
        _counter++;
    }
    else
    {
        _counter = 0;
        _drawFlag = false;
    }
}

Cell& Grid::at(int x, int y)
{
    return _gridVec[y * conf::gridCellsX + x];
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Grid::paintCells(int paintKey)
{
    Vector2 mousePos = GetMousePosition();

    int gridX = (mousePos.x - conf::halfPad) / _gridCellSize;
    int gridY = (mousePos.y - conf::halfPad) / _gridCellSize;

    if (gridX < 0 || gridX >= conf::gridCellsX || gridY < 0 || gridY >= conf::gridCellsY)
    {
        _lastGridX = -1;
        _lastGridY = -1;
        return;
    }

    Cell::Type paintType = static_cast<Cell::Type>(paintKey - 1);

    if (paintType == Cell::Type::START || paintType == Cell::Type::FINISH)
    {
        placeSpecialCell(gridX, gridY, paintType);
        _lastGridX = gridX;
        _lastGridY = gridY;
        return;
    }

    if (_lastGridX == -1)
    {
        at(gridX, gridY).setType(paintType);
        _lastGridX = gridX;
        _lastGridY = gridY;
        return;
    }

    drawBresenhamLine(gridX, gridY, paintType);
}

void Grid::placeSpecialCell(int x, int y, Cell::Type paintType)
{
    int newIndex = y * conf::gridCellsX + x;

    if (paintType == Cell::Type::START && _finishIndex == newIndex)
    {
        _finishIndex = -1;
    }
    else if (paintType == Cell::Type::FINISH && _startIndex == newIndex)
    {
        _startIndex = -1;
    }

    int& index = (paintType == Cell::Type::START) ? _startIndex : _finishIndex;
    if (index != -1)
    {
        _gridVec[index].setType(Cell::Type::EMPTY);
    }

    at(x, y).setType(paintType);
    index = newIndex;
}

void Grid::drawBresenhamLine(int gridX, int gridY, Cell::Type paintType)
{
    int x0 = _lastGridX;
    int y0 = _lastGridY;
    int x1 = gridX;
    int y1 = gridY;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        Cell& cell = at(x0, y0);

        clearSpecialCell(cell.getType());

        cell.setType(paintType);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 <  dx)
        {
            err += dx;
            y0 += sy;
        }
    }

    _lastGridX = gridX;
    _lastGridY = gridY;
}

void Grid::clearSpecialCell(Cell::Type paintType)
{
    if (paintType == Cell::Type::START)
    {
        _startIndex = -1;
    }
    else if (paintType == Cell::Type::FINISH)
    {
        _finishIndex = -1;
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
            case Cell::Type::START:
                color = BLUE;
                break;
            case Cell::Type::FINISH:
                color = RED;
                break;
            case Cell::Type::OBSTACLE:
                color = BLACK;
                break;
            case Cell::Type::EMPTY:
                color = LIGHTGRAY;
                break;
            case Cell::Type::VISITED:
                color = YELLOW;
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
