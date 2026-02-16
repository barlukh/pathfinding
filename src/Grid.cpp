/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.cpp                                                                */
/*  Purpose:    Source file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/16                                                              */
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
    goalIndex(-1),
    gridCellSize(0),
    gridVec(gridCellsX * gridCellsY),
    gridRec({0, 0, 0, 0})
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

int Grid::getStart() const
{
    return startIndex;
}

int Grid::getGoal() const
{
    return goalIndex;
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

    // Return if mouse position is out of grid bounds
    if (gridX < 0 || gridX >= conf::gridCellsX || gridY < 0 || gridY >= conf::gridCellsY)
        return Pos::OUT_OF_BOUNDS;

    Cell::Type paintType = static_cast<Cell::Type>(s1Key - 1);

    // Handle the uniqueness of the 'start' an 'goal' cells
    if (paintType == Cell::Type::START || paintType == Cell::Type::GOAL)
    {
        placeSpecialCell(gridX, gridY, paintType);
        return Pos::IN_BOUNDS;
    }

    // Place first cell
    if (mouseLast.x == -1)
    {
        Cell& cell = at(gridX, gridY);

        clearSpecialCell(cell.getType());
        cell.setType(paintType);
        return Pos::IN_BOUNDS;
    }

    // Draw line based on mouse delta
    drawBresenhamLine(mouseLast.x, mouseLast.y, gridX, gridY, paintType);
    return Pos::IN_BOUNDS;
}

void Grid::placeSpecialCell(int x, int y, Cell::Type paintType)
{
    int newIndex = y * conf::gridCellsX + x;

    if (paintType == Cell::Type::START && goalIndex == newIndex)
        goalIndex = -1;
    else if (paintType == Cell::Type::GOAL && startIndex == newIndex)
        startIndex = -1;

    int& index = (paintType == Cell::Type::START) ? startIndex : goalIndex;
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
    else if (paintType == Cell::Type::GOAL)
        goalIndex = -1;
}

std::vector<Cell>& Grid::refGridVec()
{
    return gridVec;
}

void Grid::partialClear()
{
    for (Cell& cell : gridVec)
    {
        Cell::Type t = cell.getType();
        if (t == Cell::Type::VISITED || t == Cell::Type::QUEUED || t == Cell::Type::PATH)
            cell.setType(Cell::Type::EMPTY);
    }
}

void Grid::fullClear()
{
    for (Cell& cell : gridVec)
        cell.setType(Cell::Type::EMPTY);
}
