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
    _paintKey(1),
    _textSize(0),
    _step1Pos{0, 0},
    _select1Pos{0, 0},
    _paintKeyPos{0, 0},
    _step2Pos{0, 0},
    _font(GetFontDefault())
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

int UI::getPaintKey() const
{
    return _paintKey;
}

bool UI::getPaintMode() const
{
    return _paintMode;
}

void UI::setTextPos(const Rectangle& gridRec)
{
    float xOffset = gridRec.width + conf::gridPad;

    _step1Pos.x = xOffset;
    _step1Pos.y = conf::halfPad;

    _select1Pos.x = xOffset;
    _select1Pos.y = conf::halfPad + (gridRec.height / conf::offsetYScaling);

    _paintKeyPos.x = xOffset + gridRec.width / conf::optScaling;
    _paintKeyPos.y = conf::halfPad + (gridRec.height / conf::offsetYScaling);

    _step2Pos.x = xOffset;
    _step2Pos.y = _select1Pos.y + (gridRec.height / conf::offsetYScaling);

    _textSize = gridRec.width / conf::textScaling;
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void UI::detectInput(int& lastGridX, int& lastGridY)
{
    if (IsKeyPressed(KEY_ONE))
    {
        _paintKey = 1;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        _paintKey = 2;
    }
    if (IsKeyPressed(KEY_THREE))
    {
        _paintKey = 3;
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        _paintKey = 4;
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

    std::string s1 = std::string(conf::selection1.data());
    std::string s2 = conf::opts1[_paintKey - 1].data();
    std::string s =  s1 + s2;
    DrawTextEx(_font, s.c_str(), _select1Pos, _textSize, 5, BLACK);

    DrawTextEx(_font, conf::step2.data(), _step2Pos, _textSize, 5, BLACK);
}
