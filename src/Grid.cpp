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

static void DrawGridBackRectanlge(float gridCellSize);
static void DrawGridLines(float gridCellSize);


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

void Grid::setGridCellSize(int windowHeight)
{
    gridCellSize = (static_cast<float>(windowHeight - conf::gridPad) / conf::gridCellsY);
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void Grid::DrawGrid()
{
    DrawGridBackRectanlge(this->gridCellSize);
    DrawGridLines(this->gridCellSize);
}


//----------------------------------------------------------------------------------------
// Static Functions
//----------------------------------------------------------------------------------------

static void DrawGridBackRectanlge(float gridCellSize)
{
    DrawRectangle(
        conf::halfPad,
        conf::halfPad,
        conf::gridCellsX * gridCellSize,
        conf::gridCellsY * gridCellSize,
        LIGHTGRAY
    );
}

static void DrawGridLines(float gridCellSize)
{
    for (size_t y = 0; y <= conf::gridCellsY; y++)
    {
        DrawLine(
            conf::halfPad,
            conf::halfPad + y * gridCellSize,
            conf::halfPad + conf::gridCellsX * gridCellSize,
            conf::halfPad + y * gridCellSize,
            BLACK
        );
    }

    for (size_t x = 0; x <= conf::gridCellsX; x++)
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
