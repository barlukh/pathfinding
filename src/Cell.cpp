/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.cpp                                                                */
/*  Purpose:    Source file for the Class Cell                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/01                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Cell.hpp"
#include "raylib.h"


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Cell::Cell(float posX, float posY, float gridCellSize, Cell::Type type)
:   _cell{posX, posY, gridCellSize, gridCellSize},
    _type(type)
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

const Rectangle& Cell::getCell() const
{
    return _cell;
}

Cell::Type Cell::getType() const
{
    return _type;
}

void Cell::setType(Type type)
{
    _type = type;
}
