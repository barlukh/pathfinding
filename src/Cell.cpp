/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.cpp                                                                */
/*  Purpose:    Source file for the Class Cell                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/05                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Cell.hpp"
#include "raylib.h"


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Cell::Cell(float posX, float posY, float gridCellSize, Cell::Type type)
:   cell{posX, posY, gridCellSize, gridCellSize},
    type(type)
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

const Rectangle& Cell::getCell() const
{
    return cell;
}

Cell::Type Cell::getType() const
{
    return type;
}

void Cell::setType(Type type)
{
    this->type = type;
}
