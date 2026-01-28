/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Cell.hpp                                                                */
/*  Purpose:    Header file for the Class Cell                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/28                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef CELL_HPP
#define CELL_HPP


class Cell
{
    public:
        enum class Type
        {
            PLAYER,
            EMPTY,
            OBSTACLE,
            GOAL
        };

        // Constructors & Destructors
        Cell() = delete;
        Cell(float x, float y, Type type);
        Cell(const Cell& other) = delete;
        Cell& operator=(const Cell& other) = delete;
        ~Cell() = default;

    private:
        float _x;
        float _y;
        Type _type;
};

#endif
