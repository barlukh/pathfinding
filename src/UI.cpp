/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.cpp                                                                */
/*  Purpose:    Source file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/06                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "UI.hpp"
#include "Cell.hpp"
#include "config.hpp"
#include "raylib.h"
#include <array>
#include <string>
#include <string_view>
#include <vector>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

UI::UI()
:   paintMode(false),
    execMode(false),
    s1Key(1),
    s2Key(1),
    textSize(0),
    mouseCur({-1, -1}),
    mouseLast({-1, -1}),
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

bool UI::isExecModeOn() const
{
    return execMode;
}

int UI::getS1Key() const
{
    return s1Key;
}

int UI::getS2Key() const
{
    return s2Key;
}

const Vector2& UI::getMouseCur() const
{
    return mouseCur;
}

const Vector2& UI::getMouseLast() const
{
    return mouseLast;
}

void UI::setMouseCur(float gridCellSize)
{
    Vector2 mousePos = GetMousePosition();

    mouseCur.x = (mousePos.x - conf::halfPad) / gridCellSize;
    mouseCur.y = (mousePos.y - conf::halfPad) / gridCellSize;
}

void UI::setMouseLast(Vector2 pos)
{
    mouseLast = {pos.x, pos.y};
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

void UI::calcUIPosValues(const Rectangle& gridRec)
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

void UI::detectInput()
{
    // Detect cell type selection input
    if (IsKeyPressed(KEY_ONE))
        s1Key = 1;

    if (IsKeyPressed(KEY_TWO))
        s1Key = 2;

    if (IsKeyPressed(KEY_THREE))
        s1Key = 3;

    if (IsKeyPressed(KEY_FOUR))
        s1Key = 4;

    // Detect algorithm selection input
    if (IsKeyPressed(KEY_Q))
        s2Key = 1;

    if (IsKeyPressed(KEY_W))
        s2Key = 2;

    if (IsKeyPressed(KEY_E))
        s2Key = 3;

    if (IsKeyPressed(KEY_R))
        s2Key = 4;

    // Detect mouse being pressed (paint mode on/off)
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        paintMode = true;
    else
    {
        paintMode = false;
        mouseLast = {-1, -1};
    }

    // Detect execution input
    if (IsKeyPressed(KEY_SPACE))
        execMode = true;
}

void UI::drawUI()
{
    // Draw 'Step 1' info with the current selection
    DrawTextEx(font, conf::step1.data(), step1Pos, textSize, conf::textSpacing, BLACK);

    std::string s1 = std::string(conf::selection1.data());
    std::string s2 = conf::opts1[s1Key - 1].data();
    std::string s =  s1 + s2;
    DrawTextEx(font, s.c_str(), select1Pos, textSize, conf::textSpacing, DARKPURPLE);

    // Draw 'Step 2' info with the current selection
    DrawTextEx(font, conf::step2.data(), step2Pos, textSize, conf::textSpacing, BLACK);

    s1 = std::string(conf::selection2.data());
    s2 = conf::opts2[s2Key - 1].data();
    s =  s1 + s2;
    DrawTextEx(font, s.c_str(), select2Pos, textSize, conf::textSpacing, DARKPURPLE);
}

void UI::drawGrid(const std::vector<Cell>& gridVec, const Rectangle& gridRec)
{
    Color color;

    for (int y = 0; y < conf::gridCellsY; y++)
    {
        for (int x = 0; x < conf::gridCellsX; x++)
        {
            Cell currentCell = gridVec[y * conf::gridCellsX + x];
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

    // Draw the outside rectangle to compensate for the inner line thickness
    DrawRectangleLinesEx(gridRec, 2.0f, DARKGRAY);
}
