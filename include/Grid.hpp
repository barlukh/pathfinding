/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Grid.hpp                                                                */
/*  Purpose:    Header file for the Class Grid                                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/28                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef GRID_HPP
#define GRID_HPP

#include <vector>


class Grid
{
    private:
        float gridCellSize = 0.0f;

    public:
        // Constructors & Destructors
        Grid() = default;
        Grid(const Grid& other) = delete;
        Grid& operator=(const Grid& other) = delete;
        ~Grid() = default;

        // Getters & Setters
        void setGridCellSize(int windowHeight);

        // Member Functions
        void DrawGrid();
};

#endif
