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
        Cell() = default;
        Cell(int x, int y, Type type);
        Cell(const Cell& other) = default;
        Cell& operator=(const Cell& other) = default;
        ~Cell() = default;

        // Getters & Setters
        Type getType() const;

    private:
        int _x;
        int _y;
        Type _type;
};

#endif
