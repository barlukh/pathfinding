/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.cpp                                                                */
/*  Purpose:    Source file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/05                                                              */
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
:   paintMode(false),
    paintKey(1),
    algoKey(1),
    textSize(0),
    mGridLastPos({-1, -1}),
    step1Pos({0, 0}),
    select1Pos({0, 0}),
    step2Pos({0, 0}),
    select2Pos({0, 0}),
    font(GetFontDefault())
{}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

bool UI::isPaintModeOn() const
{
    return paintMode;
}

int UI::getPaintKey() const
{
    return paintKey;
}

const Vector2& UI::getMGridLastPos() const
{
    return mGridLastPos;
}

void UI::setMGridLastPos(Vector2 pos)
{
    mGridLastPos.x = pos.x;
    mGridLastPos.y = pos.y;
}

void UI::setTextPos(const Rectangle& gridRec)
{
    float xOffset = gridRec.width + conf::gridPad;

    // Set position of the 'Step 1' info panel
    step1Pos.x = xOffset;
    step1Pos.y = conf::halfPad;

    select1Pos.x = xOffset;
    select1Pos.y = step1Pos.y + (gridRec.height / conf::offsetYScaling);

    // Set position of the 'Step 2' info panel
    step2Pos.x = xOffset;
    step2Pos.y = select1Pos.y + (gridRec.height / conf::offsetYScaling);

    select2Pos.x = xOffset;
    select2Pos.y = step2Pos.y + (gridRec.height / conf::offsetYScaling);

    // Set text size
    textSize = gridRec.width / conf::textScaling;
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void UI::detectInput()
{
    // Detect cell type selection input
    if (IsKeyPressed(KEY_ONE))
    {
        paintKey = 1;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        paintKey = 2;
    }
    if (IsKeyPressed(KEY_THREE))
    {
        paintKey = 3;
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        paintKey = 4;
    }

    // Detect algorithm selection input
    if (IsKeyPressed(KEY_Q))
    {
        algoKey = 1;
    }

    if (IsKeyPressed(KEY_W))
    {
        algoKey = 2;
    }

    if (IsKeyPressed(KEY_E))
    {
        algoKey = 3;
    }

    if (IsKeyPressed(KEY_R))
    {
        algoKey = 4;
    }

    // Detect mouse being pressed (paint mode on/off)
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        paintMode = true;
    }
    else
    {
        paintMode = false;
        mGridLastPos.x = -1;
        mGridLastPos.y = -1;
    }
}

void UI::drawUI()
{
    // Draw 'Step 1' info with the current selection
    DrawTextEx(font, conf::step1.data(), step1Pos, textSize, conf::textSpacing, BLACK);

    std::string s1 = std::string(conf::selection1.data());
    std::string s2 = conf::opts1[paintKey - 1].data();
    std::string s =  s1 + s2;
    DrawTextEx(font, s.c_str(), select1Pos, textSize, conf::textSpacing, DARKPURPLE);

    // Draw 'Step 2' info with the current selection
    DrawTextEx(font, conf::step2.data(), step2Pos, textSize, conf::textSpacing, BLACK);

    s1 = std::string(conf::selection2.data());
    s2 = conf::opts2[algoKey - 1].data();
    s =  s1 + s2;
    DrawTextEx(font, s.c_str(), select2Pos, textSize, conf::textSpacing, DARKPURPLE);
}
