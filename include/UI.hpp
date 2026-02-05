/* ************************************************************************************ */
/*                                                                                      */
/*  File:       UI.hpp                                                                  */
/*  Purpose:    Header file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/05                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef UI_HPP
#define UI_HPP

#include "Grid.hpp"
#include "raylib.h"


class UI
{
    public:
        // Constructors & Destructors
        UI();
        UI(const UI& other) = delete;
        UI& operator=(const UI& other) = delete;
        ~UI() = default;

        // Getters & Setters
        bool isPaintModeOn() const;
        int getPaintKey() const;
        const Vector2& getMGridLastPos() const;
        void setMGridLastPos(Vector2 pos);
        void setTextPos(const Rectangle& gridRec);

        // Member Functions
        void detectInput();
        void drawUI();

    private:
        bool paintMode;
        int paintKey;
        int algoKey;
        float textSize;
        Vector2 mGridLastPos;
        Vector2 step1Pos;
        Vector2 select1Pos;
        Vector2 step2Pos;
        Vector2 select2Pos;
        Font font;
};

#endif
