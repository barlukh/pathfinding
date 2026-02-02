/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.cpp                                                                */
/*  Purpose:    Source file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/02                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "UI.hpp"
#include "config.hpp"
#include "raylib.h"
#include <array>
#include <string>
#include <string_view>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

UI::UI()
:   _paintMode(false),
    _optKey(1),
    _textSize(0),
    _step1Pos{0, 0},
    _selectPos{0, 0},
    _optPos{0, 0},
    _font(GetFontDefault())
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

int UI::getOptKey() const
{
    return _optKey;
}

bool UI::getPaintMode() const
{
    return _paintMode;
}

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

void UI::detectInput(int& lastGridX, int& lastGridY)
{
    if (IsKeyPressed(KEY_ONE))
    {
        _optKey = 1;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        _optKey = 2;
    }
    if (IsKeyPressed(KEY_THREE))
    {
        _optKey = 3;
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        _optKey = 4;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        _paintMode = true;
    }
    else
    {
        _paintMode = false;
        lastGridX = -1;
        lastGridY = -1;
    }
}

void UI::drawUI()
{
    DrawTextEx(_font, conf::step1.data(), _step1Pos, _textSize, 5, BLACK);

    std::string s = std::string(conf::selection.data()) + conf::opts[_optKey - 1].data();
    DrawTextEx(_font, s.c_str(), _selectPos, _textSize, 5, BLACK);
}
