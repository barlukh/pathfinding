/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.hpp                                                                */
/*  Purpose:    Header file for the Class Cell                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/16                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef CELL_HPP
#define CELL_HPP

#include "raylib.h"


class Cell
{
    public:
        enum class Type
        {
            START,
            GOAL,
            WALL,
            EMPTY,
            VISITED,
            QUEUED,
            PATH
        };

        // Constructors & Destructors
        Cell() = default;
        Cell(float posX, float posY, float gridCellSize, Type type);
        Cell(const Cell& other) = default;
        Cell& operator=(const Cell& other) = default;
        ~Cell() = default;

        // Getters & Setters
        const Rectangle& getCell() const;
        Type getType() const;
        void setType(Type type);

    private:
        Rectangle cell;
        Type type;
};

#endif
