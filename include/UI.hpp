/* ************************************************************************************ */
/*                                                                                      */
/*  File:       UI.hpp                                                                  */
/*  Purpose:    Header file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/17                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef UI_HPP
#define UI_HPP

#include "Cell.hpp"
#include "raylib.h"
#include <vector>


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
        bool isExecModeOn() const;
        bool isPartialClearModeOn() const;
        bool isFullClearModeOn() const;
        int getS1Key() const;
        int getS2Key() const;
        const Vector2& getMouseCur() const;
        const Vector2& getMouseLast() const;
        void setExecMode(bool mode);
        void setMouseCur(float gridCellSize);
        void setMouseLast(Vector2 pos);

        // Member Functions
        void calcUIPosValues(const Rectangle& gridRec);
        void detectInput();
        void drawUI();
        void drawGrid(const std::vector<Cell>& gridVec, const Rectangle& gridRec);

    private:
        bool paintMode;
        bool execMode;
        bool partialClearMode;
        bool fullClearMode;
        int s1Key;
        int s2Key;
        float textSize;
        Vector2 mouseCur;
        Vector2 mouseLast;
        Vector2 step1Pos;
        Vector2 select1Pos;
        Vector2 step2Pos;
        Vector2 select2Pos;
        Vector2 step3Pos;
        Vector2 colorIndexPos;
        Rectangle recIndex0;
        Rectangle recIndex1;
        Rectangle recIndex2;
        Rectangle recIndex3;
        Rectangle recIndex4;
        Rectangle recIndex5;
        Rectangle recIndex6;
        Font font;
};

#endif
