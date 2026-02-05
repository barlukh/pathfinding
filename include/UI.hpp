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
        int getS1Key() const;
        const Vector2& getMouseCur() const;
        const Vector2& getMouseLast() const;
        void setMouseCur(float gridCellSize);
        void setMouseLast(Vector2 pos);

        // Member Functions
        void calcUIPosValues(const Rectangle& gridRec);
        void detectInput();
        void drawUI();

    private:
        bool paintMode;
        int s1Key;
        int s2key;
        float textSize;
        Vector2 mouseCur;
        Vector2 mouseLast;
        Vector2 step1Pos;
        Vector2 select1Pos;
        Vector2 step2Pos;
        Vector2 select2Pos;
        Font font;
};

#endif
