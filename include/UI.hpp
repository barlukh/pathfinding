/* ************************************************************************************ */
/*                                                                                      */
/*  File:       UI.hpp                                                                  */
/*  Purpose:    Header file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/03                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef UI_HPP
#define UI_HPP

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
        int getPaintKey() const;
        bool getPaintMode() const;
        void setTextPos(const Rectangle& gridRec);

        // Member Functions
        void detectInput(int& lastGridX, int& lastGridY);
        void drawUI();

    private:
        bool _paintMode;
        int _paintKey;
        int _algoKey;
        float _textSize;
        Vector2 _step1Pos;
        Vector2 _select1Pos;
        Vector2 _step2Pos;
        Vector2 _select2Pos;
        Font _font;
};

#endif
