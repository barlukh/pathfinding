/* ************************************************************************************ */
/*                                                                                      */
/*  File:       UI.hpp                                                                  */
/*  Purpose:    Header file for the Class UI                                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/30                                                              */
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

    private:
        Rectangle _playerRec;
        Rectangle _obstacleRec;
        Rectangle _goalRec;
};

#endif
