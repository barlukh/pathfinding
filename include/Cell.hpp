/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.hpp                                                                */
/*  Purpose:    Header file for the Class Cell                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/05                                                              */
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
            FINISH,
            OBSTACLE,
            EMPTY,
            VISITED
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
