/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.cpp                                                                */
/*  Purpose:    Source file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/06                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Grid.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include "raylib.h"
#include <cstdlib>
#include <vector>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Grid::Grid(int gridCellsX, int gridCellsY)
:   startIndex(-1),
    finishIndex(-1),
    counter(0),
    gridCellSize(0),
    gridVec(gridCellsX * gridCellsY),
    gridRec({0, 0, 0, 0})
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

int Grid::getStartIndex() const
{
    return startIndex;
}

float Grid::getGridCellSize() const
{
    return gridCellSize;
}

const std::vector<Cell>& Grid::getGridVec() const
{
    return gridVec;
}

const Rectangle& Grid::getGridRec() const
{
    return gridRec;
}

void Grid::setGridVec(int windowHeight)
{
    gridCellSize = static_cast<float>(windowHeight - conf::gridPad) / conf::gridCellsY;

    for (int y = 0; y < conf::gridCellsY; y++)
    {
        for (int x = 0; x < conf::gridCellsX; x++)
        {
            float posX = (static_cast<float>(x) * gridCellSize) + conf::halfPad;
            float posY = (static_cast<float>(y) * gridCellSize) + conf::halfPad;
            at(x, y) = Cell(posX, posY, gridCellSize, Cell::Type::EMPTY);
        }
    }
}

void Grid::setGridRec()
{
    float x = conf::halfPad;
    float y = conf::halfPad;
    float width = static_cast<float>(conf::gridCellsX) * gridCellSize;
    float height = static_cast<float>(conf::gridCellsY) * gridCellSize;

    gridRec = {x, y, width, height};
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

Cell& Grid::at(int x, int y)
{
    return gridVec[y * conf::gridCellsX + x];
}

Grid::Pos Grid::paint(int s1Key, Vector2 mouseCur, Vector2 mouseLast)
{
    int gridX = mouseCur.x;
    int gridY = mouseCur.y;

    if (gridX < 0 || gridX >= conf::gridCellsX || gridY < 0 || gridY >= conf::gridCellsY)
        return Pos::OUT_OF_BOUNDS;

    Cell::Type paintType = static_cast<Cell::Type>(s1Key - 1);

    if (paintType == Cell::Type::START || paintType == Cell::Type::FINISH)
    {
        placeSpecialCell(gridX, gridY, paintType);
        return Pos::IN_BOUNDS;
    }

    if (mouseLast.x == -1)
    {
        at(gridX, gridY).setType(paintType);
        return Pos::IN_BOUNDS;
    }

    drawBresenhamLine(mouseLast.x, mouseLast.y, gridX, gridY, paintType);
    return Pos::IN_BOUNDS;
}

void Grid::placeSpecialCell(int x, int y, Cell::Type paintType)
{
    int newIndex = y * conf::gridCellsX + x;

    if (paintType == Cell::Type::START && finishIndex == newIndex)
        finishIndex = -1;
    else if (paintType == Cell::Type::FINISH && startIndex == newIndex)
        startIndex = -1;

    int& index = (paintType == Cell::Type::START) ? startIndex : finishIndex;
    if (index != -1)
        gridVec[index].setType(Cell::Type::EMPTY);

    at(x, y).setType(paintType);
    index = newIndex;
}

void Grid::drawBresenhamLine(int x0, int y0, int x1, int y1, Cell::Type paintType)
{
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
}

void Grid::clearSpecialCell(Cell::Type paintType)
{
    if (paintType == Cell::Type::START)
        startIndex = -1;
    else if (paintType == Cell::Type::FINISH)
        finishIndex = -1;
}

void Grid::visualize(const std::vector<int>& order)
{
    if (counter < static_cast<int>(order.size() - 1))
    {
        gridVec[order[counter]].setType(Cell::Type::VISITED);
        counter++;
    }
    else
    {
        counter = 0;
        // visualizeMode = false;
    }
}
