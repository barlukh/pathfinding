/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.cpp                                                                */
/*  Purpose:    Source file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/01                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "UI.hpp"
#include "config.hpp"
#include "raylib.h"
#include <array>
#include <string_view>
#include <string>

//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

UI::UI()
:   _optKey(1),
    _step1Pos{0, 0},
    _selectPos{0, 0},
    _optPos{0, 0},
    _font(GetFontDefault()),
    _textSize(0) 
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

void UI::setTextPos(const Rectangle& gridRec)
{
    _step1Pos.x = gridRec.width + conf::gridPad;
    _step1Pos.y = conf::halfPad;

    _selectPos.x = gridRec.width + conf::gridPad;
    _selectPos.y = conf::halfPad + (gridRec.height / conf::offsetYScaling);

    _optPos.x = gridRec.width + conf::gridPad + gridRec.width / conf::optScaling;
    _optPos.y = conf::halfPad + (gridRec.height / conf::offsetYScaling);

    _textSize = gridRec.width / conf::textScaling;
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void UI::drawUI()
{
    DrawTextEx(_font, conf::step1.data(), _step1Pos, _textSize, 5, BLACK);

    std::string s = std::string(conf::selection.data()) + conf::opts[_optKey - 1].data();
    DrawTextEx(_font, s.c_str(), _selectPos, _textSize, 5, BLACK);
}
