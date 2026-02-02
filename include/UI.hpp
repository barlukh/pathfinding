/* ************************************************************************************ */
/*                                                                                      */
/*  File:       UI.hpp                                                                  */
/*  Purpose:    Header file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/02                                                              */
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
        int getOptKey() const;
        bool getPaintMode() const;
        void setTextPos(const Rectangle& gridRec);

        // Member Functions
        void detectInput(int& lastGridX, int& lastGridY);
        void drawUI();

    private:
        bool _paintMode;
        int _optKey;
        float _textSize;
        Vector2 _step1Pos;
        Vector2 _selectPos;
        Vector2 _optPos;
        Font _font;
};

#endif
